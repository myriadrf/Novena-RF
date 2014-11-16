--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   12:23:12 07/11/2014
-- Design Name:   
-- Module Name:   D:/LimeMicrosystems/xilinx/projects/novena_try/ipcore_dir/dds/dds_tb.vhd
-- Project Name:  novena_try
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: dds
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY dds_tb IS
END dds_tb;
 
ARCHITECTURE behavior OF dds_tb IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
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
    

   --Inputs
   signal ce : std_logic := '1';
   signal clk : std_logic := '0';
   signal we : std_logic := '0';
   signal data : std_logic_vector(26 downto 0) := (others => '0');

 	--Outputs
   signal rdy : std_logic;
   signal cosine : std_logic_vector(11 downto 0);
   signal sine : std_logic_vector(11 downto 0);

   -- Clock period definitions
   constant clk_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: dds PORT MAP (
          ce => ce,
          clk => clk,
          we => we,
          data => data,
          rdy => rdy,
          cosine => cosine,
          sine => sine
        );

   -- Clock process definitions
   clk_process :process
   begin
		clk <= '0';
		wait for clk_period/2;
		clk <= '1';
		wait for clk_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for clk_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
