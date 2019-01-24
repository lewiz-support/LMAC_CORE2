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
module fmac2fib_rxctrl(
	clk_fib,							//i-1	clock signal at FMAC frequency
	reset_,								//i-1	global reset signal 	

//Signals to Read FIFOs
	wren_rf,							//o-1	write enable of data FIFO
	wren_rcf,							//o-1	write enable of wrcnt FIFO
	datain_rf,							//o-64	Datain of data FIFO	 
	datain_rcf,							//o-32	Datain of wrcnt FIFO
	
//Signals from Read FIFOs	
	wrempty_rf, 						//i-1	Empty signal of data FIFO	
	wrempty_rcf,						//i-1	Empty signal of rdcnt FIFO
	
	
//Signals from FMAC
	fib_rx_mac_data_empty,				//i-1 	 signal from FMAC saying its FIFO is empty
	fib_rx_mac_pkt_data,				//i-64 	 data signal of FMAC module
    fib_rx_mac_ipcs_empty,  			//i-1 	 signal from IPCS FIFO in FMAC its empty
    fib_rx_mac_ipcs_data,				//i-64 	 data signal of IPCS FIFO from FMAC module
    
//Signals to FMAC
	fib_rx_mac_rdcycle,					//o-1 	 read cycle signal
	fib_rx_mac_rd, 						//o-1 	 read signal 
	fib_rx_mac_ipcs_rd, 				//o-1 	 read signal 
	
//TEST signal
	test 								//o-1 	debug	
);


parameter 	DATA_WIDTH = 64;
parameter 	BCNT_WIDTH = 32;


input  										clk_fib; 					// clock running at 125MHz
input  										reset_;

//Signals to Read FIFOs
output	reg	             					wren_rf;					//o-1	write enable of data FIFO
output	reg	              					wren_rcf;					//o-1	write enable of wrcnt FIFO
output	reg [DATA_WIDTH - 1:0]  			datain_rf;					//o-64	Datain of data FIFO	 
output	reg	[BCNT_WIDTH - 1:0]				datain_rcf;					//o-32	Datain of wrcnt FIFO
	
//Signals from Read FIFOs	
input										wrempty_rf; 				//i-1	Empty signal of data FIFO	
input										wrempty_rcf;				//i-1	Empty signal of rdcnt FIFO
	
	
//Signals from FMAC
input		             					fib_rx_mac_data_empty;		//i-1 	 signal from FMAC saying its Data FIFO is empty
input [DATA_WIDTH - 1:0]					fib_rx_mac_pkt_data;		//i-64 	 data signal of FMAC module
input		             					fib_rx_mac_ipcs_empty;		//i-1 	 signal from IPCS FIFO in FMAC its empty
input [DATA_WIDTH - 1:0]					fib_rx_mac_ipcs_data;		//i-64 	 data signal of IPCS FIFO from FMAC module

//Signals to FMAC
output reg									fib_rx_mac_rdcycle;			//o-1 	 read cycle signal
output reg 				 					fib_rx_mac_rd; 				//o-1 	 read signal for FMAC data 
output reg  								fib_rx_mac_ipcs_rd; 		//o-1 	 read signal for IPCS data 

//TEST signal
output 										test ;						//o-1 	debug


parameter [5:0] 
	BR_IDLE		= 	6'h01,	//idle state
	BR_CHECKRX	= 	6'h02, 	//check rx fifo state
	BR_READCNT	= 	6'h04, 	//read rdcount state
	BR_RDDATA	= 	6'h08,	//FIFO write state
	BR_DONE		= 	6'h10	//done  state
	;


	wire 						br_idle_st ;
	wire 						br_checkrx_st ;
	wire 						br_readcnt_st ;
	wire 						br_rddata_st ;
	wire 						br_done_st ;
		        				
	reg 	[5:0] 				br_state;
	
	reg 	[15:0] 				chckcnt; 
	reg 	[1:0] 				rd_st_cnt;
	reg 						wren_rf_delay;
	reg		[31:0]				datain_rcf_before_packet;
	
	
	assign 			br_idle_st    	= 	br_state[0];
	assign 			br_checkrx_st 	= 	br_state[1];
	assign 			br_readcnt_st 	= 	br_state[2];
	assign 			br_rddata_st  	= 	br_state[3];
	assign 			br_done_st    	= 	br_state[4];

	assign			test			=	1'b0;         

	
