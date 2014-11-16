-- ----------------------------------------------------------------------------	
-- FILE:	dds_top.vhd
-- DESCRIPTION:	Instantiates DDS IP and adopts data for LMS6.
-- DATE:	Jul 12, 2014.
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	
-- ----------------------------------------------------------------------------	
library ieee;
use ieee.std_logic_1164.all;

entity dds_top is port
	(
		clk: in std_logic;
		nrst: in std_logic;
		fcw: in std_logic_vector(26 downto 0);
		wrfcw: in std_logic;
		diq: out std_logic_vector(11 downto 0);
		iqsel: out std_logic
	);
end dds_top;

architecture dds_top_arch of dds_top is

	signal iqselr: std_logic;
	signal I, Q: std_logic_vector(11 downto 0);
	
  COMPONENT dds
  PORT(
       ce : IN  std_logic;
       clk : IN  std_logic;
       we : IN  std_logic;
       data : IN  std_logic_vector(26 downto 0);
       rdy : OUT  std_logic;
       cosine : OUT  std_logic_vector(11 downto 0);
       sine : OUT  std_logic_vector(11 downto 0)
      );
  END COMPONENT;

begin

	-- ---------------------------------------------------------------------------------------------
	-- IQSEL register
	-- ---------------------------------------------------------------------------------------------
	iqsel_proc: process(clk, nrst)
	begin
		if nrst = '0' then
			iqselr <= '1'; --(others => '0');
		elsif clk'event and clk = '1' then
			iqselr <= not iqselr;
		end if;
	end process iqsel_proc;
	
	iqsel <= iqselr;
	diq <= I when iqselr = '0' else Q;

	-- Instantiate the DDS
   idds: dds PORT MAP (
          ce => iqselr,
          clk => clk,
          we => wrfcw,
          data => fcw,
          rdy => open,
          cosine => I,
          sine => Q
        );

end dds_top_arch;

