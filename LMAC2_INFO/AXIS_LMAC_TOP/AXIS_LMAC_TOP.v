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

module AXIS_LMAC_TOP(

		clk,			  			//i-1, 322MHz 		
		reset_,             	    //i-1        
		
		gen_en_wr,      			//i-1, to initiate the write transaction.
		                    		
		fmac_speed,					//i-3, specify speed mode
		
		//Main Signals
		tx_mac_aclk, 				//i-1, TX clock.                                                                                                	
		tx_axis_mac_tdata,		    //i-DATA_WIDTH, Write data.                                                                                     
		tx_axis_mac_tvalid,		    //i-1, Signal to show if the data is valid.                                                                     
		tx_axis_mac_tlast,		    //i-1, Signal to show the last data byte or quadword.                                                           
		tx_axis_mac_tuser,		    //i-1, Error signal.                                                                                            
		tx_axis_mac_tstrb,		    //i-8, To show how many bytes of the data is valid.                                                             
		tx_axis_mac_tready,		    //o-1, Indicates if the slave is ready.                                                                         
		                                                                                                                                            
		//Sideband Signals                                                                                                                          
		tx_ifg_delay,			    //i-1, Control signal for configurable interframe gap                                                           
		tx_collision,			    //o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
		tx_retransmit,			    //o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
		tx_statistics_vector,       //o-32,A statistics vector that gives information on the last frame transmitted.                                
		tx_statistics_valid,        //o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.                
		
		//Signals to AXIS Master
		rx_mac_aclk,				//i-1	
		rx_axis_mac_tdata,			//o-64 	 data signal of bridge module
    	rx_axis_mac_tvalid,  		//o-1 	 signal to AXIS master indicating the data is valid
    	rx_axis_mac_tlast,			//o-1 	 signal to AXIS Master saying end of data
    	rx_axis_mac_tuser,			//o-1 	 error signal from FMAC
    	rx_axis_filter_tuser,		//o-1 	 error signal from filter of FMAC
    	rx_axis_mac_tstrb,			//o-8 	 Signal indicating valid bytes inside the qword transmitting
    	rx_statistics_vector,		//o-27 	 information about current frame 
    	rx_statistics_valid,		//o-1	 Signal indication the statistics vector is valid
    	
    	//Signals from AXIS Master
		rx_axis_mac_tready,			//i-1	signal indicating that AXIS master accepted data
		rx_axis_compatible_mode,	//i-1    signal to keep tready always one  
		
		xA_clk,					//i-1		156.25 Mhz			
		
		//xgmii signals not used. 20 july 2018
		xgmii_txd,			//o-64
		xgmii_txc,			//o-8
		                	
		xgmii_rxd,			//i-64
		xgmii_rxc,			//i-8 
		
		host_addr_reg, 		//i-16	   	
		fail_over,	       	//i-1                                   
		fmac_ctrl, 		   	//i-32                                  
		fmac_ctrl1, 	   	//i-32                                  
		fmac_rxd_en, 	   	//i-1, 13jul11		                        
		mac_pause_value,   	//i-32                                  
		mac_addr0, 		   	//i-48                                  
		SYS_ADDR,		   	//i-4, system assigned addr for the FMAC
		
		TCORE_MODE,			//i-1, coming as zero
		
		reg_rd_start,     	//i-1 
		reg_rd_done_out,    //o-1 
		FMAC_REGDOUT,       //o-32
				
		test				//o-1	

	);

	parameter 				ADDR_WIDTH  = 32;						//default
	parameter 				DATA_WIDTH 	= 64;
	parameter 				DATA_PTR 	= 8;
	parameter 				BCNT_WIDTH 	= 32;
	parameter 				BCNT_PTR 	= 2;
      
	
	input      								clk;			   		//i-1, 322MHz
	input      								reset_;             	//i-1
	
	input									gen_en_wr;				//i-1, to initiate the write transaction.
	
	input		[ 2 : 0]					fmac_speed;				//i-3		
	
	//Main Signals
	input									tx_mac_aclk; 			//i-1, TX clock.                                     
	input		[DATA_WIDTH-1 : 0]			tx_axis_mac_tdata;		//i-DATA_WIDTH, Write data.                          
	input									tx_axis_mac_tvalid;		//i-1, Signal to show if the data is valid.          
	input									tx_axis_mac_tlast;		//i-1, Signal to show the last data byte or quadword.
	input									tx_axis_mac_tuser;		//i-1, Error signal.                                 
	input		[ 7 : 0]					tx_axis_mac_tstrb;		//i-8, To show how many bytes of the data is valid.  
	output									tx_axis_mac_tready;		//o-1, Indicates if the slave is ready.              
	
	//Sideband Signals	
	input									tx_ifg_delay;			//i-1, Control signal for configurable interframe gap                                                           
	output									tx_collision;			//o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	output									tx_retransmit;			//o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	output		[31 : 0]					tx_statistics_vector;   //o-32,A statistics vector that gives information on the last frame transmitted.                                
	output									tx_statistics_valid;	//o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid. 
	
	
	//Signals to AXIS Master
	input									rx_mac_aclk;			//i-1
	output		[DATA_WIDTH - 1:0]			rx_axis_mac_tdata;		//o-64 	 data signal of bridge module********
	output  								rx_axis_mac_tvalid;		//o-1 	 signal to AXIS master indicating the data is valid********
	output  								rx_axis_mac_tlast;		//o-1 	 signal to AXIS Master saying end of data
	output  								rx_axis_mac_tuser;		//o-1 	 error signal from FMAC
	output  								rx_axis_filter_tuser;	//o-1 	 error signal from filter of FMAC
	output  	[ 8 - 1: 0] 				rx_axis_mac_tstrb;   	//o-8 	 Signal indicating valid bytes inside the qword transmitting
	output  	[28 - 1: 0]  				rx_statistics_vector;   //o-27 	 information about current frame 
	output  								rx_statistics_valid;	//o-1	 Signal indication the statistics vector is valid
	  
	//Signals from AXIS Master  
	input									rx_axis_mac_tready;		//i-1	signal indicating that AXIS master accepted data
	input       							rx_axis_compatible_mode;//i-1    signal to keep tready always one
	
	output									test;					//o-1
	
	
	input									reg_rd_start;			//i-1
	output									reg_rd_done_out;		//o-1	
	output		[31:0]						FMAC_REGDOUT;           //o-32
		                                                                    	
	//Signals from FMAC                                             	
	wire 		[12:0] 						fib_tx_mac_usedw; 			//13  Bit-wise OR the signal to use it as empty signal 
	                                                                	
	//Signals to FMAC                                               	
	wire 		[DATA_WIDTH-1 : 0] 			fib_tx_mac_data; 			//64, Data in of FMAC for tx path 
	wire 									fib_tx_mac_wr; 				//1	, Write enable signal of FMAC FIFO 	
	wire 		[DATA_WIDTH-1 : 0] 			fib_tx_mac_ipcs_data; 		//64, IPCS Data in of FMAC IPCS for tx path 
	wire 									fib_tx_mac_ipcs_wr; 		//1 , Write enable signal of FMAC IPCS FIFO	
	
	//Signals from FMAC
	wire 									fib_rx_mac_data_empty; 		//1 , signal from FMAC saying its FIFO is empty
	wire 		[DATA_WIDTH-1 : 0] 			fib_rx_mac_pkt_data; 		//64, data signal of FMAC module
	wire 									fib_rx_mac_ipcs_empty; 		//1 , signal from IPCS FIFO in FMAC its empty
	wire 		[DATA_WIDTH-1 : 0]			fib_rx_mac_ipcs_data; 		//64, data signal of IPCS FIFO from FMAC module
	
	//Signals to FMAC
	wire 									fib_rx_mac_rdcycle; 		//1, read cycle signal
	wire 									fib_rx_mac_rd; 				//1, read signal 
	wire 									fib_rx_mac_ipcs_rd; 		//1, read signal for ipcs
			

	input 									xA_clk;						//i-1 156.25 Mhz

	//XGMII Signals not used. 20 july 2018
	output		[DATA_WIDTH-1 : 0]			xgmii_txd ;					//o-64
	output		[7:0]       				xgmii_txc ;					//o-8
	                                		                			
	input 		[DATA_WIDTH-1 : 0]			xgmii_rxd;					//i-64
    input 		[7:0]						xgmii_rxc;					//i-8

										
	input									TCORE_MODE;

	// Interface to TX PATH         		
	wire									tx_mac_full;
			                        		
	// Interface to RX PATH         		
	wire		[7:0]						rx_mac_ctrl;
	                                		
	//for field debug               		
	wire									rx_mac_full_dbg;
	wire		[11:0]						rx_mac_usedw_dbg;

	// From central_decoder	
	input 		[15:0]			host_addr_reg;
	input		[3:0]			SYS_ADDR;
			
	// From mac_register
	input						fail_over;
	input		[31:0]			fmac_ctrl;
	input		[31:0]			fmac_ctrl1;
	
	input						fmac_rxd_en	;
	
	input 		[31:0]			mac_pause_value;			// [31:16] = tx_pause_value to send a pause frame, [15:0] = rx_pause_value (not implement)
	input 		[47:0]			mac_addr0;					// mac_addr to check in non-promiscuous mode
	
	wire						reg_rd_start;
				
	// To mac_register
	wire		[31:0]			FMAC_REGDOUT;
	wire						FIFO_OV_IPEND;
				
	reg 			mode_10G;
	reg 			mode_5G;
	reg 			mode_2p5G;
	reg 			mode_1G;
	
	
	wire		[15 : 0]		host_addr_reg_out; 
	wire		[31 : 0]		FMAC_REGDOUT_in;   
    wire 						reg_rd_start_out;  
	wire 						reg_rd_done_in;
	
	
		
	
	always @(posedge clk) begin
	
		mode_10G    <=	(fmac_speed	==	3'd0);
		mode_5G     <=	(fmac_speed	==	3'd5);
		mode_2p5G	<=	(fmac_speed	==	3'd2);
		mode_1G     <=	(fmac_speed	==	3'd1);
	
	end
		

	//FMAC SIGNALS///////////////         
	AXIS_BRIDGE_TOP AXIS_BRIDGE_TOP(

	.clk 						(clk),							//i-1, 322MHz
	.xA_clk 					(xA_clk),						//i-1, 156.25MHz
	.reset_ 					(reset_),        				//i-1
             
	//Main Signals	               	
	.tx_mac_aclk 				(tx_mac_aclk), 					//i-1, TX clock 322MHz.                                     
	.tx_axis_mac_tdata 			(tx_axis_mac_tdata),			//i-DATA_WIDTH, Write data.                          
	.tx_axis_mac_tvalid 		(tx_axis_mac_tvalid),			//i-1, Signal to show if the data is valid.          
	.tx_axis_mac_tlast 			(tx_axis_mac_tlast),			//i-1, Signal to show the last data byte or quadword.
	.tx_axis_mac_tuser 			(tx_axis_mac_tuser),			//i-1, Error signal.                                 
	.tx_axis_mac_tstrb 			(tx_axis_mac_tstrb),			//i-8, To show how many bytes of the data is valid.  
	.tx_axis_mac_tready 		(tx_axis_mac_tready),			//o-1, Indicates if the slave is ready.              
	      
	//Sideband Signals                  	
	.tx_ifg_delay 				(tx_ifg_delay),					//i-1, Control signal for configurable interframe gap                                                           
	.tx_collision 				(tx_collision),					//o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	.tx_retransmit 				(tx_retransmit),				//o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	.tx_statistics_vector 		(tx_statistics_vector),   		//o-32,A statistics vector that gives information on the last frame transmitted.                                
	.tx_statistics_valid 		(tx_statistics_valid),			//o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.  
	
	//Signals to AXIS Master
	.rx_mac_aclk				(rx_mac_aclk),					//i-1, RX clock 322MHz.	
	.rx_axis_mac_tdata 			(rx_axis_mac_tdata),			//o-64, data signal of bridge module
    .rx_axis_mac_tvalid 		(rx_axis_mac_tvalid),  			//o-1, signal to AXIS master indicating the data is valid
    .rx_axis_mac_tlast 			(rx_axis_mac_tlast),			//o-1, signal to AXIS Master saying end of data
    .rx_axis_mac_tuser 			(rx_axis_mac_tuser),			//o-1, error signal from FMAC
    .rx_axis_filter_tuser 		(rx_axis_filter_tuser),			//o-1, error signal from filter of FMAC
    .rx_axis_mac_tstrb 			(rx_axis_mac_tstrb),			//o-8, Signal indicating valid bytes inside the qword transmitting
    .rx_statistics_vector 		(rx_statistics_vector),			//o-27, information about current frame 
    .rx_statistics_valid 		(rx_statistics_valid),			//o-1, Signal indication the statistics vector is valid
    
    //Signals from AXIS Master
	.rx_axis_mac_tready 		(rx_axis_mac_tready),			//i-1, signal indicating that AXIS master accepted data
	.rx_axis_compatible_mode 	(rx_axis_compatible_mode),		//i-1, signal to keep tready always one     
	
	//Signals from FMAC	                    	                    			
	.fib_tx_mac_usedw 			(fib_tx_mac_usedw),				//i-13, Bit-wise OR the signal to use it as empty signal 
           
	//Signals to FMAC                 	                			
	.fib_tx_mac_data 			(fib_tx_mac_data),				//o-64, Data in of FMAC for tx path 
	.fib_tx_mac_wr 				(fib_tx_mac_wr),				//o-1,  Write enable signal of FMAC FIFO 
	.fib_tx_mac_ipcs_data 		(fib_tx_mac_ipcs_data),			//o-64, IPCS Data in of FMAC IPCS for tx path 
    .fib_tx_mac_ipcs_wr 		(fib_tx_mac_ipcs_wr),  			//o-1 , Write enable signal of FMAC IPCS FIFO    
    
	//Signals from FMAC
	.fib_rx_mac_data_empty 		(fib_rx_mac_data_empty),		//i-1 , signal from FMAC saying its FIFO is empty
	.fib_rx_mac_pkt_data 		(fib_rx_mac_pkt_data),			//i-64, data signal of FMAC module
    .fib_rx_mac_ipcs_empty 		(fib_rx_mac_ipcs_empty),  		//i-1 , signal from IPCS FIFO in FMAC its empty
    .fib_rx_mac_ipcs_data 		(fib_rx_mac_ipcs_data),			//i-64, data signal of IPCS FIFO from FMAC module
    
    //Signals to FMAC
	.fib_rx_mac_rdcycle 		(fib_rx_mac_rdcycle),			//o-1, read cycle signal
	.fib_rx_mac_rd 				(fib_rx_mac_rd), 				//o-1, read signal 
	.fib_rx_mac_ipcs_rd 		(fib_rx_mac_ipcs_rd), 			//o-1, read signal        
	
	.host_addr_in				(host_addr_reg),		  		//i-16   
	.mac_regdout_in				(FMAC_REGDOUT_in),		        //i-32
	.reg_rd_start_in			(reg_rd_start),	                //i-1 
	.reg_rd_done_in				(reg_rd_done_in),	            //i-1 
	                                                                  
	.host_addr_out				(host_addr_reg_out),		    //o-16
	.mac_regdout_out			(FMAC_REGDOUT),	                //o-32
	.reg_rd_start_out			(reg_rd_start_out),	            //o-1 
	.reg_rd_done_out			(reg_rd_done_out),			    //o-1 
                                                            	
	.test 						(test)							//o-1 debug		

	);

	
	LMAC_CORE_TOP LMAC_CORE_TOP(
	
	//clk, xaui_clk is really FMAC clk125 for GigE version
	.clk 						(xA_clk),					//i-1, 156.25 MHz
	.xA_clk 					(xA_clk),					//i-1, 156.25 Mhz
	.reset_ 					(reset_),					//i-1, FMAC specific reset (also follows PCIE RST)	
	
	.mode_10G 					(mode_10G),  				//i-1, speed modes
	.mode_5G  					(mode_5G),   				//i-1, 
	.mode_2p5G					(mode_2p5G), 				//i-1, 
	.mode_1G  					(mode_1G),   				//i-1, 
	            				                			
	.TCORE_MODE 				(1'b0),						//i-1, TOE Core = 0.		   
           
	//Interface to TX PATH                 	
	.tx_mac_wr 					(fib_tx_mac_wr),			//i-1
	.tx_mac_data 				(fib_tx_mac_data),			//i-64
	.tx_mac_full 				(tx_mac_full),				//o-1
	.tx_mac_usedw 				(fib_tx_mac_usedw),			//o-13
	       
	//Interface to RX PATH                  	
	.rx_mac_data 				(fib_rx_mac_pkt_data),		//o-64
	.rx_mac_ctrl 				(rx_mac_ctrl),				//o-8, rsvd, pkt_end, pkt_start
	.rx_mac_empty 				(fib_rx_mac_data_empty),	//o-1
	.rx_mac_rd 					(fib_rx_mac_rd),			//i-1
	.rx_mac_rd_cycle 			(fib_rx_mac_rdcycle),		//i-1, from EXTR
	      
	//for field debug                   	
	.rx_mac_full_dbg 			(rx_mac_full_dbg),			//o-1
	.rx_mac_usedw_dbg 			(rx_mac_usedw_dbg),			//o-12
	
	//for pre_CS/parser (I/F to RX Path/EXTR)
	.cs_fifo_rd_en 				(fib_rx_mac_ipcs_rd),		//i-1
	.cs_fifo_empty 				(fib_rx_mac_ipcs_empty),	//o-1
	.ipcs_fifo_dout 			(fib_rx_mac_ipcs_data),		//o-64	
	
	////XGMII Signals not used. 20 july 2018  
	.xgmii_reset_ 				(1'b0),        				//i-1
    .xgmii_txd 					(xgmii_txd),				//o-64
    .xgmii_txc 					(xgmii_txc),				//o-8
    //           					
	.xgmii_rxd 					(xgmii_rxd),				//i-64
    .xgmii_rxc 					(xgmii_rxc),				//i-8
    .xgmii_led_ 				(2'b0),						//i-2
	                        	
	.xauiA_linkup 				(),							//o-1, link up for either 10G or 10G mode 
	                        	
	.host_addr_reg 				(host_addr_reg_out),		//i-16
	.SYS_ADDR 					(SYS_ADDR),					//i-4, system assigned addr for the FMAC
	                                                        
	//From mac_register               	                    
	.fail_over 					(fail_over),				//i-1
	.fmac_ctrl 					(fmac_ctrl),				//i-32
	.fmac_ctrl1 				(fmac_ctrl1),				//i-32
	                        	                            
	.fmac_rxd_en 				(fmac_rxd_en),				//i-1, 13jul11
	                        	                            
	.mac_pause_value 			(mac_pause_value),			//i-32
	.mac_addr0 					(mac_addr0), 				//i-48
	                                                        
	.reg_rd_start 				(reg_rd_start_out),			//i-1	
	.reg_rd_done_out			(reg_rd_done_in),			//o-1
	                        	                            
	.FMAC_REGDOUT 				(FMAC_REGDOUT_in),			//o-32		
	.FIFO_OV_IPEND 				(FIFO_OV_IPEND)				//o-1
	
	);
	
			
endmodule