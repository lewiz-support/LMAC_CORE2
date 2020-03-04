//
// Copyright (C) 2018 LeWiz Communications, Inc. 
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.
// 
// You should have received a copy of the GNU Lesser General Public
// License along with this library release; if not, write to the Free Software
// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
// 
// LeWiz can be contacted at:  support@lewiz.com
// or address:  
// PO Box 9276
// San Jose, CA 95157-9276
// www.lewiz.com
// 
//    Author: LeWiz Communications, Inc.
//    Language: Verilog
//

// synopsys translate_off
`timescale 1ns/10ps
// synopsys translate_on

module LMAC_SYNTH (

    input              clk,                //i-1, clk
    input              reset_,             //i-1, reset_

    // Interface to TX PATH
	input              tx_mac_wr,          // i-1
	(* KEEP = "TRUE" *) input  [63 : 0]    tx_mac_data,		   // i-64
	output	           tx_mac_full,		   // o-1
    output [12 : 0]    tx_mac_usedw,       // o-13
		
    // Interface to RX PATH
    (* KEEP = "TRUE" *) output [63 : 0]	   rx_mac_data,
    output [ 7 : 0]	   rx_mac_ctrl,
    output 			   rx_mac_empty,
    input			   rx_mac_rd,

    //for pattern search (I/F to RX Path/EXTR)
    input		       cs_fifo_rd_en,		//i-1
    output		       cs_fifo_empty,		//o-1

    output [63 : 0]	   ipcs_fifo_dout,		

    //input			   xgmii_reset_,		//i-1   
    (* KEEP = "TRUE" *) output [63 : 0]    xgmii_txd,			//o-64
    (* KEEP = "TRUE" *) output [ 7 : 0]    xgmii_txc,			//o-8
    (* KEEP = "TRUE" *) input  [63 : 0]    xgmii_rxd,			//i-64
    (* KEEP = "TRUE" *) input  [ 7 : 0]    xgmii_rxc,			//i-8
    //input[ 1 : 0]    xgmii_led_,		    //i-2

    output		       xauiA_linkup,		// to LED on board 
        
    // From central decoder
    input  [15 : 0]	   host_addr_reg,
    input  [ 3 : 0]	   SYS_ADDR,
            
    // From mac_register
    input			   fail_over,
    input  [31 : 0]	   fmac_ctrl,
    input  [31 : 0]	   fmac_ctrl1,

    input			   fmac_rxd_en	,

    input  [31 : 0]	   mac_pause_value,		// [31:16] = tx_pause_value to send a pause frame, [15:0] = rx_pause_value (not implement)
    input  [47 : 0]	   mac_addr0,			// mac_addr to check in non-promiscuous mode

    input			   reg_rd_start,

    output			   reg_rd_done_out,		

            
    output [31 : 0]	   FMAC_REGDOUT,
    output			   FIFO_OV_IPEND,
    input [2:0] 		fmac_speed

);

reg 		mode_1G 	;
reg 		mode_2p5G  	;
reg 		mode_5G  	;
reg 		mode_10G  	;


	always@(posedge clk)
		begin
			case (fmac_speed)
			
			3'b001: begin
					mode_1G    <= 1'b1;
					mode_2p5G  <= 1'b0;
					mode_5G    <= 1'b0;
					mode_10G   <= 1'b0;
			
					end
			3'b010: begin
					mode_1G    <= 1'b0;
					mode_2p5G  <= 1'b1;
					mode_5G    <= 1'b1;
					mode_10G   <= 1'b0;
				
					end
			3'b101: begin
					mode_1G    <= 1'b0;
					mode_2p5G  <= 1'b0;
					mode_5G    <= 1'b1;
					mode_10G   <= 1'b0;
				
					end
			default: begin
					mode_1G    <= 1'b0;
					mode_2p5G  <= 1'b0;
					mode_5G    <= 1'b0;
					mode_10G   <= 1'b1;
					
					end
			endcase
		end
		

LMAC_CORE_TOP LMAC_CORE_TOP	(
		
		// Clocks and Reset
		.clk              (clk),					// i-1		250 Mhz		// changed to 156.25 MHz- 7 june 2018		
		.xA_clk           (clk),					// i-1		156.25 Mhz
		.reset_           (reset_),					// i-1, FMAC specific reset (also follows PCIE RST)		
		                    	
		.mode_10G         (mode_10G),  	      	 		//i-1, speed modes: 10G selected
		.mode_5G          (mode_5G),   				//i-1, 
		.mode_2p5G        (mode_2p5G),      				//i-1, 
		.mode_1G          (mode_1G),   				//i-1, 
		                		
		.TCORE_MODE	      (1'b0),			        //i-1,	   

		// Interface to TX PATH
		.tx_mac_wr        (tx_mac_wr),				// i-1
		.tx_mac_data      (tx_mac_data),			// i-64
		.tx_mac_full      (tx_mac_full),			// o-1
		.tx_mac_usedw     (tx_mac_usedw),			// o-13
		
		// Interface to RX PATH
		.rx_mac_data      (rx_mac_data),			// o-64
		.rx_mac_ctrl      (rx_mac_ctrl),			// o-8, rsvd, pkt_end, pkt_start
		.rx_mac_empty     (rx_mac_empty),			// o-1
		.rx_mac_rd        (rx_mac_rd),				// i-1
		
		//for field debug   	
		.rx_mac_full_dbg  (),		            //o-1
		.rx_mac_usedw_dbg (),		            //o-12
		
		//for pre_CS/parser (I/F to RX Path/EXTR)
		.cs_fifo_rd_en 	  (cs_fifo_rd_en),		//i-1
		.cs_fifo_empty 	  (cs_fifo_empty),		//o-1
		.ipcs_fifo_dout	  (ipcs_fifo_dout),	    //o-64
		
		// Xaui/PHY A Interface
		.xgmii_reset_     (1'b0),    		    //i-1
        .xgmii_txd        (xgmii_txd),			//o-64
        .xgmii_txc        (xgmii_txc),			//o-8
        
		.xgmii_rxd	      (xgmii_rxd),			//i-64
        .xgmii_rxc        (xgmii_rxc),			//i-8
        .xgmii_led_       (2'b0),			    //i-2
		
		.xauiA_linkup     (xauiA_linkup),       // o-1, link up for either 10G or 10G mode 
		
		// From central decoder
		.host_addr_reg    (host_addr_reg),   	// i-16
		.SYS_ADDR         (SYS_ADDR),			//i-4, system assigned addr for the FMAC
		
		// From mac_register
		.fail_over        (fail_over),			// i-1
		.fmac_ctrl        (fmac_ctrl),			// i-32
		.fmac_ctrl1       (fmac_ctrl1),			// i-32
		                    	
		.fmac_rxd_en      (fmac_rxd_en),		//i-1, 13jul11
		
		.mac_pause_value  (mac_pause_value),	// i-32
		.mac_addr0        (mac_addr0),    		// i-48
		
		.reg_rd_start     (reg_rd_start),		// i-1	
				
		.reg_rd_done_out  (reg_rd_done_out),	// o-1		
		                    	
		.FMAC_REGDOUT     (FMAC_REGDOUT),		// o-32
		.FIFO_OV_IPEND    (FIFO_OV_IPEND)		// o-1
		
		);

		
endmodule
