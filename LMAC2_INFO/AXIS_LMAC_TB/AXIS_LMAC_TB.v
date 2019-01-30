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

module AXIS_LMAC_TB();

	parameter 				ADDR_WIDTH  = 32;				//default
	parameter 				DATA_WIDTH 	= 64;
	parameter 				DATA_PTR 	= 8;
	parameter 				BCNT_WIDTH 	= 32;
	parameter 				BCNT_PTR 	= 2;
                                    			
	reg 							clk; 		
	reg 							reset_; 
	reg 							gen_en_wr;				//start write operation

	reg 							xA_clk;					// i-1		156.25 Mhz			

	//Tx Main Signals
	reg								tx_mac_aclk; 			//1, TX clock.
	wire	[DATA_WIDTH-1 : 0]		tx_axis_mac_tdata;		//DATA_WIDTH, Write data.
	wire							tx_axis_mac_tvalid;		//1, Signal to show if the data is valid.
	wire							tx_axis_mac_tlast;		//1, Signal to show the last data byte or quadword.
	wire							tx_axis_mac_tuser;		//1, Error signal.
	wire	[7 : 0]					tx_axis_mac_tstrb;		//8, To show how many bytes of the data is valid.
	wire							tx_axis_mac_tready;		//1, Indicates if the slave is ready.
	
	//Tx Sideband Signals
	wire							tx_ifg_delay;			//1, Control signal for configurable interframe gap
	wire							tx_collision;			//1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	wire							tx_retransmit;			//1, Aborted frame to be retransmitted. 0 in full-duplex mode.
	wire	[31 : 0]				tx_statistics_vector;   //32,A statistics vector that gives information on the last frame transmitted.
	wire							tx_statistics_valid;	//1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.
		
	//Rx Main Signals
	reg								rx_mac_aclk; 			//1, RX clock.                                     
	wire	[DATA_WIDTH-1 : 0]		rx_axis_mac_tdata;		//DATA_WIDTH, Read data.                          
	wire							rx_axis_mac_tvalid;		//1, Signal to show if the data is valid.          
	wire							rx_axis_mac_tlast;		//1, Signal to show the last data byte or quadword.
	wire							rx_axis_mac_tuser;		//1, Error signal.                                 
	wire	[ 7 :  0]				rx_axis_mac_tstrb;		//8, To show how many bytes of the data is valid.  
	wire							rx_axis_mac_tready;		//1, If 1, Master is ready to accept data.              
	
	//Rx Sideband Signals
	wire	[27 :  0]				rx_statistics_vector;   //32,A statistics vector that gives information on the last frame transmitted.                                
	wire							rx_statistics_valid;	//1, Asserted at end of frame transmission, indicating that the rx_statistics_vector is valid.                


	////xgmii signals not used. 20 july 2018
	wire	[63 : 0]				xgmii_txd;				//64
	wire 	[ 7 : 0]				xgmii_txc;				//8
	                    			                		
	wire	[63 : 0]				xgmii_rxd;				//64
	wire 	[ 7 : 0]				xgmii_rxc;				//8
	                			                    	
	wire 	[15 : 0]				host_addr_reg; 			//16
	reg 							fail_over; 				//1
	reg 	[31 : 0]				fmac_ctrl; 			    //32
	reg 	[31 : 0]				fmac_ctrl1; 			//32
	reg 							fmac_rxd_en; 			//1		                    	
	reg 	[31 : 0]				mac_pause_value; 		//32
	reg 	[47 : 0]				mac_addr0; 				//48
	reg 	[ 3 : 0]				SYS_ADDR; 				//4, system assigned addr for the FMAC
	
	reg								TCORE_MODE;
	
	//rx_pkt_gen
	reg								rx_pkt_gen_sel;			// if 1, rxd and rxc becomes the rx_pkt_gen data. if 0, rxd and rxc is loopback data i.e. txd and txc.
            
	reg								rx_axis_compatible_mode;
	
    wire	[ 2 : 0]				fmac_speed = 3'b0;	
    
    
	reg 	[15:0] 	address;
    wire 			reg_rd_start;
    wire 			reg_rd_done_out;
    wire 	[31:0] 	FMAC_REGDOUT;
    reg 			start;
    
    wire			vld_data_flag;		//will be used for readmem in the memory_compare.v
    

	axi_stream_master axi_stream_master(

	.clk 					(clk),						//i-1, 322MHz
	.reset_ 				(reset_),        			//i-1
	.gen_en_wr 				(gen_en_wr),      			//i-1, to initiate the write transaction.

	//Main Signals	
	.tx_mac_aclk 			(tx_mac_aclk), 				//i-1, TX clock.                                     
	.tx_axis_mac_tdata 		(tx_axis_mac_tdata),		//o-DATA_WIDTH, Write data.                          
	.tx_axis_mac_tvalid 	(tx_axis_mac_tvalid),		//o-1, Signal to show if the data is valid.          
	.tx_axis_mac_tlast 		(tx_axis_mac_tlast),		//o-1, Signal to show the last data byte or quadword.
	.tx_axis_mac_tuser 		(tx_axis_mac_tuser),		//o-1, Error signal.                                 
	.tx_axis_mac_tstrb 		(tx_axis_mac_tstrb),		//o-8, To show how many bytes of the data is valid.  
	.tx_axis_mac_tready 	(tx_axis_mac_tready),		//i-1, Indicates if the slave is ready.              
	
	//Sideband Signals
	.tx_ifg_delay 			(tx_ifg_delay),				//o-1, Control signal for configurable interframe gap                                                           
	.tx_collision 			(tx_collision),				//i-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	.tx_retransmit 			(tx_retransmit),			//i-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	.tx_statistics_vector 	(tx_statistics_vector),   	//i-32,A statistics vector that gives information on the last frame transmitted.                                
	.tx_statistics_valid 	(tx_statistics_valid),		//i-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.                
	
	//Rx Main Signals
	.rx_mac_aclk 			(rx_mac_aclk), 				//i-1, RX clock.                                     
	.rx_axis_mac_tdata 		(rx_axis_mac_tdata),		//i-DATA_WIDTH, Read data.                          
	.rx_axis_mac_tvalid 	(rx_axis_mac_tvalid),		//i-1, Signal to show if the data is valid.          
	.rx_axis_mac_tlast 		(rx_axis_mac_tlast),		//i-1, Signal to show the last data byte or quadword.
	.rx_axis_mac_tuser 		(rx_axis_mac_tuser),		//i-1, Error signal.                                 
	.rx_axis_mac_tstrb 		(rx_axis_mac_tstrb),		//i-8, To show how many bytes of the data is valid.  
	.rx_axis_mac_tready 	(rx_axis_mac_tready),		//o-1, If 1, Master is ready to accept data.              
	
	//Rx Sideband Signals
	.rx_statistics_vector 	(rx_statistics_vector),   	//i-32,A statistics vector that gives information on the last frame transmitted.                                
	.rx_statistics_valid 	(rx_statistics_valid),		//i-1, Asserted at end of frame transmission, indicating that the rx_statistics_vector is valid. 
	
	.rx_pkt_gen_sel 		(rx_pkt_gen_sel),			//i                  
	
	.host_addr				(host_addr_reg),      
	.reg_rd_start			(reg_rd_start),	  
	.reg_rd_done_out		(reg_rd_done_out),
	.mac_regdout			(FMAC_REGDOUT),	   
	.start					(start),			       
	.address 				(address),
	
   	.vld_data_flag			(vld_data_flag),			//i-1, will be used for readmem in the memory_compare.v
	
	.test 					()							//o-1 debug			        

	);
	
	AXIS_LMAC_TOP AXIS_LMAC_TOP(

	.clk 					(clk),			   			//i-1, 322MHz
	.reset_ 				(reset_),             	    //i-1
	
	.gen_en_wr 				(gen_en_wr),      			//i-1, to initiate the write transaction.
	
	.fmac_speed				(fmac_speed),				//i-3
	
	//Main Signals
	.tx_mac_aclk 			(tx_mac_aclk), 			    //i-1, TX clock.                                                                                                
	.tx_axis_mac_tdata 		(tx_axis_mac_tdata),		//i-DATA_WIDTH, Write data.                                                                                     
	.tx_axis_mac_tvalid		(tx_axis_mac_tvalid),		//i-1, Signal to show if the data is valid.                                                                     
	.tx_axis_mac_tlast 		(tx_axis_mac_tlast),		//i-1, Signal to show the last data byte or quadword.                                                           
	.tx_axis_mac_tuser 		(tx_axis_mac_tuser),		//i-1, Error signal.                                                                                            
	.tx_axis_mac_tstrb 		(tx_axis_mac_tstrb),		//i-8, To show how many bytes of the data is valid.                                                             
	.tx_axis_mac_tready 	(tx_axis_mac_tready),		//o-1, Indicates if the slave is ready.                                                                         
	                                                                                                                                                                    
	//Sideband Signals                                                                                                                                                  
	.tx_ifg_delay 			(tx_ifg_delay),			    //i-1, Control signal for configurable interframe gap                                                           
	.tx_collision 			(tx_collision),			    //o-1, Asserted by the Ethernet MAC core. Any transmission in progress should be aborted. 0 in full-duplex mode.
	.tx_retransmit 			(tx_retransmit),			//o-1, Aborted frame to be retransmitted. 0 in full-duplex mode.                                                
	.tx_statistics_vector 	(tx_statistics_vector),     //o-32,A statistics vector that gives information on the last frame transmitted.                                
	.tx_statistics_valid 	(tx_statistics_valid),      //o-1, Asserted at end of frame transmission, indicating that the tx_statistics_vector is valid.                
	
	//Signals to AXIS Master
	.rx_mac_aclk			(rx_mac_aclk),				//i-1	
	.rx_axis_mac_tdata 		(rx_axis_mac_tdata),		//o-64 	 data signal of bridge module
    .rx_axis_mac_tvalid 	(rx_axis_mac_tvalid),  		//o-1 	 signal to AXIS master indicating the data is valid
    .rx_axis_mac_tlast 		(rx_axis_mac_tlast),		//o-1 	 signal to AXIS Master saying end of data
    .rx_axis_mac_tuser 		(rx_axis_mac_tuser),		//o-1 	 error signal from FMAC
    .rx_axis_filter_tuser 	(rx_axis_filter_tuser),		//o-1 	 error signal from filter of FMAC
    .rx_axis_mac_tstrb 		(rx_axis_mac_tstrb),		//o-8 	 Signal indicating valid bytes inside the qword transmitting
    .rx_statistics_vector 	(rx_statistics_vector),		//o-27 	 information about current frame 
    .rx_statistics_valid 	(rx_statistics_valid),		//o-1	 Signal indication the statistics vector is valid
    
    //Signals from AXIS Master
	.rx_axis_mac_tready 	(rx_axis_mac_tready),		//i-1	signal indicating that AXIS master accepted data
	.rx_axis_compatible_mode(rx_axis_compatible_mode),	//i-1    signal to keep tready always one 
	
	.xA_clk 				(xA_clk),	 				// i-1		156.25 Mhz except for 1G should be 125Mhz
	
	////xgmii signals not used. 20 july 2018				
	.xgmii_txd 				(xgmii_txd),				//o-64
	.xgmii_txc 				(xgmii_txc),				//o-8
	           				     	                	
	.xgmii_rxd 				(xgmii_rxd),				//i-64
	.xgmii_rxc 				(xgmii_rxc),				//i-8 
		                                                
	.host_addr_reg 			(host_addr_reg), 	  		//i-16  		
	.fail_over				(fail_over),	       		//i-1                                   
	.fmac_ctrl				(fmac_ctrl), 		   		//i-32                                  
	.fmac_ctrl1 			(fmac_ctrl1), 	   			//i-32                                  
	.fmac_rxd_en 			(fmac_rxd_en), 	   			//i-1, 13jul11		                        
	.mac_pause_value 		(mac_pause_value),   		//i-32                                  
	.mac_addr0 				(mac_addr0), 		   		//i-48                                  
	.SYS_ADDR 				(SYS_ADDR),		   			//i-4, system assigned addr for the FMAC
	
	.TCORE_MODE				(TCORE_MODE),				//i-1

	.reg_rd_start			(reg_rd_start),        		//i-1 
	.reg_rd_done_out		(reg_rd_done_out),          //o-1 
	.FMAC_REGDOUT			(FMAC_REGDOUT),				//o-32	
	                    	
	.test 					()					    	//o-1

	);
	
	
	phy_emulator_10G phy_emulator_10G(
	
	.x_clk 					(xA_clk),				//i-1, 156.25MHz
	.reset_ 				(reset_),				//i-1
	                                            	
	.fmac_speed				(fmac_speed),       	//i-3
	                                            	
	.rx_pkt_gen_sel 		(rx_pkt_gen_sel),		//i-1
	                                              	
	.xgmii_txd 				(xgmii_txd),          	//i-64
	.xgmii_txc 				(xgmii_txc),          	//i-8
	                		            		
   	.xgmii_rxd				(xgmii_rxd),			//o-64
   	.xgmii_rxc				(xgmii_rxc),			//o-8 
   	
   	.vld_data_flag			(vld_data_flag),		//o-1, will be used for readmem in the memory_compare.v
    
    .test 					()						//o TEST
    
	);

	
	initial begin
		clk		 			<= 0;
		tx_mac_aclk			<= 0;
		rx_mac_aclk			<= 0;
		xA_clk 				<= 0;
	end

	always #1.55	clk	 		<= ~clk; 			//322MHz	 (#number = period div by 2)
	always #1.55	tx_mac_aclk	<= ~tx_mac_aclk; 	//322MHz	
	always #1.55	rx_mac_aclk	<= ~rx_mac_aclk; 	//322MHz	

	always #3.2	 	xA_clk 		<= ~xA_clk; 		//156.25MHz (set to 125MHz for 1G)

	
			
	initial begin
	
		reset_ 			<= 0;
		gen_en_wr		<= 0;
		
		rx_pkt_gen_sel	<= 0;
		
		#200 reset_ 	<= 1;
	
	end
	
	//initialization
	initial begin
		fail_over			<=	1'b0; 			
		fmac_ctrl			<=	32'h00000808;	
		fmac_ctrl1			<=	32'h000005ee;	
		fmac_rxd_en			<=	1'b1;			
		mac_pause_value		<=	32'hffff0000;	
		mac_addr0			<=	48'h001232004eaf;
		SYS_ADDR			<=	4'h1;			
		
		TCORE_MODE			<=	1'b0;	
		
		rx_axis_compatible_mode <= 	1'b1;	
		
		start				<=	1'b1;
		address				<=	16'h0;	
		
	end
	
		
endmodule