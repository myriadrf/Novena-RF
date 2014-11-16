-- ----------------------------------------------------------------------------
-- FILE:	spi_mod.vhd
-- DESCRIPTION:	Serial configuration interface
-- DATE:	2007.06.07
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:	
-- ----------------------------------------------------------------------------

library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;
use work.mem_package.all;

-- ----------------------------------------------------------------------------
-- Entity declaration
-- ----------------------------------------------------------------------------
entity spi_mod is
	port(
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
		
		measburst: in std_logic_vector(15 downto 0);
		actid: in std_logic;
		
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
end spi_mod;

-- ----------------------------------------------------------------------------
-- Architecture
-- ----------------------------------------------------------------------------
architecture spi_mod_arch of spi_mod is
	signal inst_reg: std_logic_vector(7 downto 0);	-- Instruction register
	signal inst_reg_en: std_logic;
	
	signal din_reg: std_logic_vector(7 downto 0);		-- Data in register
	signal din_reg_en: std_logic;
	signal dout_reg: std_logic_vector(7 downto 0);	-- Data out register
	signal dout_reg_sen, dout_reg_len: std_logic;
	
	signal mem: marray16x8;					-- Config memory
	signal mem_we: std_logic;
	
	signal oe: std_logic;				-- Tri state buffers control 
	
	use work.spi_components.spi_fsm;
	for all: spi_fsm use entity work.spi_fsm(fsm_arch);

begin
	-- ---------------------------------------------------------------------------------------------
	-- Finite state machine
	-- ---------------------------------------------------------------------------------------------
	fsm: spi_fsm port map( 
		address => maddress, inst_reg => inst_reg, sclk => saclk, sen => saen, reset => hreset,
		inst_reg_en => inst_reg_en, din_reg_en => din_reg_en, dout_reg_sen => dout_reg_sen,
		dout_reg_len => dout_reg_len, mem_we => mem_we, oe => oe);



	-- ---------------------------------------------------------------------------------------------
	-- Instruction register
	-- ---------------------------------------------------------------------------------------------
	inst_reg_proc: process(saclk, hreset)
		variable i: integer;
	begin
		if hreset = '0' then
			inst_reg <= (others => '0');
		elsif saclk'event and saclk = '1' then
			if inst_reg_en = '1' then
				for i in 7 downto 1 loop
					inst_reg(i) <= inst_reg(i-1);
				end loop;
				inst_reg(0) <= sadin;
			end if;
		end if;
	end process inst_reg_proc;

	-- ---------------------------------------------------------------------------------------------
	-- Data input register
	-- ---------------------------------------------------------------------------------------------
	din_reg_proc: process(saclk, hreset)
		variable i: integer;
	begin
		if hreset = '0' then
			din_reg <= (others => '0');
		elsif saclk'event and saclk = '1' then
			if din_reg_en = '1' then
				for i in 7 downto 1 loop
					din_reg(i) <= din_reg(i-1);
				end loop;
				din_reg(0) <= sadin;
			end if;
		end if;
	end process din_reg_proc;

	-- ---------------------------------------------------------------------------------------------
	-- Data output register
	-- ---------------------------------------------------------------------------------------------
	dout_reg_proc: process(saclk, hreset)
		variable i: integer;
	begin
		if hreset = '0' then
			dout_reg <= (others => '0');
		elsif saclk'event and saclk = '0' then
			-- Shift operation
			if dout_reg_sen = '1' then
				for i in 7 downto 1 loop
					dout_reg(i) <= dout_reg(i-1);
				end loop;
				dout_reg(0) <= dout_reg(7);
			-- Load operation
			elsif dout_reg_len = '1' then
				dout_reg <= mem(to_integer(unsigned(inst_reg(3 downto 0))));
			end if;
		end if;
	end process dout_reg_proc;

	-- Tri state buffer to connect multiple serial interfaces in parallel
	--sadout <= dout_reg(7) when oe = '1' else 'Z';

--	sadout <= dout_reg(7);
--	oen <= oe;
	
	sadout <= dout_reg(7) and oe;
	oen <= oe;

	-- ---------------------------------------------------------------------------------------------
	-- Configuration memory
	-- --------------------------------------------------------------------------------------------- 
	ram: process(saclk, hreset)
	begin
		-- Defaults
		if hreset = '0' then
			mem(0)  <= "00000000";
			mem(1)  <= "00000000";
			mem(2)  <= "00000000";
			mem(3)  <= "00000000";
			mem(4)  <= "00000000";
			mem(5)  <= "00000000";
			mem(6)  <= "00000000";
			
			mem(7)  <= "00000000";
			mem(8)  <= "00111000";	-- LMS_RESET, LMS_RXEN, LMS_TXEN, MRF_GPIO2, MRF_GPIO1, MRF_GPIO0
			mem(9)  <= "01010101";	-- TXDDS_FCW[7:0]
			mem(10) <= "01010101";	-- TXDDS_FCW[15:8]
			mem(11) <= "10000101";	-- TXDDS_FCW[23:9]
			mem(12) <= "00000000";	-- FREE[3:0], TXDDS_FCW_UPD, TXDDS_FCW[26:24]
			mem(13) <= "00000000";			
			
			mem(14)	<= "00000000";
			mem(15)	<= "00000000";
			
		elsif saclk'event and saclk = '1' then
			if mem_we = '1' then
				mem(to_integer(unsigned(inst_reg(3 downto 0)))) <= din_reg(6 downto 0) & sadin;
			end if;
			
			--if saen = '1' then
				mem(7) <= measburst(7 downto 0);
				mem(13) <= measburst(15 downto 8);

				mem(0)(0) <= actid;
			--end if;
			
			
		end if;
	end process ram;
	
	-- ---------------------------------------------------------------------------------------------
	-- Decoding logic
	-- ---------------------------------------------------------------------------------------------
	
	
	--0x8
	gpio0 <= mem(8)(0);
	gpio1 <= mem(8)(1);
	gpio2 <= mem(8)(2);
	txen <= mem(8)(3);
	rxen <= mem(8)(4);
	reset <= mem(8)(5);
	
	--0x9, 0xA, 0xB, 0xC
	txdds_fcw <= mem(12)(2 downto 0) & mem(11) & mem(10) & mem(9);
	--txdds_fcw(7 downto 0) <= mem(9);
	txdds_fcw_upd <= mem(12)(3);

	
end spi_mod_arch;
