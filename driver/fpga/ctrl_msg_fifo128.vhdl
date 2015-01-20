------------------------------------------------------------------------
-- The control message fifo buffers multi-line control messages.
-- The input is a 32bit multi-line data message,
-- the output is a single wide control message.
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity ctrl_msg_fifo128 is
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
        in_tdata : in std_logic_vector(31 downto 0);
        in_tlast : in std_logic;
        in_tvalid : in std_logic;
        in_tready : out std_logic;

        -- output bus interface
        out_tdata : out std_logic_vector(127 downto 0);
        out_tvalid : out std_logic;
        out_tready : in std_logic
    );
end entity ctrl_msg_fifo128;

architecture rtl of ctrl_msg_fifo128 is

    signal msg_fifo_in_data : std_logic_vector(127 downto 0);
    signal msg_fifo_in_valid : std_logic;
    signal msg_fifo_in_ready : std_logic;
    signal in_tready_i : std_logic;

    -- state machine enumerations
    type state_type is (
        STATE_LINE0,
        STATE_LINE1,
        STATE_LINE2,
        STATE_LINE3,
        STATE_LINEN,
        STATE_WRITE);
    signal state : state_type;

begin

    in_tready <= in_tready_i;
    in_tready_i <= '1' when (state /= STATE_WRITE) else '0';
    msg_fifo_in_valid <= '1' when (state = STATE_WRITE) else '0';

    msg_fifo: entity work.StreamFifo
    generic map (
        --configure a small distributed ram
        MEM_SIZE => MEM_SIZE,
        SYNC_READ => false
    )
    port map (
        clk => clk,
        rst => rst,
        in_data => msg_fifo_in_data,
        in_valid => msg_fifo_in_valid,
        in_ready => msg_fifo_in_ready,
        out_data => out_tdata,
        out_valid => out_tvalid,
        out_ready => out_tready
    );

    process (clk) begin
    if (rising_edge(clk)) then
        if (rst = '1') then
            state <= STATE_LINE0;
        else case state is

        when STATE_LINE0 =>
            if (in_tvalid = '1' and in_tready_i = '1') then
                msg_fifo_in_data(127 downto 96) <= in_tdata;
                if (in_tlast = '1') then
                    state <= STATE_WRITE;
                else
                    state <= STATE_LINE1;
                end if;
            end if;

        when STATE_LINE1 =>
            if (in_tvalid = '1' and in_tready_i = '1') then
                msg_fifo_in_data(95 downto 64) <= in_tdata;
                if (in_tlast = '1') then
                    state <= STATE_WRITE;
                else
                    state <= STATE_LINE2;
                end if;
            end if;

        when STATE_LINE2 =>
            if (in_tvalid = '1' and in_tready_i = '1') then
                msg_fifo_in_data(63 downto 32) <= in_tdata;
                if (in_tlast = '1') then
                    state <= STATE_WRITE;
                else
                    state <= STATE_LINE3;
                end if;
            end if;

        when STATE_LINE3 =>
            if (in_tvalid = '1' and in_tready_i = '1') then
                msg_fifo_in_data(31 downto 0) <= in_tdata;
                if (in_tlast = '1') then
                    state <= STATE_WRITE;
                else
                    state <= STATE_LINEN;
                end if;
            end if;

        when STATE_LINEN =>
            if (in_tvalid = '1' and in_tready_i = '1') then
                if (in_tlast = '1') then
                    state <= STATE_WRITE;
                end if;
            end if;

        when STATE_WRITE =>
            if (msg_fifo_in_valid = '1' and msg_fifo_in_ready = '1') then
                state <= STATE_LINE0;
            end if;

        end case;
        end if;
    end if;
    end process;

end architecture rtl;
