-- ----------------------------------------------------------------------------	
-- FILE:	alive.vhd
-- DESCRIPTION:	Heartbeat counter and apoptosis control.
-- DATE:	Jul 12, 2014.
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	
-- ----------------------------------------------------------------------------	

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;


entity alive is	port
	(
		 rst: in std_logic;
		 clk: in std_logic;
		 beat: out std_logic;
		 APOPTOSIS: out std_logic
	);
end alive;

architecture alive_arch of alive is
	signal cnt: unsigned (23 downto 0);
begin

--=============================================
-- Counter
--=============================================
	cntp: process (clk, rst)
	begin
		if rst = '0' then
			cnt <= (others => '1');
		elsif (clk'event and clk = '1') then
			cnt <= cnt + 1;
		end if;
	end process cntp;
	
	beat <= cnt(23);
	
	APOPTOSIS <= '0';

end alive_arch;

