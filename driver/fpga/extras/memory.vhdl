--------------------------------------------------------------------
--  _    __ __  __ ____   __   =                                  --
-- | |  / // / / // __ \ / /   =                                  --
-- | | / // /_/ // / / // /    =    .__  |/ _/_  .__   .__    __  --
-- | |/ // __  // /_/ // /___  =   /___) |  /   /   ) /   )  (_ ` --
-- |___//_/ /_//_____//_____/  =  (___  /| (_  /     (___(_ (__)  --
--                           =====     /                          --
--                            ===                                 --
-----------------------------  =  ----------------------------------
--# memory.vhdl - Generic memories
--# $Id$
--# Freely available from VHDL-extras (http://code.google.com/p/vhdl-extras)
--#
--# Copyright © 2014 Kevin Thibedeau
--# (kevin 'period' thibedeau 'at' gmail 'punto' com)
--#
--# Permission is hereby granted, free of charge, to any person obtaining a
--# copy of this software and associated documentation files (the "Software"),
--# to deal in the Software without restriction, including without limitation
--# the rights to use, copy, modify, merge, publish, distribute, sublicense,
--# and/or sell copies of the Software, and to permit persons to whom the
--# Software is furnished to do so, subject to the following conditions:
--#
--# The above copyright notice and this permission notice shall be included in
--# all copies or substantial portions of the Software.
--#
--# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
--# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
--# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
--# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
--# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
--# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
--# DEALINGS IN THE SOFTWARE.
--#
--# DEPENDENCIES: none
--#
--# DESCRIPTION:
--#  This package provides general purpose components for inferred RAM and ROM.
--#  These memories share a SYNC_READ generic which will optionally generate
--#  synchronous or asynchronous read ports for each instance. On Xilinx devices
--#  asynchronous read forces the synthesis of distributed RAM using LUTs rather
--#  than BRAMs. When SYNC_READ is false the Read enable input is unused.
--#
--#  The ROM component gets its contents using synthesizable file IO to read a
--#  list of binary or hex values.
--------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;

package memory is

  component dual_port_ram is
    generic (
      MEM_SIZE  : positive;
      SYNC_READ : boolean := true
    );
    port (
      Wr_clock : in std_ulogic;
      We       : in std_ulogic; -- Write enable
      Wr_addr  : in natural range 0 to MEM_SIZE-1;
      Wr_data  : in std_ulogic_vector;

      Rd_clock : in std_ulogic;
      Re       : in std_ulogic; -- Read enable
      Rd_addr  : in natural range 0 to MEM_SIZE-1;
      Rd_data  : out std_ulogic_vector
    );
  end component;

  type rom_format is (BINARY_TEXT, HEX_TEXT);

  component rom is
    generic (
      ROM_FILE  : string;
      FORMAT    : rom_format;
      MEM_SIZE  : positive;
      SYNC_READ : boolean := true
    );
    port (
      Clock : in std_ulogic;
      Re    : in std_ulogic; -- Read enable
      Addr  : in natural range 0 to MEM_SIZE-1;
      Data  : out std_ulogic_vector
    );
  end component;


end package;



library ieee;
use ieee.std_logic_1164.all;

entity dual_port_ram is
  generic (
    MEM_SIZE  : positive;
    SYNC_READ : boolean := true
  );
  port (
    Wr_clock : in std_ulogic;
    We       : in std_ulogic; -- Write enable
    Wr_addr  : in natural range 0 to MEM_SIZE-1;
    Wr_data  : in std_ulogic_vector;

    Rd_clock : in std_ulogic;
    Re       : in std_ulogic; -- Read enable
    Rd_addr  : in natural range 0 to MEM_SIZE-1;
    Rd_data  : out std_ulogic_vector
  );
end entity;

architecture rtl of dual_port_ram is
  type ram_type is array (0 to MEM_SIZE-1) of std_ulogic_vector(Wr_data'length-1 downto 0);
  signal ram : ram_type;

  signal sync_rdata : std_ulogic_vector(Rd_data'range);
begin
  assert Wr_data'length = Rd_data'length report "Data bus size mismatch" severity failure;

  wr: process(Wr_clock)
  begin
    if rising_edge(Wr_clock) then
      if We = '1' then
        ram(Wr_addr) <= Wr_data;
      end if;
    end if;
  end process;

  sread: if SYNC_READ = true generate
  rd: process(Rd_clock)
  begin
    if rising_edge(Rd_clock) then
      if Re = '1' then
        sync_rdata <= ram(Rd_addr);
      end if;
    end if;
  end process;
  end generate;

  Rd_data <= ram(Rd_addr) when SYNC_READ = false else sync_rdata;

end architecture;
