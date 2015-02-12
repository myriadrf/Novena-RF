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
-- You must compile the wrapper file stream_fifo16_xclk.vhd when simulating
-- the core, stream_fifo16_xclk. When compiling the wrapper file, be sure to
-- reference the XilinxCoreLib VHDL simulation library. For detailed
-- instructions, please refer to the "CORE Generator Help".

-- The synthesis directives "translate_off/translate_on" specified
-- below are supported by Xilinx, Mentor Graphics and Synplicity
-- synthesis tools. Ensure they are correct for your synthesis tool(s).

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
-- synthesis translate_off
LIBRARY XilinxCoreLib;
-- synthesis translate_on
ENTITY stream_fifo16_xclk IS
  PORT (
    m_aclk : IN STD_LOGIC;
    s_aclk : IN STD_LOGIC;
    s_aresetn : IN STD_LOGIC;
    s_axis_tvalid : IN STD_LOGIC;
    s_axis_tready : OUT STD_LOGIC;
    s_axis_tdata : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    m_axis_tvalid : OUT STD_LOGIC;
    m_axis_tready : IN STD_LOGIC;
    m_axis_tdata : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END stream_fifo16_xclk;

ARCHITECTURE stream_fifo16_xclk_a OF stream_fifo16_xclk IS
-- synthesis translate_off
COMPONENT wrapped_stream_fifo16_xclk
  PORT (
    m_aclk : IN STD_LOGIC;
    s_aclk : IN STD_LOGIC;
    s_aresetn : IN STD_LOGIC;
    s_axis_tvalid : IN STD_LOGIC;
    s_axis_tready : OUT STD_LOGIC;
    s_axis_tdata : IN STD_LOGIC_VECTOR(15 DOWNTO 0);
    m_axis_tvalid : OUT STD_LOGIC;
    m_axis_tready : IN STD_LOGIC;
    m_axis_tdata : OUT STD_LOGIC_VECTOR(15 DOWNTO 0)
  );
END COMPONENT;

-- Configuration specification
  FOR ALL : wrapped_stream_fifo16_xclk USE ENTITY XilinxCoreLib.fifo_generator_v9_3(behavioral)
    GENERIC MAP (
      c_add_ngc_constraint => 0,
      c_application_type_axis => 0,
      c_application_type_rach => 0,
      c_application_type_rdch => 0,
      c_application_type_wach => 0,
      c_application_type_wdch => 0,
      c_application_type_wrch => 0,
      c_axi_addr_width => 32,
      c_axi_aruser_width => 1,
      c_axi_awuser_width => 1,
      c_axi_buser_width => 1,
      c_axi_data_width => 64,
      c_axi_id_width => 4,
      c_axi_ruser_width => 1,
      c_axi_type => 0,
      c_axi_wuser_width => 1,
      c_axis_tdata_width => 16,
      c_axis_tdest_width => 4,
      c_axis_tid_width => 8,
      c_axis_tkeep_width => 2,
      c_axis_tstrb_width => 2,
      c_axis_tuser_width => 4,
      c_axis_type => 0,
      c_common_clock => 0,
      c_count_type => 0,
      c_data_count_width => 10,
      c_default_value => "BlankString",
      c_din_width => 18,
      c_din_width_axis => 16,
      c_din_width_rach => 32,
      c_din_width_rdch => 64,
      c_din_width_wach => 32,
      c_din_width_wdch => 64,
      c_din_width_wrch => 2,
      c_dout_rst_val => "0",
      c_dout_width => 18,
      c_enable_rlocs => 0,
      c_enable_rst_sync => 1,
      c_error_injection_type => 0,
      c_error_injection_type_axis => 0,
      c_error_injection_type_rach => 0,
      c_error_injection_type_rdch => 0,
      c_error_injection_type_wach => 0,
      c_error_injection_type_wdch => 0,
      c_error_injection_type_wrch => 0,
      c_family => "spartan6",
      c_full_flags_rst_val => 1,
      c_has_almost_empty => 0,
      c_has_almost_full => 0,
      c_has_axi_aruser => 0,
      c_has_axi_awuser => 0,
      c_has_axi_buser => 0,
      c_has_axi_rd_channel => 0,
      c_has_axi_ruser => 0,
      c_has_axi_wr_channel => 0,
      c_has_axi_wuser => 0,
      c_has_axis_tdata => 1,
      c_has_axis_tdest => 0,
      c_has_axis_tid => 0,
      c_has_axis_tkeep => 0,
      c_has_axis_tlast => 0,
      c_has_axis_tready => 1,
      c_has_axis_tstrb => 0,
      c_has_axis_tuser => 0,
      c_has_backup => 0,
      c_has_data_count => 0,
      c_has_data_counts_axis => 0,
      c_has_data_counts_rach => 0,
      c_has_data_counts_rdch => 0,
      c_has_data_counts_wach => 0,
      c_has_data_counts_wdch => 0,
      c_has_data_counts_wrch => 0,
      c_has_int_clk => 0,
      c_has_master_ce => 0,
      c_has_meminit_file => 0,
      c_has_overflow => 0,
      c_has_prog_flags_axis => 0,
      c_has_prog_flags_rach => 0,
      c_has_prog_flags_rdch => 0,
      c_has_prog_flags_wach => 0,
      c_has_prog_flags_wdch => 0,
      c_has_prog_flags_wrch => 0,
      c_has_rd_data_count => 0,
      c_has_rd_rst => 0,
      c_has_rst => 1,
      c_has_slave_ce => 0,
      c_has_srst => 0,
      c_has_underflow => 0,
      c_has_valid => 0,
      c_has_wr_ack => 0,
      c_has_wr_data_count => 0,
      c_has_wr_rst => 0,
      c_implementation_type => 0,
      c_implementation_type_axis => 11,
      c_implementation_type_rach => 12,
      c_implementation_type_rdch => 11,
      c_implementation_type_wach => 12,
      c_implementation_type_wdch => 11,
      c_implementation_type_wrch => 12,
      c_init_wr_pntr_val => 0,
      c_interface_type => 1,
      c_memory_type => 1,
      c_mif_file_name => "BlankString",
      c_msgon_val => 0,
      c_optimization_mode => 0,
      c_overflow_low => 0,
      c_preload_latency => 1,
      c_preload_regs => 0,
      c_prim_fifo_type => "4kx4",
      c_prog_empty_thresh_assert_val => 2,
      c_prog_empty_thresh_assert_val_axis => 13,
      c_prog_empty_thresh_assert_val_rach => 13,
      c_prog_empty_thresh_assert_val_rdch => 1021,
      c_prog_empty_thresh_assert_val_wach => 13,
      c_prog_empty_thresh_assert_val_wdch => 1021,
      c_prog_empty_thresh_assert_val_wrch => 13,
      c_prog_empty_thresh_negate_val => 3,
      c_prog_empty_type => 0,
      c_prog_empty_type_axis => 0,
      c_prog_empty_type_rach => 0,
      c_prog_empty_type_rdch => 0,
      c_prog_empty_type_wach => 0,
      c_prog_empty_type_wdch => 0,
      c_prog_empty_type_wrch => 0,
      c_prog_full_thresh_assert_val => 1021,
      c_prog_full_thresh_assert_val_axis => 15,
      c_prog_full_thresh_assert_val_rach => 15,
      c_prog_full_thresh_assert_val_rdch => 1023,
      c_prog_full_thresh_assert_val_wach => 15,
      c_prog_full_thresh_assert_val_wdch => 1023,
      c_prog_full_thresh_assert_val_wrch => 15,
      c_prog_full_thresh_negate_val => 1020,
      c_prog_full_type => 0,
      c_prog_full_type_axis => 0,
      c_prog_full_type_rach => 0,
      c_prog_full_type_rdch => 0,
      c_prog_full_type_wach => 0,
      c_prog_full_type_wdch => 0,
      c_prog_full_type_wrch => 0,
      c_rach_type => 0,
      c_rd_data_count_width => 10,
      c_rd_depth => 1024,
      c_rd_freq => 1,
      c_rd_pntr_width => 10,
      c_rdch_type => 0,
      c_reg_slice_mode_axis => 0,
      c_reg_slice_mode_rach => 0,
      c_reg_slice_mode_rdch => 0,
      c_reg_slice_mode_wach => 0,
      c_reg_slice_mode_wdch => 0,
      c_reg_slice_mode_wrch => 0,
      c_synchronizer_stage => 2,
      c_underflow_low => 0,
      c_use_common_overflow => 0,
      c_use_common_underflow => 0,
      c_use_default_settings => 0,
      c_use_dout_rst => 1,
      c_use_ecc => 0,
      c_use_ecc_axis => 0,
      c_use_ecc_rach => 0,
      c_use_ecc_rdch => 0,
      c_use_ecc_wach => 0,
      c_use_ecc_wdch => 0,
      c_use_ecc_wrch => 0,
      c_use_embedded_reg => 0,
      c_use_fifo16_flags => 0,
      c_use_fwft_data_count => 0,
      c_valid_low => 0,
      c_wach_type => 0,
      c_wdch_type => 0,
      c_wr_ack_low => 0,
      c_wr_data_count_width => 10,
      c_wr_depth => 1024,
      c_wr_depth_axis => 16,
      c_wr_depth_rach => 16,
      c_wr_depth_rdch => 1024,
      c_wr_depth_wach => 16,
      c_wr_depth_wdch => 1024,
      c_wr_depth_wrch => 16,
      c_wr_freq => 1,
      c_wr_pntr_width => 10,
      c_wr_pntr_width_axis => 4,
      c_wr_pntr_width_rach => 4,
      c_wr_pntr_width_rdch => 10,
      c_wr_pntr_width_wach => 4,
      c_wr_pntr_width_wdch => 10,
      c_wr_pntr_width_wrch => 4,
      c_wr_response_latency => 1,
      c_wrch_type => 0
    );
-- synthesis translate_on
BEGIN
-- synthesis translate_off
U0 : wrapped_stream_fifo16_xclk
  PORT MAP (
    m_aclk => m_aclk,
    s_aclk => s_aclk,
    s_aresetn => s_aresetn,
    s_axis_tvalid => s_axis_tvalid,
    s_axis_tready => s_axis_tready,
    s_axis_tdata => s_axis_tdata,
    m_axis_tvalid => m_axis_tvalid,
    m_axis_tready => m_axis_tready,
    m_axis_tdata => m_axis_tdata
  );
-- synthesis translate_on

END stream_fifo16_xclk_a;
