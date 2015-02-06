-- ----------------------------------------------------------------------------
-- FILE:	spi_bypass.vhd
-- DESCRIPTION:	
-- DATE:	07 Jul, 2014
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	
-- ----------------------------------------------------------------------------
library ieee;
use ieee.std_logic_1164.all;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

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

