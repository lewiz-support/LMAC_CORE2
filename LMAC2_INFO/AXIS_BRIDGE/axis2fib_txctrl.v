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

`timescale 1ns / 1ns

module axis2fib_txctrl (
	clk,						//i-1, 322MHz
	reset_,        				//i-1
                            	
	//Main Signals		    	
	tx_mac_aclk, 				//i-1, TX clock.                                     
	tx_axis_mac_tdata,			//i-DATA_WIDTH, Write data.                          
	tx_axis_mac_tvalid,			//i-1, Signal to show if the data is valid.          
	tx_axis_mac_tlast,			//i-1, Signal to show the last data byte or quadword.
	tx_axis_mac_tuser,			//i-1, Error signal.                                 
	tx_axis_mac_tstrb,			//i-8, To show how many bytes of the data is valid.  
	tx_axis_mac_tready,			//o-1, Indicates if the slave is ready.              
	                        	
	//Sideband Signals	    	
	tx_ifg_delay,				//i-1, Control signal for configurable interframe gap                                                           
	tx_collision,				//o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	tx_retransmit,				//o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	tx_statistics_vector,   	//o-32,A statistics vector that gives information on the last frame transmitted.                                
	tx_statistics_valid,		//o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.                
	                			
	//BCNT to txwbcnt_fifo  	
	wr2_txwbcnt_fifo,			//o-16, wbcnt value 
	txwbcnt_wrreq, 				//o-1, request to write to wr_fifo in bridge		
	txwbcnt_wrempty,  			//i-1, write data fifo in bridge is empty
	txwbcnt_wrfull,				//i-1, indicates wr_fifo is full
	txwbcnt_wrusedw,			//i-4, wrusedw -number of locations filled in fifo	
	                        	
	//DATA to txdata_fifo   	
	wr2_txdata_fifo,			//o-64, write data to wr_fifo in bridge		
	txdata_wrreq, 				//o-1, request to write to wr_fifo in bridge		
	txdata_wrempty,  			//i-1, write data fifo in bridge is empty
	txdata_wrfull,				//i-1, indicates wr_fifo is full
	txdata_wrusedw,				//i-4, wrusedw -number of locations filled in fifo	
			                	
	test						//o-1 debug

	);

	parameter 				ADDR_WIDTH  = 32;						//default
	parameter 				DATA_WIDTH 	= 64;
	parameter 				DATA_PTR 	= 8;
	parameter 				BCNT_WIDTH 	= 32;
	parameter 				BCNT_PTR 	= 2;
	
	input      								clk;			   		//i-1, 322MHz
	input      								reset_;             	//i-1
	
	//Main Signals		
	input									tx_mac_aclk; 			//i-1, TX clock.                                     
	input		[DATA_WIDTH-1 : 0]			tx_axis_mac_tdata;		//i-DATA_WIDTH, Write data.                          
	input									tx_axis_mac_tvalid;		//i-1, Signal to show if the data is valid.          
	input									tx_axis_mac_tlast;		//i-1, Signal to show the last data byte or quadword.
	input									tx_axis_mac_tuser;		//i-1, Error signal.                                 
	input		[ 7 : 0]					tx_axis_mac_tstrb;		//i-8, To show how many bytes of the data is valid.  
	output	reg								tx_axis_mac_tready;		//o-1, Indicates if the slave is ready.              
	
	//Sideband Signals	
	input									tx_ifg_delay;			//i-1, Control signal for configurable interframe gap                                                           
	output	reg								tx_collision;			//o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	output	reg								tx_retransmit;			//o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	output	reg	[31 : 0]					tx_statistics_vector;   //o-32,A statistics vector that gives information on the last frame transmitted.                                
	output	reg								tx_statistics_valid;	//o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.                
	
	//wbcnt to txwbcnt_fifo
	output 	reg	[BCNT_WIDTH-1 :0]	    	wr2_txwbcnt_fifo;		//0-16, wbcnt value                   
	output 	reg								txwbcnt_wrreq; 			//o-1, request to write to wr_fifo in bridge		
	input									txwbcnt_wrempty; 		//i-1, write data fifo in bridge is empty
	input									txwbcnt_wrfull;			//i-1, indicates wr_fifo is full
	input		[BCNT_PTR :0]				txwbcnt_wrusedw;		//i-4,  wrusedw -number of locations filled in fifo
		
	//data to txdata_fifo                
	output reg 	[DATA_WIDTH-1 : 0] 			wr2_txdata_fifo;		//o-64, write data to wr_fifo in bridge	
	input      								txdata_wrempty;     	//i-1, write data fifo in bridge is empty 
	output reg								txdata_wrreq;			//o-1, request to write to wr_fifo in bridge
	input									txdata_wrfull;			//i-1, indicates wr_fifo is full
	input		[DATA_PTR : 0]				txdata_wrusedw;			//i-4,  wrusedw -number of locations filled in fifo
	
	output 	  								test;					//o-1 debug
	
	reg 									wr_done;
	
	reg			[BCNT_WIDTH-1 : 0]	    	bcnt;                

	//=========== MAIN SM ===============
	//State Machine for Write
	reg		[3:0] 	axis_wr_state;
	
	wire			axis_wr_idle_st;
	wire			axis_wr_data_st;
	wire			axis_wr_side_st;
	wire			axis_wr_done_st;
		
	parameter [3:0]       
			AXIS_WR_IDLE		= 	4'h1,  
			AXIS_WR_DATA		= 	4'h2, 
			AXIS_WR_SIDE	    = 	4'h4,		
			AXIS_WR_DONE		= 	4'h8;    
		
	assign	axis_wr_idle_st  = 	axis_wr_state[0];   
	assign  axis_wr_data_st  = 	axis_wr_state[1];             
	assign	axis_wr_side_st	 = 	axis_wr_state[2];   
	assign	axis_wr_done_st  = 	axis_wr_state[3];
	    
	
	assign	test = 1'b0;
	
	
	always @ (posedge tx_mac_aclk)
	begin
	
		if (!reset_)
		begin
			//reset
			tx_axis_mac_tready	<=	1'b0;
			wr_done				<=	1'b0;
			bcnt				<=	32'd0;
			txdata_wrreq		<=	1'b0;
			txwbcnt_wrreq		<=	1'b0;
			wr2_txdata_fifo		<=	tx_axis_mac_tdata;
			wr2_txwbcnt_fifo	<=	32'd0;
			
			tx_collision			<=	1'b0;
			tx_retransmit			<=	1'b0;
			tx_statistics_vector	<=	32'b0;   
			tx_statistics_valid		<=	1'b0;
		
		end
		
		else if (axis_wr_idle_st)
		begin
			//initialize in IDLE
			tx_axis_mac_tready	<=	1'b0;
			wr_done				<=	1'b0;
			bcnt				<=	32'd0;
			txdata_wrreq		<=	1'b0;
			txwbcnt_wrreq		<=	1'b0;
			wr2_txdata_fifo		<=	tx_axis_mac_tdata;
			wr2_txwbcnt_fifo	<=	32'd0;
		
		end
		
		else if (axis_wr_data_st)
		begin
			//if valid signal is high and fifo is empty then ready is high
			tx_axis_mac_tready	<=	(!tx_axis_mac_tready && tx_axis_mac_tvalid && txdata_wrempty)?	1'b1	:
										(tx_axis_mac_tready	&& tx_axis_mac_tlast)?	1'b0	:	tx_axis_mac_tready;	//if last comes, make ready low
			
			//calculate bcnt														
			if (tx_axis_mac_tready	&&	tx_axis_mac_tvalid) begin
			
				case (tx_axis_mac_tstrb)
				
					8'h01 	: 	bcnt	<=	bcnt + 32'd1;
					8'h03 	:	bcnt	<=	bcnt + 32'd2;
					8'h07 	:	bcnt	<=	bcnt + 32'd3;
					8'h0f 	:	bcnt	<=	bcnt + 32'd4;
					8'h1f 	:	bcnt	<=	bcnt + 32'd5;
					8'h3f 	:	bcnt	<=	bcnt + 32'd6;
					8'h7f 	:	bcnt	<=	bcnt + 32'd7;
					8'hff 	:	bcnt	<=	bcnt + 32'd8;
					default	:	bcnt	<=	bcnt + 32'd0;
				
				endcase
			
			end	
			
			
			txdata_wrreq	<=	(tx_axis_mac_tready	&&	tx_axis_mac_tvalid && !txdata_wrfull)?	1'b1	: 
									1'b0;
			//if ready and valid is high, write data to the fifo						
			wr2_txdata_fifo	<=	(tx_axis_mac_tready	&&	tx_axis_mac_tvalid && !txdata_wrfull)?	tx_axis_mac_tdata	:  					
									wr2_txdata_fifo;	
														
		end
		
		else if (axis_wr_side_st)
		begin
		
			txwbcnt_wrreq		<=	(txwbcnt_wrempty & !txwbcnt_wrreq)?	1'b1	:	1'b0;
			wr2_txwbcnt_fifo	<=	(txwbcnt_wrempty)?	bcnt	:	wr2_txwbcnt_fifo;	
		
			txdata_wrreq		<=	1'b0; 

			wr_done				<=	1'b1;
		
		end
		
		else if (axis_wr_done_st)
		begin
		
			wr_done				<=	1'b0;
		
		end

	
	end
	
	    
	
	//State Machine for Write
	always @ (posedge tx_mac_aclk)           
	begin             
	               	                                
		if (!reset_)         
		begin   
		                       
			axis_wr_state	<= AXIS_WR_IDLE ; 
		     
		end  
		                          
		else                            
		begin                          
		                               
			if (axis_wr_idle_st)              
					axis_wr_state 	<=	AXIS_WR_DATA;                            
					                             					                             
			if (axis_wr_data_st)              
					axis_wr_state 	<= 
					(tx_axis_mac_tlast) ? AXIS_WR_SIDE : AXIS_WR_DATA;  
											
			if (axis_wr_side_st)	//sideband signals not used                          
					axis_wr_state 	<=                         						
					(wr_done) ? AXIS_WR_DONE : AXIS_WR_SIDE;		
			 
			if (axis_wr_done_st)                          		
					axis_wr_state 	<= AXIS_WR_IDLE;                       	  		
		 			    									                          		                             
		end                 
	                                
	end		

	//============== Simulation ONLY =======================//
	//synopsys translate_off                                  
		                                                         
	reg [64*8-1:0] ascii_axis_wr_state;                          
	                                                          
	always@(axis_wr_state)                                       
	begin                                                     
		case(axis_wr_state)                                         
	    AXIS_WR_IDLE		:  	ascii_axis_wr_state = "AXIS_WR_IDLE";        
		AXIS_WR_DATA		:  	ascii_axis_wr_state = "AXIS_WR_DATA";          
		AXIS_WR_SIDE		:  	ascii_axis_wr_state = "AXIS_WR_SIDE";            
		AXIS_WR_DONE		:   ascii_axis_wr_state = "AXIS_WR_DONE";
		endcase                                                  
	end                                                       
	                                                          
	//synopsys translate_on                               
	    
endmodule	