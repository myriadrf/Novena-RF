-- ----------------------------------------------------------------------------	
-- FILE:	components.vhd
-- DESCRIPTION:	This package contains SPI component declarations.
-- DATE:	Jul 12, 2014.
-- AUTHOR(s):	Lime Microsystems
-- REVISION
-- ----------------------------------------------------------------------------	

library	ieee;
use ieee.std_logic_1164.all;

-- ----------------------------------------------------------------------------
-- Package declaration
-- ----------------------------------------------------------------------------

package spi_components is

-- ----------------------------------------------------------------------------
component spi_fsm
	port (		  
		address: in std_logic_vector(2 downto 0);	-- Hardware address
		inst_reg: in std_logic_vector(7 downto 0);	-- Instruction register (read only here)
		sclk: in std_logic;				-- Serial clock
		sen: in std_logic;				-- Serial enable
		reset: in std_logic;				-- Reset
		inst_reg_en: out std_logic;			-- Instruction register enable
		din_reg_en: out std_logic;			-- Data in register enable
		dout_reg_sen: out std_logic;			-- Data out register shift enable
		dout_reg_len: out std_logic;			-- Data out register load enable
		mem_we: out std_logic;				-- Memory write enable
		oe: out std_logic				-- Output enable 	
	);
end component;

-- ----------------------------------------------------------------------------
component spi_mod
	port (
		-- Address and location of this module
		-- These signals will be hard wired at the top level
		maddress: in std_logic_vector(2 downto 0);
	
		-- Serial port IOs
		sadin: in std_logic;		-- Data in
		saclk: in std_logic;		-- Data clock
		saen: in std_logic;			-- Enable signal (active low)
		sadout: out std_logic;	-- Data out
	
		-- Signals coming from the pins or top level serial interface
		hreset: in std_logic;	-- Hard reset signal, resets everything
		
		--Control signals
		gpio0 : buffer std_logic;
		gpio1 : buffer std_logic;
		gpio2 : buffer std_logic;
		txen : buffer std_logic;
		rxen : buffer std_logic;
		reset : buffer std_logic;
		
		txdds_fcw: buffer std_logic_vector(26 downto 0);
		txdds_fcw_upd: buffer std_logic;

		oen: out std_logic
	);
end component;

-- ----------------------------------------------------------------------------

end spi_components;
