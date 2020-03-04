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

module LPBK_MODULE(

	input				clk,				//i-1
	input				reset_,     		//i-1   					
	
    //Interface to TX PATH
	output reg         	tx_mac_wr,       	//o-1
	(* KEEP = "TRUE" *) output reg [63 : 0] tx_mac_data,		//o-64
	input	           	tx_mac_full,		//i-1
    input  [12 : 0]    	tx_mac_usedw,    	//i-13
		
    //Interface to RX PATH
    (* KEEP = "TRUE" *) input  [63 : 0]	   	rx_mac_data,		//i-64
    input 			   	rx_mac_empty,   	//i-1
    output reg		   	rx_mac_rd,      	//o-1

    //for pattern search (I/F to RX Path/EXTR)
    output reg	       	cs_fifo_rd_en,		//o-1
    input		       	cs_fifo_empty,		//i-1
    input [63 : 0]	   	ipcs_fifo_dout		//i-64		

);


   //State Machine for RX_FIFO
	reg		[3:0] 	rx_fifo_state;
	
	wire			rx_fifo_idle_st;
	wire			rx_fifo_bcnt_st;
	wire			rx_fifo_data_st;
	wire			rx_fifo_done_st;
		
	parameter [3:0]       
			RX_FIFO_IDLE		= 	4'h1,  
			RX_FIFO_BCNT		= 	4'h2, 
			RX_FIFO_DATA	    = 	4'h4,		
			RX_FIFO_DONE		= 	4'h8;    
		
	assign	rx_fifo_idle_st  = 	rx_fifo_state[0];   
	assign  rx_fifo_bcnt_st  = 	rx_fifo_state[1];             
	assign	rx_fifo_data_st	 = 	rx_fifo_state[2];   
	assign	rx_fifo_done_st  = 	rx_fifo_state[3];
	
	//synopsys translate_off                                  
	reg [64*8-1:0] ascii_rx_fifo_state;                          
	                                                          
	always@(rx_fifo_state)                                       
	begin                                                     
		case(rx_fifo_state)                                         
	    RX_FIFO_IDLE		:  	ascii_rx_fifo_state = "RX_FIFO_IDLE";        
		RX_FIFO_BCNT		:  	ascii_rx_fifo_state = "RX_FIFO_BCNT";          
		RX_FIFO_DATA		:  	ascii_rx_fifo_state = "RX_FIFO_DATA";            
		RX_FIFO_DONE		:   ascii_rx_fifo_state = "RX_FIFO_DONE";
		endcase                                                  
	end      
	//synopsys translate_on    
	
	
	//Quad-word count for control logic
	reg		[15 : 0]	byte_count;
	reg					first_data;
	reg					first_qwd;
	reg					second_qwd;
	reg					third_qwd;
	reg					fourth_qwd;
	reg					fifth_qwd;
	reg					sixth_qwd;
    reg		[63 : 0]   	rx_mac_data_dly;
    reg		[63 : 0]   	rx_mac_data_dly1;
	
	always @ (posedge clk) begin
		if(!reset_) begin
			rx_fifo_state		<= RX_FIFO_IDLE;
			cs_fifo_rd_en 		<= 1'b0;
			rx_mac_rd			<= 1'b0;
			byte_count			<= 16'h0;
			
			first_data			<= 1'b0;
			rx_mac_rd			<= 1'b0;
			
			first_qwd			<= 1'b0;
			second_qwd			<= 1'b0;
			third_qwd			<= 1'b0;
			fourth_qwd			<= 1'b0;
			fifth_qwd			<= 1'b0;
			sixth_qwd			<= 1'b0;
			
			rx_mac_data_dly		<= 64'h0;
			rx_mac_data_dly1	<= 64'h0;
			
			tx_mac_data			<= 64'h0;
			tx_mac_wr			<= 1'b0;
		end
		else begin
			if (rx_fifo_idle_st) begin
				rx_fifo_state 	<= 
					((!rx_mac_empty) & (!cs_fifo_empty) & (!tx_mac_full) & (tx_mac_usedw <= 13'h300)) ? RX_FIFO_BCNT : RX_FIFO_IDLE;
					
				cs_fifo_rd_en 	<= 
					((!rx_mac_empty) & (!cs_fifo_empty) & (!tx_mac_full) & (tx_mac_usedw <= 13'h300)) ? 1'b1 : 1'b0;
					
				rx_mac_rd		<= 1'b0;

				first_qwd		<= 1'b0;
				second_qwd		<= 1'b0;
				third_qwd		<= 1'b0;
				fourth_qwd		<= 1'b0;
				fifth_qwd		<= 1'b0;
				sixth_qwd		<= 1'b0;
				
				rx_mac_data_dly		<= 64'h0;
				rx_mac_data_dly1	<= 64'h0;
			
				tx_mac_data		<= 64'h0;
				tx_mac_wr		<= 1'b0;
			end
					                             					                             
			else if (rx_fifo_bcnt_st) begin
				rx_fifo_state 	<= RX_FIFO_DATA;
				
				cs_fifo_rd_en 	<= 1'b0;
				rx_mac_rd		<= 1'b1;
				byte_count		<= 16'h0;
				first_data		<= 1'b1;
			end
											
			else if (rx_fifo_data_st) begin
				rx_fifo_state 	<= 
					((byte_count == 16'h0) & (!first_data)) ? RX_FIFO_DONE	:	RX_FIFO_DATA;
					
				first_data		<= 1'b0;
				byte_count		<= (first_data)?	ipcs_fifo_dout[63:48]	:
										(byte_count >= 16'h8)? (byte_count - 8'h8)	:
										16'h0;
										
				first_qwd		<= (first_data)?	1'b1	:	1'b0;
				second_qwd		<= (first_qwd)?		1'b1	:	1'b0;
				third_qwd		<= (second_qwd)?	1'b1	:	1'b0;
				fourth_qwd		<= (third_qwd)?		1'b1	:	1'b0;
				fifth_qwd		<= (fourth_qwd)?	1'b1	:	1'b0;
				sixth_qwd		<= (fifth_qwd)?		1'b1	:	1'b0;
				
				rx_mac_rd		<= (first_data | ((byte_count > 16'h10) & (!rx_mac_empty)))?	1'b1	:	1'b0;
				
				rx_mac_data_dly		<= rx_mac_data;
				rx_mac_data_dly1	<= rx_mac_data_dly;
									
				tx_mac_data		<= (first_qwd)?		byte_count	:
									(second_qwd)?	{rx_mac_data_dly[15:0], rx_mac_data[31:0], rx_mac_data_dly[63:48]}	:
									(third_qwd)?	{rx_mac_data_dly[63:32], rx_mac_data_dly1[47:16]}	:
									(fourth_qwd)?	rx_mac_data_dly	:
									(fifth_qwd)?	{rx_mac_data_dly[31:16], rx_mac_data[15:0], rx_mac_data_dly[63:48], rx_mac_data_dly[15:0]}	:
									(sixth_qwd)?	{rx_mac_data_dly[63:48], rx_mac_data_dly[31:16], rx_mac_data_dly[47:32], rx_mac_data_dly1[47:32]}	:
									rx_mac_data_dly;
									
				tx_mac_wr		<= (first_qwd)?	1'b1	:
									tx_mac_wr;
			end
			 
			else if (rx_fifo_done_st) begin
				rx_fifo_state 	<= RX_FIFO_IDLE;
				tx_mac_wr		<= 1'b0;
			end
		 
			else
				rx_fifo_state 	<= RX_FIFO_IDLE;
		end	
	end
	
endmodule