always @(posedge clk_fib)
		if (!reset_ )
		begin
			wren_rf		        	<= 	1'b0;
			wren_rcf		        <= 	1'b0;
			datain_rf		        <= 	64'd0;
			datain_rcf		        <= 	32'd0;
			fib_rx_mac_rdcycle   	<= 	1'b0;
			fib_rx_mac_rd		    <= 	1'b0;
			fib_rx_mac_ipcs_rd	    <= 	1'b0;
			chckcnt		         	<= 	16'd0;		
			rd_st_cnt               <= 	2'b0;
			wren_rf_delay 	       	<= 	1'b0;
			
			datain_rcf_before_packet <= 32'b0; 
			
		end
			
		else
		begin 
		
			datain_rcf_before_packet <= (rd_st_cnt==2'b01) ? fib_rx_mac_ipcs_data [63:32] :  // write  brcnt when read stste count is 1 
                       						datain_rcf_before_packet;
                       						            
            datain_rcf		<=	((br_rddata_st) & (chckcnt == 16'h00))?		datain_rcf_before_packet : datain_rcf;                        
                        
            wren_rcf		<=	((br_rddata_st) & (chckcnt == 16'h00))?		1'b1 : 1'b0;
          	
			fib_rx_mac_rdcycle <= 
								(br_rddata_st ) ? 
							    (((chckcnt - 16'h10) == 16'h0) | ((chckcnt - 16'h10) > fib_rx_mac_ipcs_data [63:32] ) ) ? 1'b0 : //the read should be zero before 2 byte counts as we start reading 2 clocks early
								1'b1 :  // start rdcycle in these states
        					    1'b0  
        					    ;
            
            
            fib_rx_mac_rd 	<=
            				(br_rddata_st  ) ? 
            				(((chckcnt - 16'h10) == 16'h0) | ((chckcnt - 16'h10) > fib_rx_mac_ipcs_data [63:32] )  ) ? 1'b0    : //the read should be zero before 2 byte counts as we start reading 2 clocks early
            				1'b1 :  // start rdcycle in these states
            				1'b0  
            				;
																			
			fib_rx_mac_ipcs_rd 	<= 
								(br_checkrx_st & !fib_rx_mac_ipcs_empty ) ? 1'b1 :  // enable data read (June 11, 2018)
            					1'b0  
								;
			
		    datain_rf 	<= 	
		    			(chckcnt >= 16'h00 ) ? fib_rx_mac_pkt_data      : // write the data in Read FIFO till the byte count is greater than or equal to zero
		                datain_rf
						;
			
			
            wren_rf_delay 	<= 	
            				(fib_rx_mac_rd) ? 1'b1: 	// write enable delayed for Read data FIFO
            				1'b0
            				;
            
            
			wren_rf 	<= 
						(wren_rf_delay) ? 1'b1: 	// write enable for Read data FIFO
            			1'b0
            			;
            
			chckcnt <= 
					( br_rddata_st & (16'h00 < chckcnt) & (chckcnt <= 16'h08) )? 16'h00	:  
					(wren_rf_delay & (chckcnt > 16'h08) ) ?  chckcnt - 16'h08 	: // keep track of check count and update  it
            		(br_readcnt_st ) ? fib_rx_mac_ipcs_data [63:48] : // store count in temp reg (chckcnt) 
            		chckcnt                                           // DOnt descrement the count until 1st write into the RD FIFO
            		;
            
            
		    rd_st_cnt 	<= 
		    			br_readcnt_st & (rd_st_cnt != 2'b10) & !br_done_st & !br_idle_st & !br_checkrx_st & !br_rddata_st ? rd_st_cnt + 1'b1 :
		    			!br_readcnt_st | br_done_st | br_idle_st | br_checkrx_st | br_rddata_st ? 2'b0 :
		    			rd_st_cnt
		    			;
		
		
end



	
always @(posedge clk_fib)
		if (!reset_ ) // if reset then go into idle state
			br_state <= BR_IDLE ;	
		else
			begin
			
			if(br_idle_st) // wait in idle state till the Read FIFOs get empty
				br_state <= 
				(wrempty_rf & wrempty_rcf ) ? BR_CHECKRX : // if true , check fmac fifo status
				BR_IDLE
				;
				
			
			if(br_checkrx_st) // wait in this state till the RX FIFOs of FMAC has data
				br_state <=
				(!fib_rx_mac_data_empty & !fib_rx_mac_ipcs_empty ) ? BR_READCNT : // if it has data, go in next state
				BR_CHECKRX 
				;
							
				
			if(br_readcnt_st) // read byte count and make a copy, go in next state
				br_state <= (rd_st_cnt==2'b10) ? BR_RDDATA  : // wait till read state sount is 2; 2 indicates the read data has been written successfully
				 BR_READCNT
				;
				
				
			if(br_rddata_st) 
				br_state <=
				(chckcnt == 16'h00  ) ? BR_DONE :
				BR_RDDATA
				;
				
				
			if(br_done_st)			// this states indicates that last transfer will 
				br_state <= BR_IDLE // take place and the transaction will be  completed 
				;					// or the FMAC fifo is empty 
end 
		
		
//============== Simulation ONLY =======================//
        //synopsys translate_off
            
        reg [8*8-1:0] ascii_br_state;
        
        always@(br_state)
        begin
            case(br_state)
            BR_IDLE:          ascii_br_state 	= 	"BR_IDLE";
            BR_CHECKRX:       ascii_br_state 	= 	"BR_CHECKRX";
            BR_READCNT:       ascii_br_state 	= 	"BR_READCNT";
            BR_RDDATA:        ascii_br_state 	= 	"BR_RDDATA";
            BR_DONE:          ascii_br_state 	= 	"BR_DONE";
            endcase
        end
        
        //synopsys translate_on        
		
endmodule 
