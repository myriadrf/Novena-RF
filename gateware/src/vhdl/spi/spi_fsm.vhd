-- ----------------------------------------------------------------------------	
-- FILE:	fsm.vhd
-- DESCRIPTION:	Finite State Machine for serial interface
-- DATE:	Jul 12, 2014.
-- AUTHOR(s):	Lime Microsystems
-- REVISIONS:
-- ----------------------------------------------------------------------------	

library ieee;
use ieee.std_logic_1164.all;

-- ----------------------------------------------------------------------------
-- Entity declaration
-- ----------------------------------------------------------------------------
entity spi_fsm is
	port (
		address: in std_logic_vector(2 downto 0);		-- Hardware address
		inst_reg: in std_logic_vector(7 downto 0);	-- Instruction register (read only here)
		sclk: in std_logic;													-- Serial clock
		sen: in std_logic;													-- Serial enable
		reset: in std_logic;												-- Reset
		inst_reg_en: out std_logic;									-- Instruction register enable
		din_reg_en: out std_logic;									-- Data in register enable
		dout_reg_sen: out std_logic;								-- Data out register shift enable
		dout_reg_len: out std_logic;								-- Data out register load enable
		mem_we: out std_logic;											-- Memory write enable
		oe: out std_logic														-- Output enable
	);
end spi_fsm;

-- ----------------------------------------------------------------------------
-- Architecture
-- ----------------------------------------------------------------------------
architecture fsm_arch of spi_fsm is
	-- State codes
	constant s0:  std_logic_vector(4 downto 0) := "00000"; -- Reset state
	constant s1:  std_logic_vector(4 downto 0) := "00001";
	constant s2:  std_logic_vector(4 downto 0) := "00010";
	constant s3:  std_logic_vector(4 downto 0) := "00011";
	constant s4:  std_logic_vector(4 downto 0) := "00100";
	constant s5:  std_logic_vector(4 downto 0) := "00101";
	constant s6:  std_logic_vector(4 downto 0) := "00110";
	constant s7:  std_logic_vector(4 downto 0) := "00111";
	constant s8:  std_logic_vector(4 downto 0) := "01000";
	constant s9:  std_logic_vector(4 downto 0) := "01001";
	constant s10: std_logic_vector(4 downto 0) := "01010";
	constant s11: std_logic_vector(4 downto 0) := "01011";
	constant s12: std_logic_vector(4 downto 0) := "01100";
	constant s13: std_logic_vector(4 downto 0) := "01101";
	constant s14: std_logic_vector(4 downto 0) := "01110";
	constant s15: std_logic_vector(4 downto 0) := "01111";
	constant s16: std_logic_vector(4 downto 0) := "10000";
	
	signal state, next_state: std_logic_vector(4 downto 0);
begin
	state_register: process(sclk, reset, sen)
	begin
		if reset = '0' then  -- Async reset
			state <= s0;
		-- Go back to initial state when sen goes high even if
		-- read/write cycle is not finished by user's mistake
		elsif sen = '1' then
			state <= s0;
		elsif sclk'event and sclk = '1' then
			state <= next_state;
		end if;
	end process state_register;

	state_machine: process (state, sen, address, inst_reg)
	begin
		case state is
			when s0 =>
				inst_reg_en <= not sen; 
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s1;
			when s1 =>
				-- 1 instruction bit is in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s2;
			when s2 =>
				-- 2 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s3;
			when s3 =>
				-- 3 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s4;
			when s4 =>
				-- 4 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s5;
			when s5 =>
				-- 5 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s6;
			when s6 =>
				-- 6 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s7;
			when s7 =>
				-- 7 instruction bits are in
				inst_reg_en <= '1';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s8;
			when s8 =>
				-- Instruction register loaded
				inst_reg_en <= '0';
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '1';
					mem_we <= '0';
					oe <= '1';
				else -- Ignore the next 8 cycles, this is not for us
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s9;
			when s9 =>
				-- 1 data bit in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s10;
			when s10 =>
				-- 2 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s11;
			when s11 =>
				-- 3 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s12;
			when s12 =>
				-- 4 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s13;
			when s13 =>
				-- 5 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';					
					oe <= '0';
				end if;
				next_state <= s14;
			when s14 =>
				-- 6 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				end if;
				next_state <= s15;
			when s15 =>
				-- 7 data bits in/out
				inst_reg_en <= '0';	
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					din_reg_en <= '1';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '1';  --//buvo 0
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					din_reg_en <= '0';
					dout_reg_sen <= '1';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '1';
				else 
					din_reg_en <= '0';
					dout_reg_sen <= '0';
					dout_reg_len <= '0';
					mem_we <= '0';
					oe <= '0';
				end if;
				next_state <= s16;
			when s16 =>
				-- 8 data bits in/out
				inst_reg_en <= '1'; 
				din_reg_en <= '0';
				dout_reg_len <= '0';
				if    inst_reg(6 downto 4) = address and inst_reg(7) = '1' then -- Write cycle
					mem_we <= '0'; --//buvo 1
					dout_reg_sen <= '0';
					oe <= '0';
				elsif inst_reg(6 downto 4) = address and inst_reg(7) = '0' then -- Read cycle
					mem_we <= '0';
					dout_reg_sen <= '1';
					oe <= '1';
				else 
					mem_we <= '0';
					dout_reg_sen <= '0';
					oe <= '0';
				end if;
				next_state <= s1;
			when others =>
				-- This will never happen, just to avoid inferred latches in synthesis
				inst_reg_en <= '0';
				din_reg_en <= '0';
				dout_reg_sen <= '0';
				dout_reg_len <= '0';
				mem_we <= '0';
				oe <= '0';
				next_state <= s0;
		end case;
	end process state_machine;	

end fsm_arch;
