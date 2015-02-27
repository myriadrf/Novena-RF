------------------------------------------------------------------------
-- Remove DC from a signed stream using subtract and integration.
--
-- Copyright (c) 2015-2015 Lime Microsystems
-- Copyright (c) 2015-2015 Andrew "bunnie" Huang
-- SPDX-License-Identifier: Apache-2.0
-- http://www.apache.org/licenses/LICENSE-2.0
------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;

entity dc_removal is
    generic(
        ALPHA_WIDTH : natural := 20
    );
    port(
        -- The clock domain used for all interfaces.
        clk : in std_logic;

        -- synchronous reset
        rst : in std_logic;

        -- enable automatic removal
        enable : in std_logic;

        -- input bus interface
        in_tdata : in std_logic_vector;
        in_tvalid : in std_logic;
        in_tready : out std_logic;

        -- output bus interface
        out_tdata : out std_logic_vector;
        out_tvalid : out std_logic;
        out_tready : in std_logic
    );
end entity dc_removal;

architecture rtl of dc_removal is

    constant DATA_WIDTH : positive := in_tdata'length;
    constant NUM_WIDTH : positive := DATA_WIDTH + ALPHA_WIDTH;

    signal out_num : signed(DATA_WIDTH-1 downto 0);
    signal last_avg : signed(NUM_WIDTH-1 downto 0);
    signal next_avg : signed(NUM_WIDTH-1 downto 0);
begin

    out_tvalid <= in_tvalid;
    in_tready <= out_tready;
    out_tdata <= std_logic_vector(out_num) when (enable = '1') else in_tdata;

    --integration equation
    next_avg <= out_num + last_avg;

    process (clk) begin
        if (rising_edge(clk)) then
            if (rst = '1') then
                last_avg <= to_signed(0, NUM_WIDTH);
                out_num <= to_signed(0, DATA_WIDTH);
            elsif (in_tvalid = '1' and out_tready = '1') then
                last_avg <= next_avg;
                out_num <= signed(in_tdata) - last_avg(NUM_WIDTH-1 downto NUM_WIDTH-DATA_WIDTH);
            end if;
        end if;
    end process;

end architecture rtl;
