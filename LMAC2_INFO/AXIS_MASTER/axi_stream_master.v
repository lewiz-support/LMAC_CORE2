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

module axi_stream_master(

	clk,					//i-1, 250MHz	
	reset_,        			//i-1	
	gen_en_wr,      		//i-1, to initiate the write transaction.	
	
	//Tx Main Signals		
	tx_mac_aclk, 			//i-1, TX clock.
	tx_axis_mac_tdata,	   	//o-DATA_WIDTH, Write data.
	tx_axis_mac_tvalid,	   	//o-1, Signal to show if the data is valid. 
	tx_axis_mac_tlast,	   	//o-1, Signal to show the last data byte or quadword.
	tx_axis_mac_tuser,	   	//o-1, Error signal.  
	tx_axis_mac_tstrb,	   	//o-8, To show how many bytes of the data is valid. 
	tx_axis_mac_tready,	   	//i-1, Indicates if the slave is ready.  
	
    //Tx Sideband Signals
	tx_ifg_delay,			//o-1, Control signal for configurable interframe gap
	tx_collision,			//i-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	tx_retransmit,			//i-1, Aborted frame to be retransmitted. 0 in full-duplex mode.
	tx_statistics_vector,  	//i-32,A statistics vector that gives information on the last frame transmitted.
	tx_statistics_valid,	//i-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.
	
	 //Rx Main Signals
	rx_mac_aclk, 			//i-1, RX clock.
	rx_axis_mac_tdata,		//i-DATA_WIDTH, Read data.
	rx_axis_mac_tvalid,		//i-1, Signal to show if the data is valid.
	rx_axis_mac_tlast,		//i-1, Signal to show the last data byte or quadword.
	rx_axis_mac_tuser,		//i-1, Error signal.
	rx_axis_mac_tstrb,		//i-8, To show how many bytes of the data is valid.
	rx_axis_mac_tready,		//o-1, If 1, Master is ready to accept data.
	
    //Rx Sideband Signals
	rx_statistics_vector,  	//i-32,A statistics vector that gives information on the last frame transmitted.
	rx_statistics_valid,	//i-1, Asserted at end of frame transmission, indicating that the rx_statistics_vector is valid.
	 
	rx_pkt_gen_sel,			//i

	host_addr,      		//o-16
	reg_rd_start,	  		//o,
	reg_rd_done_out,		//i,
	mac_regdout,	   		//i-32
	start,			       	//i,
	address,         		//i-16
	
	vld_data_flag,			//i-1, will be used for readmem in the memory_compare.v

	test				

);




	parameter ADDR_WIDTH = 32;		
	parameter DATA_WIDTH = 64;
	parameter BCNT_WIDTH = 32;


	input							clk;					//250MHz		
	input							reset_;        					
	input							gen_en_wr;      		//i-1, to initiate the write transaction.		

	input							tx_mac_aclk; 	    	//i-1, TX clock.		
	output	[DATA_WIDTH-1 : 0]		tx_axis_mac_tdata;		//o-DATA_WIDTH, Write data.	
	output	reg						tx_axis_mac_tvalid;		//o-1, Signal to show if the data is valid.	
	output	reg						tx_axis_mac_tlast;		//o-1, Signal to show the last data byte or quadword.	
	output							tx_axis_mac_tuser;		//o-1, Error signal.	
	output	reg [7 : 0]				tx_axis_mac_tstrb;		//o-8, To show how many bytes of the data is valid.	
	input							tx_axis_mac_tready;		//i-1, Indicates if the slave is ready.	
	                                                    	
    //Tx Sideband Signals                               	
	output	reg						tx_ifg_delay;			//o-1, Control signal for configurable interframe gap	
	input							tx_collision;			//i-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.	
	input							tx_retransmit;			//i-1, Aborted frame to be retransmitted. 0 in full-duplex mode.	
	input	[31 : 0]				tx_statistics_vector;  	//i-32,A statistics vector that gives information on the last frame transmitted. 
	input							tx_statistics_valid;	//i-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.
	
    //Rx Main Signals	
	input							rx_mac_aclk; 			//i-1, RX clock.
	input	[DATA_WIDTH-1 : 0]		rx_axis_mac_tdata;		//i-DATA_WIDTH, Read data.
	input							rx_axis_mac_tvalid;		//i-1, Signal to show if the data is valid.
	input							rx_axis_mac_tlast;		//i-1, Signal to show the last data byte or quadword.
	input							rx_axis_mac_tuser;		//i-1, Error signal.
	input	[ 7 :  0]				rx_axis_mac_tstrb;		//i-8, To show how many bytes of the data is valid.
	output	reg						rx_axis_mac_tready;		//o-1, If 1, Master is ready to accept data.
	
    //Rx Sideband Signals
	output	[27 :  0]				rx_statistics_vector;   //i-32,A statistics vector that gives information on the last frame transmitted.
	output							rx_statistics_valid;	//i-1, Asserted at end of frame transmission, indicating that the rx_statistics_vector is valid.
	
	input							rx_pkt_gen_sel;			//i
	
	output 	  						test;					//o-1, debug  	
	
	input		[15 : 0]			address;				//i-16			
	output		[15 : 0]			host_addr;       	 	//o-16		
	output							reg_rd_start;			//o,		
	input 							start;					//i,		
	input							reg_rd_done_out;		//i,		
	input		[31 : 0]			mac_regdout;			//i-32
	
	input							vld_data_flag;			//i-1, will be used for readmem in the memory_compare.v
	                                                                        
	
	reg 							wr_done;				  // pulse that indicates write transaction is done.
	reg 							rd_done;				  // pulse that indicates read transaction is done.
	                            	                    	
	reg		[31 : 0]				mem_wr_address;			  // address to access the memory read register and file.
	
	reg		[31 : 0]				data_length;
	
	reg		[ 7 : 0]				axis_qwd_length;		  // value comes from control memory which tells the length of the packet.
	reg 	[ 3 : 0]				axis_last_qwd_strb;		  // random data between 1 and 8 from control memory which tells how many bytes of the last data is valid.
	
	wire	[31 : 0]	  			mem_axis_wctrl;			  // control value coming from memory.
	wire	[DATA_WIDTH-1 : 0]		mem_axis_wdata;			  // write data coming from the memory.
	
	wire	[DATA_WIDTH-1 : 0]		mem_axis_rdata;			  // read data sent to the memory.
	wire	[ 7 : 0]				mem_axis_rstrb;			  // strobe sent to the memory.
	reg		[ADDR_WIDTH-1 : 0]		mem_rd_address;			  // address to access/write read data and strobe to read memory.
	reg 	[BCNT_WIDTH-1 : 0]		rx_axis_mac_tbcnt;		  // holds the bcnt of the received data. calculated in the master.
	reg 	[31 : 0]				rx_axis_mac_tlen;		  // holds the length of received data and sent to the memory_rd and memory_compare modules
	
	
   	wire	[ADDR_WIDTH-1 : 0]		mem_rd_start_address;
   	wire	[31 : 0]				pkt_cnt;

	
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
	
	
	//State Machine for Read
	reg		[3:0] 	axis_rd_state = 4'h1;
	
	wire			axis_rd_idle_st;
	wire			axis_rd_data_st;
	wire			axis_rd_side_st;
	wire			axis_rd_done_st;
		
	parameter [3:0]       
			AXIS_RD_IDLE		= 	4'h1,  
			AXIS_RD_DATA		= 	4'h2, 
			AXIS_RD_SIDE	    = 	4'h4,		
			AXIS_RD_DONE		= 	4'h8;    
		
	assign	axis_rd_idle_st  = 	axis_rd_state[0];   
	assign  axis_rd_data_st  = 	axis_rd_state[1];             
	assign	axis_rd_side_st	 = 	axis_rd_state[2];   
	assign	axis_rd_done_st  = 	axis_rd_state[3];
	
	
	//wr_strobe assignment
	always @ (tx_axis_mac_tvalid or tx_axis_mac_tlast) begin	
		if (tx_axis_mac_tvalid) begin
		
			if (tx_axis_mac_tlast) begin	  // if valid and tlast: check for axis_last_qwd_strb from memory and assign strobe.
			
				case (axis_last_qwd_strb)
				
					4'd1 : 		tx_axis_mac_tstrb	<=	8'h01;
					4'd2 :		tx_axis_mac_tstrb	<=	8'h03;
					4'd3 :		tx_axis_mac_tstrb	<=	8'h07;
					4'd4 :		tx_axis_mac_tstrb	<=	8'h0f;
					4'd5 :		tx_axis_mac_tstrb	<=	8'h1f;
					4'd6 :		tx_axis_mac_tstrb	<=	8'h3f;
					4'd7 :		tx_axis_mac_tstrb	<=	8'h7f;
					4'd8 :		tx_axis_mac_tstrb	<=	8'hff;
					default:	tx_axis_mac_tstrb	<=	8'h00;
				
				endcase
			
			end
			else begin				  // if valid and not tlast: assign strobe = 8'hff.
			
			tx_axis_mac_tstrb	<=	8'hff;
			
			end
		
		end
		else begin					 // if not valid: assign strobe = 8'h00.
		
			tx_axis_mac_tstrb	<=	8'h00;
		
		end
	end	
	
	
	assign tx_axis_mac_tdata 	= 	mem_axis_wdata;		   //take data from the write memory
	
	assign tx_axis_mac_tuser 	= 	1'b0;
	assign test					=	1'b0;

	assign	mem_axis_rdata		=	rx_axis_mac_tdata;		// RX data sent to the read data memory.
	assign	mem_axis_rstrb		=	rx_axis_mac_tstrb;		// RX strb sent to the read strb memory.
	
	
	
	
	memory_wr_module memory_wr_module(
	
	.tx_mac_aclk		(tx_mac_aclk),				//i, TX Clock
	.reset_ 			(reset_),        			//i, 

	.mem_axis_wctrl 	(mem_axis_wctrl),      		//o, controls the length and last_qwd_strobe
	.mem_axis_wdata 	(mem_axis_wdata),       	//o, write data coming from the memory.
	
	.mem_wr_address		(mem_wr_address)       	   	//i, address to access the memory
	
	);
		

	memory_rd_8b_module memory_rd_8b_module(
	
	.rx_mac_aclk		(rx_mac_aclk),				//i, RX Clock
	.reset_				(reset_),        			//i,
	 
     //input from AXI master to select the test cycle
	.mem_rd_address		(mem_rd_address),			//i, address to access the memory
	
	.mem_axis_rdata		(mem_axis_rdata),			//i, read_data to store in a text file
	.mem_axis_rstrb		(mem_axis_rstrb),			//i, read_strobe to store in a text file
	
	.rd_done			(rd_done),					//i, indicates that the read transaction is done
	.rx_axis_mac_tvalid	(rx_axis_mac_tvalid),		//i, to write to memory as long as valid data is high.
	.rx_axis_mac_tlen	(rx_axis_mac_tlen),			//i, holds the length of the received data
	
	.rx_pkt_gen_sel		(rx_pkt_gen_sel),			//i
	
	.mem_rd_start_address (mem_rd_start_address),	//o
	
	.pkt_cnt			(pkt_cnt)					//o
	
	);
	
	
	//Memory compare module: Self Check at every read_done state
	memory_compare_8b memory_compare_8b(
	
	.rx_mac_aclk		(rx_mac_aclk),				//i, RX Clock
	.reset_				(reset_),             		//i,
	
	.axis_rd_done_st 	(axis_rd_done_st),			//i, self check works at every read_done state
	
	.vld_data_flag		(vld_data_flag),			//i-1, will be used for readmem in the memory_compare.v
	
	.pkt_cnt			(pkt_cnt),					//i
	
	.rx_axis_mac_tvalid	(rx_axis_mac_tvalid),	  	//i, to write to memory as long as valid data is high.
	.rx_axis_mac_tbcnt	(rx_axis_mac_tbcnt)
	);
		


	//WRITE_TRANSACTION
	always @(posedge tx_mac_aclk)
	begin
	
		if (!reset_)
		begin
		
			mem_wr_address		<=	32'b0;
		
			tx_axis_mac_tvalid	<=	1'b0;
			
			tx_axis_mac_tlast	<=	1'b0;
			
	 		axis_qwd_length		<= 	mem_axis_wctrl [15 :  8];
	 		axis_last_qwd_strb	<=	mem_axis_wctrl [31 : 28];
			
			data_length			<=	32'd0;
			
			tx_ifg_delay		<=	1'b0;			 //Not used
			wr_done				<=	1'b0;
			
		end
		
		else if (axis_wr_idle_st)
		begin
		
		
			tx_axis_mac_tvalid	<=	1'b0;
			
			tx_axis_mac_tlast	<=	1'b0;
			
	 		axis_qwd_length		<= 	mem_axis_wctrl [15 :  8];
	 		axis_last_qwd_strb	<=	mem_axis_wctrl [31 : 28];
			
			data_length			<=	32'd0;
			
			wr_done				<=	1'b0;
		
		end
		
		else if (axis_wr_data_st)
		begin
		
			//if ready signal is present then increment the mem_wr_address
			mem_wr_address		<=	(tx_axis_mac_tready)?	mem_wr_address + 1'b1	:
												mem_wr_address;

			//in wr_data state: if not valid, make it high at posedge. if last is present, make it low.
			tx_axis_mac_tvalid	<=	(!tx_axis_mac_tvalid)?	1'b1 : 
												(tx_axis_mac_tvalid && tx_axis_mac_tlast)?	1'b0	:	tx_axis_mac_tvalid;

					 //used to calculate the last qwd to put tlast pulse with it, data_length is calcualted from the axis_qwd_length.
			data_length			<=	(tx_axis_mac_tready && (data_length < (axis_qwd_length - 1)))? 	data_length + 1	: 32'd0;

			tx_axis_mac_tlast	<=	(data_length == (axis_qwd_length - 1))?	1'b1 : 1'b0;
					
		end
		
		else if (axis_wr_side_st)
		begin
		
			tx_ifg_delay		<=	1'b0;		   //Not used
			wr_done				<=	1'b1;
		
		end
		
		else if (axis_wr_done_st)
		begin
		
			wr_done				<=	1'b0;
		
		end
		
	end

	
	
	//READ_TRANSACTION
	always @(posedge rx_mac_aclk)
	begin

		if (!reset_)
		begin
		
			mem_rd_address		<=	32'b0;

			rd_done				<=	1'b0;
			
			rx_axis_mac_tready	<=	1'b0;
			
			rx_axis_mac_tbcnt	<=	32'b0;
			
			rx_axis_mac_tlen	<=	32'b0;
			
		end
		
		else if (axis_rd_idle_st)
		begin
		
			rd_done				<=	1'b0;
			
			rx_axis_mac_tready	<=	1'b0;
			
			rx_axis_mac_tbcnt	<=	32'b0;
			
			rx_axis_mac_tlen	<=	32'b0;
		
		end
		
		else if (axis_rd_data_st)
		begin
		
		   //make ready high if not till the tlast is seen.
			rx_axis_mac_tready		<=	(!rx_axis_mac_tready)?	1'b1 : 
												(rx_axis_mac_tready && rx_axis_mac_tlast)?	1'b0	:	rx_axis_mac_tready;
															
			mem_rd_address			<=	(rx_axis_mac_tready	&&	rx_axis_mac_tvalid)?	mem_rd_address + 1	:	mem_rd_address;	
			
			if (rx_axis_mac_tvalid && rx_axis_mac_tready) begin				 //calculate the bcnt for the received data from the incoming strobe
			
				case (rx_axis_mac_tstrb)
				
					8'h01 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd1;
					8'h03 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd2;
					8'h07 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd3;
					8'h0f 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd4;
					8'h1f 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd5;
					8'h3f 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd6;
					8'h7f 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd7;
					8'hff 	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd8;
					default	:	rx_axis_mac_tbcnt	<=	rx_axis_mac_tbcnt	+	32'd0;
				
				endcase
				
				rx_axis_mac_tlen	<=	rx_axis_mac_tlen	+	32'd1;	
			
			end
			else begin
			
				rx_axis_mac_tbcnt	<=	32'b0;	
			
			end					
				
		end
		
		else if (axis_rd_side_st)
		begin
		
			rd_done				<=	(rd_done)? 1'b0 : 1'b1;
		
		end
		
		else if (axis_rd_done_st)
		begin
		
			rd_done				<=	1'b0;
		
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
					axis_wr_state 	<=                
					(gen_en_wr) ? AXIS_WR_DATA : AXIS_WR_IDLE;                            
					                             					                             
			if (axis_wr_data_st)              
					axis_wr_state 	<= 
					(tx_axis_mac_tlast) ? AXIS_WR_SIDE : AXIS_WR_DATA;  
											
			if (axis_wr_side_st)                          
					axis_wr_state 	<=                         						
					(wr_done) ? AXIS_WR_DONE : AXIS_WR_SIDE;		
			 
			if (axis_wr_done_st)                          		
					axis_wr_state 	<= AXIS_WR_IDLE;                       	  		
		 			    									                          		                             
		end                 
	                                
	end		
		
	
	 //State Machine for Read
	always @ (posedge rx_mac_aclk)           
	begin             
	               	                                
		if (!reset_)         
		begin   
		                       
			axis_rd_state	<= AXIS_RD_IDLE ; 
		     
		end  
		                          
		else                            
		begin                          
		                               
			if (axis_rd_idle_st)              
					axis_rd_state 	<=		AXIS_RD_DATA;                            
					                             					                             
			if (axis_rd_data_st)              
					axis_rd_state 	<= 
					(rx_axis_mac_tlast) ? 	AXIS_RD_SIDE : AXIS_RD_DATA;  
											
			if (axis_rd_side_st)                          
					axis_rd_state 	<=                         						
					(rd_done) ? 			AXIS_RD_DONE : AXIS_RD_SIDE;		
			 
			if (axis_rd_done_st)                          		
					axis_rd_state 	<= 		AXIS_RD_IDLE;                       	  		
		 			    									                          		                             
		end                 
	                                
	end		

			
	
		register_interface register_interface1(

	.reg_clk			(clk),						//i,   
	.reset_				(reset_),        			//i,   
	.host_addr			(host_addr),       	 		//o-16,
	.reg_rd_start		(reg_rd_start),				//o,   
	.reg_rd_done_out	(reg_rd_done_out),			//i,   
	.mac_regdout		(mac_regdout),				//i-32,
	.start				(start),					//i,   
	.address			(address)                   //i-16,
	);
	

	
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
	                                                 
	reg [64*8-1 : 0] ascii_axis_rd_state;                          
	                                                          
	always @ (axis_rd_state)                                       
	begin                                                     
		case(axis_rd_state)                                         
	    AXIS_RD_IDLE		:  	ascii_axis_rd_state = "AXIS_RD_IDLE";        
		AXIS_RD_DATA		:  	ascii_axis_rd_state = "AXIS_RD_DATA";          
		AXIS_RD_SIDE		:  	ascii_axis_rd_state = "AXIS_RD_SIDE";            
		AXIS_RD_DONE		:   ascii_axis_rd_state = "AXIS_RD_DONE";
		endcase                                                  
	end                                                       
	                                                          
	//synopsys translate_on                               

endmodule