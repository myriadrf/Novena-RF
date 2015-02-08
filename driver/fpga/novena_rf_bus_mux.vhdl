------------------------------------------------------------------------
-- The Novena RF bus mux:
--
-- Mux the captured EIM bus into multiple buses based on address.
-- The buses are selected with the top address bits 18:16.
-- The input bus is 19 bits, however, the output buses are 16 bits.
-- This mux could be grown to a maximum of 8 muxed interfaces.
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

entity novena_rf_bus_mux is
    port (
        --input bus from EIM capture
        bus_sel : in std_logic;
        bus_wr : in std_logic;
        bus_addr : in std_logic_vector(18 downto 0);
        bus_data_wr : in std_logic_vector(15 downto 0);
        bus_data_rd : out std_logic_vector(15 downto 0);

        --bus0 interface
        bus0_sel : out std_logic; -- valid register cycle
        bus0_wr : out std_logic; -- 1 = write, 0 = read
        bus0_addr : out std_logic_vector(15 downto 0);
        bus0_data_wr : out std_logic_vector(15 downto 0);
        bus0_data_rd : in std_logic_vector(15 downto 0);

        --bus1 interface
        bus1_sel : out std_logic; -- valid register cycle
        bus1_wr : out std_logic; -- 1 = write, 0 = read
        bus1_addr : out std_logic_vector(15 downto 0);
        bus1_data_wr : out std_logic_vector(15 downto 0);
        bus1_data_rd : in std_logic_vector(15 downto 0);

        --bus2 interface
        bus2_sel : out std_logic; -- valid register cycle
        bus2_wr : out std_logic; -- 1 = write, 0 = read
        bus2_addr : out std_logic_vector(15 downto 0);
        bus2_data_wr : out std_logic_vector(15 downto 0);
        bus2_data_rd : in std_logic_vector(15 downto 0);

        --bus3 interface
        bus3_sel : out std_logic; -- valid register cycle
        bus3_wr : out std_logic; -- 1 = write, 0 = read
        bus3_addr : out std_logic_vector(15 downto 0);
        bus3_data_wr : out std_logic_vector(15 downto 0);
        bus3_data_rd : in std_logic_vector(15 downto 0)
    );
end entity novena_rf_bus_mux;

architecture rtl of novena_rf_bus_mux is

begin

    -- selects
    bus0_sel <= bus_sel when (bus_addr(18 downto 16) = "000") else '0';
    bus1_sel <= bus_sel when (bus_addr(18 downto 16) = "001") else '0';
    bus2_sel <= bus_sel when (bus_addr(18 downto 16) = "010") else '0';
    bus3_sel <= bus_sel when (bus_addr(18 downto 16) = "011") else '0';

    -- write enable
    bus0_wr <= bus_wr;
    bus1_wr <= bus_wr;
    bus2_wr <= bus_wr;
    bus3_wr <= bus_wr;

    -- address
    bus0_addr <= bus_addr(15 downto 0);
    bus1_addr <= bus_addr(15 downto 0);
    bus2_addr <= bus_addr(15 downto 0);
    bus3_addr <= bus_addr(15 downto 0);

    -- write data
    bus0_data_wr <= bus_data_wr;
    bus1_data_wr <= bus_data_wr;
    bus2_data_wr <= bus_data_wr;
    bus3_data_wr <= bus_data_wr;

    -- read data
    bus_data_rd <=
        bus0_data_rd when (bus_addr(18 downto 16) = "000") else
        bus1_data_rd when (bus_addr(18 downto 16) = "001") else
        bus2_data_rd when (bus_addr(18 downto 16) = "010") else
        bus3_data_rd;

end architecture rtl;
