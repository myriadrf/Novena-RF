------------------------------------------------------------------------
-- LMS TRX - data capture and source synchronous interface.
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

entity lms_trx is
    port(
        lms_clk : in std_logic;

        --loopback tx data into rx
        loopback : in std_logic := '0';

        --external
        TXIQSEL : out std_logic;
        TXD : out std_logic_vector(11 downto 0);
        RXIQSEL : in std_logic;
        RXD : in std_logic_vector(11 downto 0);

        --internal
        dac_data : in std_logic_vector(31 downto 0);
        dac_ready : out std_logic;
        adc_data : out std_logic_vector(31 downto 0);
        adc_valid : out std_logic
    );
end entity lms_trx;

architecture rtl of lms_trx is
    signal rxd_r : std_logic_vector(11 downto 0);
    signal txd_r : std_logic_vector(11 downto 0);
    signal rxiqsel_r : std_logic;
    signal txiqsel_r : std_logic;

    signal txd_r_next : std_logic_vector(11 downto 0);
    signal dac_ready_int : std_logic;

    signal rxd_r_prev : std_logic_vector(11 downto 0);
    signal adc_valid_int : std_logic;
begin

    dac_ready <= dac_ready_int;
    adc_valid <= adc_valid_int;

    --all external pins directly from flops
    process (lms_clk) begin
    if (rising_edge(lms_clk)) then
        rxd_r <= RXD;
        rxiqsel_r <= RXIQSEL;
        TXD <= txd_r;
        TXIQSEL <= txiqsel_r;
    end if;
    end process;

    --rx data registered
    process (lms_clk) begin
    if (rising_edge(lms_clk)) then
        adc_valid_int <= not rxiqsel_r;
        rxd_r_prev <= rxd_r;
        adc_data(31 downto 20) <= rxd_r_prev;
        adc_data(19 downto 16) <= "0000";
        adc_data(15 downto 4) <= rxd_r;
        adc_data(3 downto 0) <= "0000";
        if (loopback = '1') then
            adc_valid_int <= txiqsel_r;
            rxd_r_prev <= txd_r;
            adc_data(15 downto 4) <= txd_r;
        end if;
    end if;
    end process;

    --tx data registered
    process (lms_clk) begin
    if (rising_edge(lms_clk)) then
        dac_ready_int <= not dac_ready_int;
        if (dac_ready_int = '1') then
            txd_r_next <= dac_data(15 downto 4);
            txd_r <= dac_data(31 downto 20);
            txiqsel_r <= '1';
        else
            txd_r <= txd_r_next;
            txiqsel_r <= '0';
        end if;
    end if;
    end process;

end architecture rtl;
