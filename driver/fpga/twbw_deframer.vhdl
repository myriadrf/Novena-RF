------------------------------------------------------------------------
-- TWBW Deframer - DAC sample deframer with time and burst controls
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity twbw_deframer is
    generic(
        -- the width of the ADC bus
        DATA_WIDTH : positive := 32;

        -- the width of the time bus
        TIME_WIDTH : positive := 48
    );
    port(
        -- the DAC clock domain used for all interfaces
        clk : in std_logic;

        -- synchronous reset
        rst : in std_logic;

        -- the current time in clock ticks
        in_time : in unsigned(TIME_WIDTH-1 downto 0);

        -- output DAC interface
        -- there is no valid signal, a ready signal with no data => underflow
        dac_tdata : out std_logic_vector(DATA_WIDTH-1 downto 0);
        dac_tready : in std_logic;

        -- input stream interface
        -- The tuser signal indicates metadata and not sample data
        in_tdata : in std_logic_vector(DATA_WIDTH-1 downto 0);
        in_tuser : in std_logic_vector(0 downto 0);
        in_tlast : in std_logic;
        in_tvalid : in std_logic;
        in_tready : out std_logic;

        -- control bus interface
        ctrl_tdata : in std_logic_vector(31 downto 0);
        ctrl_tlast : in std_logic;
        ctrl_tvalid : in std_logic;
        ctrl_tready : out std_logic;

        -- status bus interface
        stat_tdata : out std_logic_vector(31 downto 0);
        stat_tlast : out std_logic;
        stat_tvalid : out std_logic;
        stat_tready : in std_logic;

        -- Transmit activity indicator based on internal state.
        -- Example: use this signal to drive external switches and LEDs.
        dac_active : out boolean
    );
end entity twbw_deframer;

architecture rtl of twbw_deframer is


begin

    

end architecture rtl;
