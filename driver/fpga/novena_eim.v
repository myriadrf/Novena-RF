//////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013, Andrew "bunnie" Huang
//
// See the NOTICE file distributed with this work for additional 
// information regarding copyright ownership.  The copyright holder 
// licenses this file to you under the Apache License, Version 2.0 
// (the "License"); you may not use this file except in compliance
// with the License.  You may obtain a copy of the License at
//
//   http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing,
// code distributed under the License is distributed on an
// "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied.  See the License for the
// specific language governing permissions and limitations
// under the License.
//////////////////////////////////////////////////////////////////////////////
`timescale 1ns / 1ps

module novena_eim(
    input wire EIM_BCLK,
    input wire [1:0] EIM_CS,
    inout wire [15:0] EIM_DA,
    input wire [18:16] EIM_A,
    input wire EIM_LBA,
    input wire EIM_OE,
    input wire EIM_RW,
    output reg EIM_WAIT,

    input wire CLK2_N,	//
    input wire CLK2_P,	// 50MHz clock diff input
    input wire RESETBMCU,

    //clock synchronous interfaces
    output wire bus_clk,
    output wire [15:0] bus_data_wr,
    input wire [15:0] bus_data_rd,
    output wire [18:0] bus_addr,
    output wire bus_sel, //active cycle
    output wire bus_wr //write=1, read=0
);

	wire [15:0] dout;

	reg [23:0] 	counter; 
	 
	wire 	      bclk_i, bclk_o;
	wire 	      i_fbk_out, i_fbk_in;
	wire 	      o_fbk_out, o_fbk_in;
	 

	wire [15:0] 	eim_dout;
	wire [15:0] 	eim_din;
	wire 		      clk;   // free-runs at 50 MHz, unbuffered
	wire 		      bclk;  // NOTE: doesn't run until first CPU access to EIM; then free-runs at 133 MHz

   
	wire 		      reset;

	wire 	      bclk_dll, bclk_locked;

	
	assign bclk_dll_pin = bclk_dll;

   
	reg 		    cs0_r, rw_r;
	reg [15:0] 	din_r;
	reg [18:0] 	bus_addr_r;
	reg 		    adv_r;

	reg 		    cs0_in, rw_in, adv_in, cs1_in;
	reg [15:0] 	din_in;
	reg [2:0]		a_in;
	reg 		    oe_in;


	always @(posedge bclk_i) begin
      cs0_in <= EIM_CS[0];
      rw_in <= EIM_RW;
      din_in <= eim_din;
      adv_in <= !EIM_LBA; // latch address on LBA low
      a_in <= EIM_A[18:16];
      cs1_in <= EIM_CS[1];
      oe_in <= EIM_OE;

      cs0_r <= cs0_in;
      rw_r <= rw_in;
      din_r <= din_in;
      adv_r <= adv_in;
	end
   
	always @(posedge bclk_i) begin 
      if( adv_in ) begin
				bus_addr_r <= {a_in, din_in};
      end 
			else begin
				bus_addr_r <= bus_addr_r;
      end
	end

  //////////////
  // END Read from FIFO and write to EIM related
  //////////////
    reg [15:0] a_count;
    reg [15:0] dout_r;

    assign bus_clk = bclk_i;
    assign dout = dout_r;
    assign bus_data_wr = din_in;
    assign bus_sel = !cs1_in && !adv_in;
    assign bus_wr = !rw_in;
    //show bus_addr stable one cycle early when adv_in for block ram reads
    assign bus_addr = (adv_in == 1'b1)?{a_in, din_in}:{a_in, a_count};
    reg pulse;

    always @(posedge bclk_i) begin 
    	dout_r <= bus_data_rd; //only cross clock domain from register
        EIM_WAIT <= 1; //never wait
	pulse <= !pulse;
        if ( adv_in ) begin
            a_count <= din_in;
        end
        else if (bus_sel) begin
            a_count <= a_count + 2; //2 bytes
        end
    end

/*
    wire [35:0] CONTROL_ILA;
    reg [63:0] DATA_ILA;
    reg [7:0] TRIG_ILA;
    chipscope_icon my_icon(.CONTROL0(CONTROL_ILA));
    chipscope_ila my_ila(.CONTROL(CONTROL_ILA), .DATA(DATA_ILA), .TRIG0(TRIG_ILA), .CLK(bclk_i));

    always @(posedge bclk_i) begin 
        TRIG_ILA[0] <= bus_sel;
        TRIG_ILA[1] <= bus_wr;
        TRIG_ILA[2] <= cs1_in;
        TRIG_ILA[3] <= rw_in;
        TRIG_ILA[4] <= adv_in;
        TRIG_ILA[5] <= oe_in;

        DATA_ILA[15:0] <= bus_data_wr;
        DATA_ILA[31:16] <= bus_addr[15:0];
        DATA_ILA[47:32] <= din_in;
        DATA_ILA[56:54] <= a_in;
        DATA_ILA[57] <= oe_in;
        DATA_ILA[58] <= pulse;
        DATA_ILA[59] <= bus_sel;
        DATA_ILA[60] <= bus_wr;
        DATA_ILA[61] <= cs1_in;
        DATA_ILA[62] <= rw_in;
        DATA_ILA[63] <= adv_in;
    end
*/

  //////////////
  // Output pipeline registers -- explicit instantiation as their LOCs are controlled in the UCF.
  //////////////
  FDSE oddr2_eim0( .D( dout[ 0] ), .C( bclk_o ), .Q( eim_dout[ 0] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim1( .D( dout[ 1] ), .C( bclk_o ), .Q( eim_dout[ 1] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim2( .D( dout[ 2] ), .C( bclk_o ), .Q( eim_dout[ 2] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim3( .D( dout[ 3] ), .C( bclk_o ), .Q( eim_dout[ 3] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim4( .D( dout[ 4] ), .C( bclk_o ), .Q( eim_dout[ 4] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim5( .D( dout[ 5] ), .C( bclk_o ), .Q( eim_dout[ 5] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim6( .D( dout[ 6] ), .C( bclk_o ), .Q( eim_dout[ 6] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim7( .D( dout[ 7] ), .C( bclk_o ), .Q( eim_dout[ 7] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim8( .D( dout[ 8] ), .C( bclk_o ), .Q( eim_dout[ 8] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eim9( .D( dout[ 9] ), .C( bclk_o ), .Q( eim_dout[ 9] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimA( .D( dout[10] ), .C( bclk_o ), .Q( eim_dout[10] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimB( .D( dout[11] ), .C( bclk_o ), .Q( eim_dout[11] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimC( .D( dout[12] ), .C( bclk_o ), .Q( eim_dout[12] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimD( .D( dout[13] ), .C( bclk_o ), .Q( eim_dout[13] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimE( .D( dout[14] ), .C( bclk_o ), .Q( eim_dout[14] ), .CE( 1'b1 ), .S(1'b0) );
  FDSE oddr2_eimF( .D( dout[15] ), .C( bclk_o ), .Q( eim_dout[15] ), .CE( 1'b1 ), .S(1'b0) );
  

	//////////////
	/// "heartbeat" counter
	//////////////
	always @(posedge bclk_i or posedge reset)
	begin
		if (reset) begin 
			counter <= 0;
		end
		else begin
			counter <= counter + 1;
		end;
	end

	assign FPGA_LED2 = counter[23];


	 
	//////////////
	// IOBUFs as required by design
	//////////////
	wire oens, cnten;
	assign oens = EIM_OE | !EIM_LBA;
	//assign cnten = !EIM_CS[1] & EIM_LBA;


  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim0  (.IO(EIM_DA[ 0]), .I(eim_dout[ 0]), .T(oens), .O(eim_din[ 0]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim1  (.IO(EIM_DA[ 1]), .I(eim_dout[ 1]), .T(oens), .O(eim_din[ 1]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim2  (.IO(EIM_DA[ 2]), .I(eim_dout[ 2]), .T(oens), .O(eim_din[ 2]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim3  (.IO(EIM_DA[ 3]), .I(eim_dout[ 3]), .T(oens), .O(eim_din[ 3]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim4  (.IO(EIM_DA[ 4]), .I(eim_dout[ 4]), .T(oens), .O(eim_din[ 4]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim5  (.IO(EIM_DA[ 5]), .I(eim_dout[ 5]), .T(oens), .O(eim_din[ 5]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim6  (.IO(EIM_DA[ 6]), .I(eim_dout[ 6]), .T(oens), .O(eim_din[ 6]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim7  (.IO(EIM_DA[ 7]), .I(eim_dout[ 7]), .T(oens), .O(eim_din[ 7]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim8  (.IO(EIM_DA[ 8]), .I(eim_dout[ 8]), .T(oens), .O(eim_din[ 8]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim9  (.IO(EIM_DA[ 9]), .I(eim_dout[ 9]), .T(oens), .O(eim_din[ 9]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim10 (.IO(EIM_DA[10]), .I(eim_dout[10]), .T(oens), .O(eim_din[10]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim11 (.IO(EIM_DA[11]), .I(eim_dout[11]), .T(oens), .O(eim_din[11]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim12 (.IO(EIM_DA[12]), .I(eim_dout[12]), .T(oens), .O(eim_din[12]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim13 (.IO(EIM_DA[13]), .I(eim_dout[13]), .T(oens), .O(eim_din[13]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim14 (.IO(EIM_DA[14]), .I(eim_dout[14]), .T(oens), .O(eim_din[14]));
  IOBUF #(.DRIVE(12), .SLEW("FAST")) IOBUF_eim15 (.IO(EIM_DA[15]), .I(eim_dout[15]), .T(oens), .O(eim_din[15]));

	//////////////
	// END IOBUFs as required by design
	//////////////	 
	 
	 
	//////////////////////////////////////////////////
	// RESETs
	//////////////////////////////////////////////////	 
	sync_reset master_res_sync( .glbl_reset(!RESETBMCU), .clk(clk), .reset(reset) );
	 
	 
	 
	//////////////////////////////////////////////////
	// CLOCKS
	//////////////////////////////////////////////////
	//////////////
	// IOBUFs as required by design
	//////////////
	IBUFGDS clkibufgds( .I(CLK2_P), .IB(CLK2_N), .O(clk) );
	 
	////////////////////////////////////
	///// BCLK DLL -- generate zero-delay clock plus slower versions for internal use
	////////////////////////////////////
	wire 	      bclk_int_in, bclk_io_in;
	IBUFG   clkibufg (.I(EIM_BCLK), .O(bclk) );
	BUFG    bclk_dll_bufg(.I(bclk), .O(bclk_int_in) );
   
	bclk_dll bclk_dll_mod( .clk133in(bclk_int_in), .clk133(bclk_dll), .RESET(reset), .LOCKED(bclk_locked));

	wire 	      i_locked;
	wire 	      o_locked;

   
	dcm_delay bclk_i_dll( .clk133(bclk_int_in), .clk133out(bclk_i),
			  .CLKFB_IN(i_fbk_in), .CLKFB_OUT(i_fbk_out),
			  .RESET(reset), .LOCKED(i_locked));

	dcm_delay bclk_o_dll( .clk133(bclk_int_in), .clk133out(bclk_o),
			  .CLKFB_IN(o_fbk_in), .CLKFB_OUT(o_fbk_out),
			  .RESET(reset), .LOCKED(o_locked));
   
	// lock it to the input path
	BUFIO2FB bclk_o_fbk(.I(bclk_o), .O(o_fbk_in));
	assign i_fbk_in = bclk_i;

endmodule
