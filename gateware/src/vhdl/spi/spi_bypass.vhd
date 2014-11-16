-- ----------------------------------------------------------------------------	
-- FILE:	spi_bypass.vhd
-- DESCRIPTION:	Bypass SPI signalls from CPU to LMS6.
-- DATE:	Jul 12, 2014.
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	Apr 18, 2007: Adapted for dsmN23SPI project
-- ----------------------------------------------------------------------------	

library ieee;
use ieee.std_logic_1164.all;

entity spi_bypass is port
	(
		 cpu_sclk: in  std_logic;
		 lms_sclk: out std_logic;
		 cpu_mosi: in  std_logic;
		 lms_mosi: out std_logic;
		 cpu_miso: out std_logic;
		 lms_miso: in  std_logic;
		 cpu_sen:  in  std_logic;
		 lms_sen:  out std_logic
	);
end spi_bypass;

architecture spi_bypass_arch of spi_bypass is

begin

	lms_sclk <= cpu_sclk;		 
	lms_mosi <= cpu_mosi;
	cpu_miso <= lms_miso;
	lms_sen <= cpu_sen;

end spi_bypass_arch;

