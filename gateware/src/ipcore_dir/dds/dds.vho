--------------------------------------------------------------------------------
--    This file is owned and controlled by Xilinx and must be used solely     --
--    for design, simulation, implementation and creation of design files     --
--    limited to Xilinx devices or technologies. Use with non-Xilinx          --
--    devices or technologies is expressly prohibited and immediately         --
--    terminates your license.                                                --
--                                                                            --
--    XILINX IS PROVIDING THIS DESIGN, CODE, OR INFORMATION "AS IS" SOLELY    --
--    FOR USE IN DEVELOPING PROGRAMS AND SOLUTIONS FOR XILINX DEVICES.  BY    --
--    PROVIDING THIS DESIGN, CODE, OR INFORMATION AS ONE POSSIBLE             --
--    IMPLEMENTATION OF THIS FEATURE, APPLICATION OR STANDARD, XILINX IS      --
--    MAKING NO REPRESENTATION THAT THIS IMPLEMENTATION IS FREE FROM ANY      --
--    CLAIMS OF INFRINGEMENT, AND YOU ARE RESPONSIBLE FOR OBTAINING ANY       --
--    RIGHTS YOU MAY REQUIRE FOR YOUR IMPLEMENTATION.  XILINX EXPRESSLY       --
--    DISCLAIMS ANY WARRANTY WHATSOEVER WITH RESPECT TO THE ADEQUACY OF THE   --
--    IMPLEMENTATION, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OR          --
--    REPRESENTATIONS THAT THIS IMPLEMENTATION IS FREE FROM CLAIMS OF         --
--    INFRINGEMENT, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A   --
--    PARTICULAR PURPOSE.                                                     --
--                                                                            --
--    Xilinx products are not intended for use in life support appliances,    --
--    devices, or systems.  Use in such applications are expressly            --
--    prohibited.                                                             --
--                                                                            --
--    (c) Copyright 1995-2014 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--    Generated from core with identifier: xilinx.com:ip:dds_compiler:4.0     --
--                                                                            --
--    The Xilinx DDS Compiler LogiCORE provides Direct Digital Synthesizers   --
--    (DDS) and optionally either Phase Generator or Sine/Cosine Lookup       --
--    Table constituent parts as independent cores. The core features sine,   --
--    cosine or quadrature outputs with 3 to 26-bit output sample             --
--    precision. The core supports up to 16 channels by time-sharing the      --
--    sine/cosine table which dramatically reduces the area requirement       --
--    when multiple channels are needed.  Phase Dithering and Taylor Series   --
--    Correction options provide high dynamic range signals using minimal     --
--    FPGA resources. In addition, the core has an optional phase offset      --
--    capability, providing support for multiple synthesizers with            --
--    precisely controlled phase differences.                                 --
--------------------------------------------------------------------------------

-- Interfaces:
--    addr_intf
--    clk_intf
--    sclr_intf
--    ce_intf
--    reg_select_intf
--    we_intf
--    data_intf
--    pinc_in_intf
--    poff_in_intf
--    phase_in_intf
--    rdy_intf
--    rfd_intf
--    channel_intf
--    cosine_intf
--    sine_intf
--    phase_out_intf

-- The following code must appear in the VHDL architecture header:

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT dds
  PORT (
    ce : IN STD_LOGIC;
    clk : IN STD_LOGIC;
    we : IN STD_LOGIC;
    data : IN STD_LOGIC_VECTOR(26 DOWNTO 0);
    rdy : OUT STD_LOGIC;
    cosine : OUT STD_LOGIC_VECTOR(11 DOWNTO 0);
    sine : OUT STD_LOGIC_VECTOR(11 DOWNTO 0)
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : dds
  PORT MAP (
    ce => ce,
    clk => clk,
    we => we,
    data => data,
    rdy => rdy,
    cosine => cosine,
    sine => sine
  );
-- INST_TAG_END ------ End INSTANTIATION Template ------------

-- You must compile the wrapper file dds.vhd when simulating
-- the core, dds. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

