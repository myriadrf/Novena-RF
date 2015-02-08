-- ----------------------------------------------------------------------------	
-- FILE:	mem_package.vhd
-- DESCRIPTION:	Define subtypes and types used in constructing memory arrays.
-- DATE:	Aug 20, 2001
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	Apr 18, 2007: Adapted for dsmN23SPI project
-- ----------------------------------------------------------------------------	

-- ----------------------------------------------------------------------------
library ieee; 
use ieee.std_logic_1164.all ;

package mem_package is 
	subtype mword8 is std_logic_vector(7 downto 0);      -- 8 bit memory word
 	type    marray16x8  is array (15 downto 0) of mword8;  -- 16x8b memory array
end mem_package;

