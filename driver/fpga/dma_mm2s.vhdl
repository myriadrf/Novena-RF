------------------------------------------------------------------------
-- DMA memory mapped to stream block:
-- Interface between a writable memory and an output stream.
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

entity dma_mm2s is
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
        --line0: begin_addr16
        --line1: end_addr16
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

        --memory interface
        mem_sel : in std_logic;
        mem_wr : in std_logic;
        mem_addr : in std_logic_vector(15 downto 0);
        mem_data : in std_logic_vector(15 downto 0);

        --output stream
        stream_data : out std_logic_vector(31 downto 0);
        stream_last : out std_logic;
        stream_valid : out std_logic;
        stream_ready : in std_logic
    );
end entity dma_mm2s;

architecture rtl of dma_mm2s is

    --stream internal signals
    signal stream_valid_int : std_logic;
    signal stream_last_int : std_logic;

    --ctrl fifo in stream domain
    signal ctrl_data_int : std_logic_vector(15 downto 0);
    signal ctrl_valid_int : std_logic;
    signal ctrl_ready_int : std_logic;

    --stat fifo in stream domain
    signal stat_data_int : std_logic_vector(15 downto 0);
    signal stat_valid_int : std_logic;
    signal stat_ready_int : std_logic;

    --ram access signals
    signal Re : std_logic;
    signal We0 : std_logic;
    signal We1 : std_logic;
    signal Wr_addr : natural range 0 to MEM_SIZE-1;
    signal Rd_addr : natural range 0 to MEM_SIZE-1;
    signal Wr_data : std_ulogic_vector(15 downto 0);
    signal Rd0_data : std_ulogic_vector(15 downto 0);
    signal Rd1_data : std_ulogic_vector(15 downto 0);
    signal Even : boolean;

    --state machine signals
    type state_type is (
        STATE_RD_CTRL,
        STATE_RD_END,
        STATE_READ0,
        STATE_STREAM,
        STATE_WR_STAT);
    signal state : state_type;
    signal active_addr : unsigned(15 downto 0);
    signal last_addr : unsigned(15 downto 0);

    signal arstn : std_logic;

begin

    arstn <= '0' when (mem_rst = '1' or stream_rst = '1') else '1';

    --------------------------------------------------------------------
    -- Stream interface
    --------------------------------------------------------------------
    stream_valid <= stream_valid_int;
    stream_last <= stream_last_int;
    stream_valid_int <= '1' when (state = STATE_STREAM) else '0';
    stream_last_int <= '1' when (active_addr = last_addr) else '0';
    stream_data(15 downto 0) <= std_logic_vector(Rd0_data);
    stream_data(31 downto 16) <= std_logic_vector(Rd1_data);

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

    ctrl_ready_int <= '1' when (state = STATE_RD_CTRL or state = STATE_RD_END) else '0';

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
    dma_ram0: entity work.dual_port_ram
    generic map (
        MEM_SIZE => MEM_SIZE
    )
    port map (
        Wr_clock => mem_clk,
        We => We0,
        Wr_addr => Wr_addr,
        Wr_data => Wr_data,
        Rd_clock => stream_clk,
        Re => Re,
        Rd_addr => Rd_addr,
        Rd_data => Rd0_data
    );
    dma_ram1: entity work.dual_port_ram
    generic map (
        MEM_SIZE => MEM_SIZE
    )
    port map (
        Wr_clock => mem_clk,
        We => We1,
        Wr_addr => Wr_addr,
        Wr_data => Wr_data,
        Rd_clock => stream_clk,
        Re => Re,
        Rd_addr => Rd_addr,
        Rd_data => Rd1_data
    );

    --write IO (mux based on word16)
    Even <= mem_addr(1) = '0';
    We0 <= mem_sel and mem_wr when (Even) else '0';
    We1 <= mem_sel and mem_wr when (not Even) else '0';
    Wr_data <= std_ulogic_vector(mem_data);
    Wr_addr <= to_integer(unsigned(mem_addr(15 downto 2)));

    --read IO (word32 aligned)
    Rd_addr <= to_integer(unsigned(active_addr(15 downto 2)));
    Re <= '1' when (state = STATE_READ0) else (stream_valid_int and stream_ready);

    --------------------------------------------------------------------
    -- State machine
    --------------------------------------------------------------------
    process (stream_clk) begin

    if (rising_edge(stream_clk)) then

        if (stream_rst = '1') then
            state <= STATE_RD_CTRL;
            active_addr <= to_unsigned(0, active_addr'length);
            last_addr <= to_unsigned(0, last_addr'length);
        else case state is

        when STATE_RD_CTRL =>
            if (ctrl_valid_int = '1' and ctrl_ready_int = '1') then
                state <= STATE_RD_END;
                active_addr <= unsigned(ctrl_data_int);
            end if;

        when STATE_RD_END =>
            if (ctrl_valid_int = '1' and ctrl_ready_int = '1') then
                state <= STATE_READ0;
                last_addr <= unsigned(ctrl_data_int);
            end if;

        when STATE_READ0 =>
            state <= STATE_STREAM;
            active_addr <= active_addr + to_unsigned(4, active_addr'length);

        when STATE_STREAM =>

            if (stream_valid_int = '1' and stream_ready = '1') then
                active_addr <= active_addr + to_unsigned(4, active_addr'length);
                if (stream_last_int = '1') then
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
