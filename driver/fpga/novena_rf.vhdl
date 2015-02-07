------------------------------------------------------------------------
-- FPGA design for Novena-RF SDR
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http:--www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library work;

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity novena_rf is
    port(
        -- EIM signals
        EIM_BCLK : in std_logic;
        EIM_CS : in std_logic_vector(1 downto 0);
        EIM_DA : inout std_logic_vector(15 downto 0);
        EIM_A : in std_logic_vector(18 downto 16);
        EIM_LBA : in std_logic;
        EIM_OE : in std_logic;
        EIM_RW : in std_logic;
        EIM_WAIT : out std_logic;

        --misc clocks and reset
        clk_in : in std_logic; -- use with lms data
        CLK2_N : in std_logic;
        CLK2_P : in std_logic;-- 50MHz clock diff input
        FPGA_LED2 : out std_logic;
        APOPTOSIS : out std_logic;
        RESETBMCU : in std_logic;

        --lms control signals
        lms_rxen : out std_logic;
        lms_txen : out std_logic;
        lms_lmsrst : out std_logic;

        --spi to lms
        lms_sen : out std_logic;
        lms_sclk : out std_logic;
        lms_miso : in std_logic;
        lms_mosi : out std_logic;

        --spi from cpu
        cpu_sen : in std_logic;
        cpu_sclk : in std_logic;
        cpu_miso : out std_logic;
        cpu_mosi : in std_logic;

        --lms data buses
        TXIQSEL : out std_logic;
        TXD : out std_logic_vector(11 downto 0);
        RXIQSEL : in std_logic;
        RXD : in std_logic_vector(11 downto 0)
    );
end entity novena_rf;

architecture rtl of novena_rf is

    signal bus_clk : std_logic;
    signal bus_data_wr : std_logic_vector(15 downto 0);
    signal bus_data_rd : std_logic_vector(15 downto 0);
    signal bus_addr : std_logic_vector(18 downto 0);
    signal bus_sel : std_logic;
    signal bus_wr : std_logic;

    signal Wr_addr : natural range 0 to 15;
    signal Rd_addr : natural range 0 to 15;
    signal Wr_data : std_ulogic_vector(15 downto 0);
    signal Rd_data : std_ulogic_vector(15 downto 0);

begin

    --------------------------------------------------------------------
    -- framers here ... loopback for now
    --------------------------------------------------------------------
    TXIQSEL <= RXIQSEL;
    TXD <= RXD;
    lms_lmsrst <= '1';
    APOPTOSIS <= '0';
    lms_rxen <= '0';
    lms_txen <= '0';

    process (clk_in)
    begin
        FPGA_LED2 <= '0';
    end process;

    --------------------------------------------------------------------
    -- bypass cpu spi to lms
    --------------------------------------------------------------------
    spipass: entity work.spi_bypass
    port map (
        lms_sen => lms_sen,
        lms_sclk => lms_sclk,
        lms_miso => lms_miso,
        lms_mosi => lms_mosi,
        cpu_sen => cpu_sen,
        cpu_sclk => cpu_sclk,
        cpu_miso => cpu_miso,
        cpu_mosi => cpu_mosi
    );

    --------------------------------------------------------------------
    -- convert EIM into an internal addressable bus
    --------------------------------------------------------------------
    eim_bus: entity work.novena_eim
    port map (
        EIM_BCLK => EIM_BCLK,
        EIM_CS => EIM_CS,
        EIM_DA => EIM_DA,
        EIM_A => EIM_A,
        EIM_LBA => EIM_LBA,
        EIM_OE => EIM_OE,
        EIM_RW => EIM_RW,
        EIM_WAIT => EIM_WAIT,
        CLK2_N => CLK2_N,
        CLK2_P => CLK2_P,
        RESETBMCU => RESETBMCU,
        bus_clk => bus_clk,
        bus_data_wr => bus_data_wr,
        bus_data_rd => bus_data_rd,
        bus_addr => bus_addr,
        bus_sel => bus_sel,
        bus_wr => bus_wr
    );

    process (bus_clk)
        variable time_wait0 : boolean := false;
    begin
        if (rising_edge(bus_clk)) then
            --bus_data_rd <= std_logic_vector(to_unsigned(16#ABCD#, 16));
        end if;
    end process;

    --bus_data_rd <= bus_addr(15 downto 0);

    test_ram: entity work.dual_port_ram
    generic map (
        MEM_SIZE => 16--,
        --SYNC_READ => false
    )
    port map (
        Wr_clock => bus_clk,
        We => bus_wr,
        Wr_addr => Wr_addr,
        Wr_data => Wr_data,
        Rd_clock => bus_clk,
        Re => '1',
        Rd_addr => Rd_addr,
        Rd_data => Rd_data
    );

    Rd_addr <= Wr_addr when (bus_sel = '0') else (Wr_addr + 1);
    Wr_addr <= to_integer(unsigned(bus_addr(4 downto 1)));
    bus_data_rd <= std_logic_vector(Rd_data);
    Wr_data <= std_ulogic_vector(bus_data_wr);

end architecture rtl;
