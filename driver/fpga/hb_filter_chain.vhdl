------------------------------------------------------------------------
-- Configurable half-band filter chain:
--
--  * Interpolation and decimation supported.
--  * Select sample rate with bypasses selection.
--  * Configurable number of filters in chain.
--
-- TODO we have generated a single 11-tap interp and decim FIR filter
-- for all filters in the chain. This is not the best use of resources:
-- filters at lower rates can have more taps and more cycles.
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity hb_filter_chain is
    generic(
        -- the number of filters in the chain
        NUM_FILTERS : natural := 4;

        -- mode: "interp" or "decim"
        MODE : string := "interp"
    );
    port(
        -- The clock domain used for all interfaces.
        clk : in std_logic;

        -- synchronous reset
        rst : in std_logic;

        --configuration bypasses (1 = bypass, 0 = half-band)
        --index 0 = closest to the input
        --index N-1 = closest to the output
        bypass : in std_logic_vector(NUM_FILTERS-1 downto 0);

        -- input bus interface
        in_tdata : in std_logic_vector(31 downto 0);
        in_tvalid : in std_logic;
        in_tready : out std_logic;

        -- output bus interface
        out_tdata : out std_logic_vector(31 downto 0);
        out_tvalid : out std_logic;
        out_tready : in std_logic
    );
end entity hb_filter_chain;

architecture rtl of hb_filter_chain is

    signal datas : std_logic_vector((NUM_FILTERS*32) + 31 downto 0);
    signal valids : std_logic_vector(NUM_FILTERS downto 0);
    signal readies : std_logic_vector(NUM_FILTERS downto 0);

begin

    --connect input to chain start
    datas(31 downto 0) <= in_tdata;
    valids(0) <= in_tvalid;
    in_tready <= readies(0);

    --connect chain end to output
    out_tdata <= datas((NUM_FILTERS*32) + 31 downto (NUM_FILTERS*32));
    out_tvalid <= valids(NUM_FILTERS);
    readies(NUM_FILTERS) <= out_tready;

    gen_filters: for i in 0 to NUM_FILTERS-1 generate
        signal in_filter_data : std_logic_vector(31 downto 0);
        signal in_filter_ready : std_logic;
        signal in_filter_valid : std_logic;
        signal out_filter_data : std_logic_vector(31 downto 0);
        signal out_filter_ready : std_logic;
        signal out_filter_valid : std_logic;
    begin

        in_filter_data <= datas((i*32) + 31 downto (i*32));
        in_filter_valid <= valids(i) when (bypass(i) = '0') else '0';
        out_filter_ready <= readies(i+1) when (bypass(i) = '0') else '0';

        datas(((i+1)*32) + 31 downto ((i+1)*32)) <= out_filter_data when (bypass(i) = '0') else in_filter_data;
        valids(i+1) <= out_filter_valid when (bypass(i) = '0') else valids(i);
        readies(i) <= in_filter_ready when (bypass(i) = '0') else readies(i+1);

    interp_gen: if MODE = "interp" generate
        interp : entity work.half_band_interp
        port map (
            aclk => clk,
            s_axis_data_tdata => in_filter_data,
            s_axis_data_tvalid => in_filter_valid,
            s_axis_data_tready => in_filter_ready,
            m_axis_data_tdata => out_filter_data,
            m_axis_data_tvalid => out_filter_valid,
            m_axis_data_tready => out_filter_ready
        );
    end generate interp_gen;

    decim_gen: if MODE = "decim" generate
        decim : entity work.half_band_decim
        port map (
            aclk => clk,
            s_axis_data_tdata => in_filter_data,
            s_axis_data_tvalid => in_filter_valid,
            s_axis_data_tready => in_filter_ready,
            m_axis_data_tdata => out_filter_data,
            m_axis_data_tvalid => out_filter_valid,
            m_axis_data_tready => out_filter_ready
        );
    end generate decim_gen;

    end generate gen_filters;

end architecture rtl;
