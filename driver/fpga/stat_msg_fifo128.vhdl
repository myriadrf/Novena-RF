------------------------------------------------------------------------
-- The status message fifo buffers multi-line status messages.
-- The input is a single wide status message,
-- the output is a 32bit multi-line data message.
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity stat_msg_fifo128 is
    generic(
        -- the fifo depth
        MEM_SIZE : positive := 16
    );
    port(
        -- The clock domain used for all interfaces.
        clk : in std_logic;

        -- synchronous reset
        rst : in std_logic;

        -- input bus interface
        in_tdata : in std_logic_vector(127 downto 0);
        in_tvalid : in std_logic;
        in_tready : out std_logic;

        -- output bus interface
        out_tdata : out std_logic_vector(31 downto 0);
        out_tlast : out std_logic;
        out_tvalid : out std_logic;
        out_tready : in std_logic
    );
end entity stat_msg_fifo128;

architecture rtl of stat_msg_fifo128 is

    signal msg_fifo_out_data : std_logic_vector(127 downto 0);
    signal msg_fifo_out_valid : std_logic;
    signal msg_fifo_out_ready : std_logic;
    signal out_tvalid_i : std_logic;
    signal out_tlast_i : std_logic;
    signal line0 : std_logic_vector(31 downto 0);
    signal line1 : std_logic_vector(31 downto 0);
    signal line2 : std_logic_vector(31 downto 0);
    signal line3 : std_logic_vector(31 downto 0);

    -- state machine enumerations
    type state_type is (
        STATE_READ,
        STATE_LINE0,
        STATE_LINE1,
        STATE_LINE2,
        STATE_LINE3);
    signal state : state_type;

begin

    out_tvalid <= out_tvalid_i;
    out_tvalid_i <= '0' when (state = STATE_READ) else '1';
    out_tlast <= out_tlast_i;
    out_tlast_i <= '1' when (state = STATE_LINE3) else '0';
    msg_fifo_out_ready <= '1' when (state = STATE_READ) else '0';
    out_tdata <=
        line0 when (state = STATE_LINE0) else
        line1 when (state = STATE_LINE1) else
        line2 when (state = STATE_LINE2) else line3;

    msg_fifo: entity work.StreamFifo
    generic map (
        --configure a small distributed ram
        MEM_SIZE => MEM_SIZE,
        SYNC_READ => false
    )
    port map (
        clk => clk,
        rst => rst,
        in_data => in_tdata,
        in_valid => in_tvalid,
        in_ready => in_tready,
        out_data => msg_fifo_out_data,
        out_valid => msg_fifo_out_valid,
        out_ready => msg_fifo_out_ready
    );

    process (clk) begin
    if (rising_edge(clk)) then
        if (rst = '1') then
            state <= STATE_READ;
            line0 <= (others => '0');
            line1 <= (others => '0');
            line2 <= (others => '0');
            line3 <= (others => '0');
        else case state is

        when STATE_READ =>
            if (msg_fifo_out_valid = '1' and msg_fifo_out_ready = '1') then
                line0 <= msg_fifo_out_data(127 downto 96);
                line1 <= msg_fifo_out_data(95 downto 64);
                line2 <= msg_fifo_out_data(63 downto 32);
                line3 <= msg_fifo_out_data(31 downto 0);
                state <= STATE_LINE0;
            end if;

        when STATE_LINE0 =>
            if (out_tvalid_i = '1' and out_tready = '1') then
                state <= STATE_LINE1;
            end if;

        when STATE_LINE1 =>
            if (out_tvalid_i = '1' and out_tready = '1') then
                state <= STATE_LINE2;
            end if;

        when STATE_LINE2 =>
            if (out_tvalid_i = '1' and out_tready = '1') then
                state <= STATE_LINE3;
            end if;

        when STATE_LINE3 =>
            if (out_tvalid_i = '1' and out_tready = '1') then
                state <= STATE_READ;
            end if;

        end case;
        end if;
    end if;
    end process;

end architecture rtl;
