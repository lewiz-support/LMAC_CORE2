// Copyright 1986-2015 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2015.4 (win64) Build 1412921 Wed Nov 18 09:43:45 MST 2015
// Date        : Thu Jan 19 09:28:30 2017
// Host        : MANTA-RAY running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/pktctrl_fifo_ip/pktctrl_fifo_ip_stub.v
// Design      : pktctrl_fifo_ip
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7vx690tffg1761-2
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* x_core_info = "fifo_generator_v13_0_1,Vivado 2015.4" *)
module pktctrl_fifo_ip(clk, srst, din, wr_en, rd_en, dout, full, empty, data_count)
/* synthesis syn_black_box black_box_pad_pin="clk,srst,din[7:0],wr_en,rd_en,dout[7:0],full,empty,data_count[11:0]" */;
  input clk;
  input srst;
  input [7:0]din;
  input wr_en;
  input rd_en;
  output [7:0]dout;
  output full;
  output empty;
  output [11:0]data_count;
endmodule
