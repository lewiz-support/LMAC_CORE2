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

module phy_emulator_10G(
	
	x_clk,		//i
	reset_,			//i
	
	fmac_speed,		//i
	
	rx_pkt_gen_sel,	//i
	
	xgmii_txd, 		//i-64   	
	xgmii_txc,    	//i-8
	
   	xgmii_rxd,      //o-64
   	xgmii_rxc,      //o-8 
   	
	vld_data_flag,	//o-1, will be used for readmem in the memory_compare.v
   	
    test			//o TEST
    
	);

	input 				x_clk;				//i
	input 				reset_;					//i
	
	input	[2 : 0]		fmac_speed;				//fmac_speed = 3'b000	-	10G
                               					//fmac_speed = 3'b001	-	1G
                               					//fmac_speed = 3'b010	-	2.5G
                               					//fmac_speed = 3'b011	-	RSVD
  												//fmac_speed = 3'b100	-	RSVD
                               					//fmac_speed = 3'b101	-	5G
                               					//fmac_speed = 3'b110	-	RSVD
                               					//fmac_speed = 3'b111	-	RSVD
	
	input				rx_pkt_gen_sel;			//i
	
	
	//xgmii 30 aug 2018
	input		[63: 0]		xgmii_txd;
	input 		[ 7: 0]		xgmii_txc;
			
	output reg	[63: 0]		xgmii_rxd;
    output reg	[ 7: 0]		xgmii_rxc;
    
	output reg				vld_data_flag;		//o-1, shows valid data and will be used for readmem in the memory_compare.v
                                            
    output 				test;					//o TEST
    
    reg					rx_pkt_gen_en;
    reg		[63 : 0]	rx_pkt_gen_start_addr;
    reg		[10 : 0]	rx_pkt_gen_read_cnt;
    
    wire	[63 : 0]	rx_pkt_gen_data_out;
    wire	[ 7 : 0]	rx_pkt_gen_ctrl_out;
    
   	integer				data_file;
   	integer				ctrl_file;
   	integer				k, n;				//number of packets - 8-bit mode
   	
   	reg					sof;
   	wire				addr_incr;
   	   	
    
    rx_pkt_gen_10G rx_pkt_gen_10G(
	
    .x_clk 					(x_clk),					//i
	.reset_ 				(reset_),                   //i
	
	.fmac_speed				(fmac_speed),				//i
	
	.data_out 				(rx_pkt_gen_data_out),      //o-64
	.ctrl_out 				(rx_pkt_gen_ctrl_out),      //o-8
	
	.tb_rx_pkt_gen_en 			(rx_pkt_gen_en),         	//i
	.tb_rx_pkt_gen_addr_offset	(rx_pkt_gen_start_addr),   	//i
	.tb_rx_pkt_gen_read_cnt 	(rx_pkt_gen_read_cnt),   	//i
	
	.addr_incr				(addr_incr),				//o
	
	.test 					(test)
	
	);
    
	
	always @ (posedge x_clk)
	begin
	
		if (!reset_)
		begin
			rx_pkt_gen_start_addr	<=	64'b0;
			rx_pkt_gen_read_cnt		<=	11'b0;
			
			rx_pkt_gen_en		<=	1'b0;
			
			xgmii_rxd 	<= 	64'h0707070707070707;
			xgmii_rxc 	<= 	8'hff;
		
		end
		
		else
		begin
			
			//final output depending on 'rx_pkt_gen_sel' signal
			xgmii_rxd 	<= 	(rx_pkt_gen_sel)? 	rx_pkt_gen_data_out 	: 	xgmii_txd;
			xgmii_rxc 	<= 	(rx_pkt_gen_sel)? 	rx_pkt_gen_ctrl_out 	: 	xgmii_txc;
									
		end
		
	end
	
	initial begin
	
		data_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", "w"); 		//open file
		ctrl_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/ctrl_file.txt", "w"); 		//open file
		
		//write Copyright info and first line description at the beginning of every file created by phy_emulator
		$fdisplay (data_file, "// Copyright (C) 2018 LeWiz Communications, Inc.");
		$fdisplay (data_file, "//\n// This library is free software; you can redistribute it and/or");
		$fdisplay (data_file, "// modify it under the terms of the GNU Lesser General Public");
		$fdisplay (data_file, "// License as published by the Free Software Foundation; either");
		$fdisplay (data_file, "// version 2.1 of the License, or (at your option) any later version.");
		$fdisplay (data_file, "//\n// This library is distributed in the hope that it will be useful,");
		$fdisplay (data_file, "// but WITHOUT ANY WARRANTY; without even the implied warranty of");
		$fdisplay (data_file, "// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU");
		$fdisplay (data_file, "// Lesser General Public License for more details.");
		$fdisplay (data_file, "//\n// You should have received a copy of the GNU Lesser General Public");
		$fdisplay (data_file, "// License along with this library release; if not, write to the Free Software");
		$fdisplay (data_file, "// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA");
		$fdisplay (data_file, "//\n// LeWiz can be contacted at:  support@lewiz.com");
		$fdisplay (data_file, "// or address:");
		$fdisplay (data_file, "// PO Box 9276");
		$fdisplay (data_file, "// San Jose, CA 95157-9276");
		$fdisplay (data_file, "// www.lewiz.com");
		$fdisplay (data_file, "//\n//    Author: LeWiz Communications, Inc.");
		$fdisplay (data_file, "//    Language: Verilog");
		$fdisplay (data_file, "//\n//\n\n//This file stores the 64 bit data (XGMII_RXD) which needs to be compared with received data (AXIS Master input).");

		$fdisplay (ctrl_file, "// Copyright (C) 2018 LeWiz Communications, Inc.");
		$fdisplay (ctrl_file, "//\n// This library is free software; you can redistribute it and/or");
		$fdisplay (ctrl_file, "// modify it under the terms of the GNU Lesser General Public");
		$fdisplay (ctrl_file, "// License as published by the Free Software Foundation; either");
		$fdisplay (ctrl_file, "// version 2.1 of the License, or (at your option) any later version.");
		$fdisplay (ctrl_file, "//\n// This library is distributed in the hope that it will be useful,");
		$fdisplay (ctrl_file, "// but WITHOUT ANY WARRANTY; without even the implied warranty of");
		$fdisplay (ctrl_file, "// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU");
		$fdisplay (ctrl_file, "// Lesser General Public License for more details.");
		$fdisplay (ctrl_file, "//\n// You should have received a copy of the GNU Lesser General Public");
		$fdisplay (ctrl_file, "// License along with this library release; if not, write to the Free Software");
		$fdisplay (ctrl_file, "// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA");
		$fdisplay (ctrl_file, "//\n// LeWiz can be contacted at:  support@lewiz.com");
		$fdisplay (ctrl_file, "// or address:");
		$fdisplay (ctrl_file, "// PO Box 9276");
		$fdisplay (ctrl_file, "// San Jose, CA 95157-9276");
		$fdisplay (ctrl_file, "// www.lewiz.com");
		$fdisplay (ctrl_file, "//\n//    Author: LeWiz Communications, Inc.");
		$fdisplay (ctrl_file, "//    Language: Verilog");		
		$fdisplay (ctrl_file, "//\n//\n\n//This file stores the 08 bit ctrl (XGMII_RXC) which needs to be compared with received ctrl (AXIS Master input).");
	    
		$fclose(data_file);
		$fclose(ctrl_file);
		
	end
	
	always @ (posedge x_clk)
	begin
	
		if (!reset_)
		begin
			
			n	 =	1;
			k	 =	0;
			sof	 =	1'b0;
			
			vld_data_flag	=	1'b0;
			
		end
		
		else
		begin
				
			//write file for 1 GIG mode				
			if (fmac_speed == 3'd1) begin
				if (((xgmii_rxd[7:0] == 8'hFB)&(xgmii_rxc[0])) | (vld_data_flag == 1'b1)) begin
					
					//start of 8-bit data	
					if ((xgmii_rxd[7:0] == 8'hFB)&(xgmii_rxc[0])) begin
					
						vld_data_flag = 1'b1;	
					
						data_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", "a"); 		//open file	
						ctrl_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/ctrl_file.txt", "a"); 		//open file		
					
						$fdisplay (data_file, "\n\n//pkt - %0d\n", n);		//add new line at the start of each packet and write the packet numbers.	
						$fdisplay (ctrl_file, "\n\n//pkt - %0d\n", n);		//add new line at the start of each packet and write the packet numbers.
									
					end
					
					$fdisplayh (data_file, xgmii_rxd[7:0], "\t\t//Index: %3d\tPkt No.: %0d", k, n);		//write data to the text file.	
					$fdisplayb (ctrl_file, xgmii_rxc[0]  , "\t\t//Index: %3d\tPkt No.: %0d", k, n);		//write ctrl to the text file.
					
					k	=	k + 1;
					
					//end of 8-bit data
					if ((xgmii_rxd[7:0] == 8'hFD)&(xgmii_rxc[0])) begin
						n	=	n + 1;
						
						$fclose(data_file);
						$fclose(ctrl_file);
						
						vld_data_flag = 1'b0;
					end
				end
			end
			
			//write file for 10, 5 and 2.5 GIG mode	
			else if (addr_incr & (fmac_speed != 3'd1)) begin
			
				//detect end of packet, write last data and close file
				if (sof) begin
				casex ({xgmii_rxd, xgmii_rxc})			
					{64'hfd??????????????, 8'b10000000} :	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	//write data to the text file.	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	//write ctrl to the text file.
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[31:24], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[3], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[39:32], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[4], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[47:40], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[5], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[55:48], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[6], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[63:56], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[7], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);																			
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h??fd????????????, 8'b?1000000} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[31:24], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[3], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[39:32], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[4], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[47:40], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[5], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[55:48], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[6], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);															                                         
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h????fd??????????, 8'b??100000} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[31:24], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[3], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[39:32], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[4], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[47:40], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[5], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);																                                         
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h??????fd????????, 8'b???10000} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[31:24], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[3], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[39:32], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[4], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);														                                         
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h????????fd??????, 8'b????1000} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[31:24], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[3], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);														                                         
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h??????????fd????, 8'b?????100} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[23:16], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[2], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);														                                         
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h????????????fd??, 8'b??????10} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																k	=	k + 1;
																                                         
																$fdisplayh (data_file, xgmii_rxd[15:8],  "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[1], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);													                                         								
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
					                                      	
					{64'h??????????????fd, 8'b???????1} : 	begin
																sof = 1'b0;
																
																$fdisplayh (data_file, xgmii_rxd[7:0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
																$fdisplayb (ctrl_file, xgmii_rxc[0], 	 "\t\t//Index: %3d\tPkt No.: %0d", k, n);					
																k	=	k + 1;
																
																n	=	n + 1;
																$fclose(data_file);
																$fclose(ctrl_file);
																
																vld_data_flag = 1'b0;
															end
				endcase
				end
			
				//detect start of packet, open file and write first data
				casex ({xgmii_rxd, xgmii_rxc})
					{64'hfb??????????????, 8'b1???????} : 	begin
															sof = 1'b0;
															end
						
					{64'h55fb????????????, 8'b01??????} : 	begin
															sof = 1'b0;
															end
						
					{64'h5555fb??????????, 8'b001?????} : 	begin
															sof = 1'b0;
															end
						
					{64'h555555fb????????, 8'b0001????} : 	begin
					
															vld_data_flag = 1'b1;
					
															sof = 1'b1;
															data_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", "a"); 	
															ctrl_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/ctrl_file.txt", "a"); 	
					    									
															$fdisplay (data_file, "\n\n//pkt - %0d\n", n);							
															$fdisplay (ctrl_file, "\n\n//pkt - %0d\n", n);							
																														              
															$fdisplayh (data_file, xgmii_rxd[39:32],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[4], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[47:40],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[5], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[55:48],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[6], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[63:56],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[7], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															
															end
						
					{64'h55555555fb??????, 8'b00001???} : 	begin
															sof = 1'b0;
															end
						
					{64'h5555555555fb????, 8'b000001??} : 	begin
															sof = 1'b0;
															end
						
					{64'h555555555555fb??, 8'b0000001?} : 	begin
															sof = 1'b0;
															end
						
					{64'hD5555555555555fb, 8'b00000001} : 	begin
					
															vld_data_flag = 1'b1;
					
															sof = 1'b1;
															data_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", "a"); 	
															ctrl_file 	= $fopen("C:/LMAC2_INFO/PHY_EMULATOR/ctrl_file.txt", "a"); 	
					    									
															$fdisplay (data_file, "\n\n//pkt - %0d\n", n);							
															$fdisplay (ctrl_file, "\n\n//pkt - %0d\n", n);							
															
															$fdisplayh (data_file, xgmii_rxd[7:0], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[0], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                        
															$fdisplayh (data_file, xgmii_rxd[15:8], "\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[1], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                        
															$fdisplayh (data_file, xgmii_rxd[23:16],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[2], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[31:24],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[3], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[39:32],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[4], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[47:40],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[5], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[55:48],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[6], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															k	=	k + 1;
															                                         
															$fdisplayh (data_file, xgmii_rxd[63:56],"\t\t//Index: %3d\tPkt No.: %0d", k, n);	
															$fdisplayb (ctrl_file, xgmii_rxc[7], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);																										
															k	=	k + 1;
																														
															end                                                         	
					
					default: begin
				
						//if (valid_data) then write data into the file.
						if (sof) begin
						
							$fdisplayh (data_file, xgmii_rxd[7:0], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[0], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                        
							$fdisplayh (data_file, xgmii_rxd[15:8], "\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[1], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                        
							$fdisplayh (data_file, xgmii_rxd[23:16],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[2], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                         
							$fdisplayh (data_file, xgmii_rxd[31:24],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[3], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                         
							$fdisplayh (data_file, xgmii_rxd[39:32],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[4], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                         
							$fdisplayh (data_file, xgmii_rxd[47:40],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[5], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                         
							$fdisplayh (data_file, xgmii_rxd[55:48],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[6], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							                                         
							$fdisplayh (data_file, xgmii_rxd[63:56],"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							$fdisplayb (ctrl_file, xgmii_rxc[7], 	"\t\t//Index: %3d\tPkt No.: %0d", k, n);
							k	=	k + 1;
							
						end
						
					end
					
				endcase
			
			end
				
		end
		
	end
	
endmodule