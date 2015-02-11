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
--    (c) Copyright 1995-2015 Xilinx, Inc.                                    --
--    All rights reserved.                                                    --
--------------------------------------------------------------------------------

--------------------------------------------------------------------------------
--    Generated from core with identifier: xilinx.com:ip:fir_compiler:6.3     --
--                                                                            --
--    The Xilinx FIR Compiler LogiCORE is a module for generation of high     --
--    speed, compact filter implementations that can be configured to         --
--    implement many different filtering functions. The core is fully         --
--    synchronous, using a single clock, and is highly parameterizable,       --
--    allowing designers to control the filter type, data and coefficient     --
--    widths, the number of filter taps, the number of channels, etc.         --
--    Multi-rate operation is supported. The core is delivered through the    --
--    Xilinx CORE Generator System and integrates seamlessly with the         --
--    Xilinx design flow.                                                     --
--------------------------------------------------------------------------------

-- Interfaces:
--    event_s_data_tlast_missing_intf
--    event_s_data_tlast_unexpected_intf
--    event_s_data_chanid_incorrect_intf
--    event_s_config_tlast_missing_intf
--    event_s_config_tlast_unexpected_intf
--    event_s_reload_tlast_missing_intf
--    event_s_reload_tlast_unexpected_intf
--    S_AXIS_RELOAD
--    aclk_intf
--    aresetn_intf
--    aclken_intf
--    S_AXIS_DATA
--    M_AXIS_DATA
--    S_AXIS_CONFIG

-- The following code must appear in the VHDL architecture header:

------------- Begin Cut here for COMPONENT Declaration ------ COMP_TAG
COMPONENT half_band_interp
  PORT (
    aclk : IN STD_LOGIC;
    s_axis_data_tvalid : IN STD_LOGIC;
    s_axis_data_tready : OUT STD_LOGIC;
    s_axis_data_tdata : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axis_data_tvalid : OUT STD_LOGIC;
    m_axis_data_tready : IN STD_LOGIC;
    m_axis_data_tdata : OUT STD_LOGIC_VECTOR(31 DOWNTO 0)
  );
END COMPONENT;
-- COMP_TAG_END ------ End COMPONENT Declaration ------------

-- The following code must appear in the VHDL architecture
-- body. Substitute your own instance name and net names.

------------- Begin Cut here for INSTANTIATION Template ----- INST_TAG
your_instance_name : half_band_interp
  PORT MAP (
    aclk => aclk,
    s_axis_data_tvalid => s_axis_data_tvalid,
    s_axis_data_tready => s_axis_data_tready,
    s_axis_data_tdata => s_axis_data_tdata,
    m_axis_data_tvalid => m_axis_data_tvalid,
    m_axis_data_tready => m_axis_data_tready,
    m_axis_data_tdata => m_axis_data_tdata
  );
-- INST_TAG_END ------ End INSTANTIATION Template ------------

-- You must compile the wrapper file half_band_interp.vhd when simulating
-- the core, half_band_interp. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

