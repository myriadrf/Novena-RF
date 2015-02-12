------------------------------------------------------------------------
-- DMA stream to memory map block:
-- Interface between an input stream and a readable memory.
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library work;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity dma_s2mm is
    generic(
        --number of 32 bit words in the DMA block
        MEM_SIZE : positive;

        --the max depth of the control/status fifos
        CTRL_DEPTH : positive := 16
    );
    port (
        --clocks and resets
        mem_clk : in std_logic;
        mem_rst : in std_logic;
        stream_clk : in std_logic;
        stream_rst : in std_logic;

        --control interface (mem domain)
        --format: begin_addr16
        --write this control fifo to cause a DMA
        ctrl_data : in std_logic_vector(15 downto 0);
        ctrl_valid : in std_logic;
        ctrl_ready : out std_logic;

        --status interface (mem domain)
        --format: end_addr16
        --read the status fifo when DMAs complete
        stat_data : out std_logic_vector(15 downto 0);
        stat_valid : out std_logic;
        stat_ready : in std_logic;

        --memory interface (always reads)
        mem_sel : in std_logic;
        mem_addr : in std_logic_vector(15 downto 0);
        mem_data : out std_logic_vector(15 downto 0);

        --input stream
        stream_data : in std_logic_vector(31 downto 0);
        stream_last : in std_logic;
        stream_valid : in std_logic;
        stream_ready : out std_logic
    );
end entity dma_s2mm;

architecture rtl of dma_s2mm is

    --stream internal signals
    signal stream_ready_int : std_logic;

    --ctrl fifo in stream domain
    signal ctrl_data_int : std_logic_vector(15 downto 0);
    signal ctrl_valid_int : std_logic;
    signal ctrl_ready_int : std_logic;

    --stat fifo in stream domain
    signal stat_data_int : std_logic_vector(15 downto 0);
    signal stat_valid_int : std_logic;
    signal stat_ready_int : std_logic;

    --ram access signals
    signal We : std_logic;
    signal Wr_addr : natural range 0 to MEM_SIZE-1;
    signal Rd_addr : natural range 0 to MEM_SIZE-1;
    signal Rd_addr_pre : unsigned(15 downto 0);
    signal Wr_data : std_ulogic_vector(31 downto 0);
    signal Rd_data : std_ulogic_vector(31 downto 0);
    signal Even : boolean;

    --state machine signals
    type state_type is (
        STATE_RD_CTRL,
        STATE_STREAM,
        STATE_WR_STAT);
    signal state : state_type;
    signal active_addr : unsigned(15 downto 0);

    signal arstn : std_logic;

begin

    arstn <= '0' when (mem_rst = '1' or stream_rst = '1') else '1';

    --------------------------------------------------------------------
    -- Stream interface
    --------------------------------------------------------------------
    stream_ready <= stream_ready_int;
    stream_ready_int <= '1' when (state = STATE_STREAM) else '0';

    --------------------------------------------------------------------
    -- Control FIFO
    --------------------------------------------------------------------
    ctrl_fifo : entity work.stream_fifo16_xclk
    port map (
        m_aclk => stream_clk,
        s_aclk => mem_clk,
        s_aresetn => arstn,
        s_axis_tdata => ctrl_data,
        s_axis_tvalid => ctrl_valid,
        s_axis_tready => ctrl_ready,
        m_axis_tdata => ctrl_data_int,
        m_axis_tvalid => ctrl_valid_int,
        m_axis_tready => ctrl_ready_int
    );

    ctrl_ready_int <= '1' when (state = STATE_RD_CTRL) else '0';

    --------------------------------------------------------------------
    -- Status FIFO
    --------------------------------------------------------------------
    stat_fifo : entity work.stream_fifo16_xclk
    port map (
        m_aclk => mem_clk,
        s_aclk => stream_clk,
        s_aresetn => arstn,
        s_axis_tdata => stat_data_int,
        s_axis_tvalid => stat_valid_int,
        s_axis_tready => stat_ready_int,
        m_axis_tdata => stat_data,
        m_axis_tvalid => stat_valid,
        m_axis_tready => stat_ready
    );

    stat_data_int <= std_logic_vector(active_addr);
    stat_valid_int <= '1' when (state = STATE_WR_STAT) else '0';

    --------------------------------------------------------------------
    -- DMA RAM connections
    --------------------------------------------------------------------
    dma_ram: entity work.dual_port_ram
    generic map (
        MEM_SIZE => MEM_SIZE
    )
    port map (
        Wr_clock => stream_clk,
        We => We,
        Wr_addr => Wr_addr,
        Wr_data => Wr_data,
        Rd_clock => mem_clk,
        Re => '1',
        Rd_addr => Rd_addr,
        Rd_data => Rd_data
    );

    --read IO (mux based on word16)
    Rd_addr_pre <= unsigned(mem_addr) when (mem_sel = '0') else (unsigned(mem_addr) + 2);
    Rd_addr <= to_integer(Rd_addr_pre(15 downto 2));
    mem_data <= std_logic_vector(Rd_data(15 downto 0)) when (Even)
        else std_logic_vector(Rd_data(31 downto 16));
    process (mem_clk) begin
        if (rising_edge(mem_clk)) then
            Even <= Rd_addr_pre(1) = '0';
        end if;
    end process;

    --write IO (word32 aligned)
    We <= stream_valid and stream_ready_int;
    Wr_data <= std_ulogic_vector(stream_data);
    Wr_addr <= to_integer(unsigned(active_addr(15 downto 2)));

    --------------------------------------------------------------------
    -- State machine
    --------------------------------------------------------------------
    process (stream_clk) begin

    if (rising_edge(stream_clk)) then

        if (stream_rst = '1') then
            state <= STATE_RD_CTRL;
            active_addr <= to_unsigned(0, active_addr'length);
        else case state is

        when STATE_RD_CTRL =>
            if (ctrl_valid_int = '1' and ctrl_ready_int = '1') then
                state <= STATE_STREAM;
                active_addr <= unsigned(ctrl_data_int);
            end if;

        when STATE_STREAM =>
            if (stream_valid = '1' and stream_ready_int = '1') then
                active_addr <= active_addr + to_unsigned(4, active_addr'length);
                if (stream_last = '1') then
                    state <= STATE_WR_STAT;
                end if;
            end if;

        when STATE_WR_STAT =>
            if (stat_valid_int = '1' and stat_ready_int = '1') then
                state <= STATE_RD_CTRL;
            end if;

        end case;
        end if;
    end if;

    end process;

end architecture rtl;
