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

module memory_rd_8b_module(

	rx_mac_aclk,				 //i, RX Clock
	reset_,        				 //i,
	
    //outputs to drive the AXI bus
	mem_axis_rdata,    			//i, read_data to store in a text file
	                            
	mem_rd_address,       		//i, address to access the memory
	mem_axis_rstrb,				//i, read_strobe to store in a text file
	rd_done,					//i, indicates that the read transaction is done
	rx_axis_mac_tvalid,         //i, to write to memory as long as valid data is high.     
	rx_axis_mac_tlen,           //i, holds the length of the received data
	
	rx_pkt_gen_sel,				//i
	
	mem_rd_start_address,		//o
	
	pkt_cnt						//o
	                            
	);
	
	parameter ADDR_WIDTH = 32;			 //default
	parameter DATA_WIDTH = 64;
	parameter BCNT_WIDTH = 32;
	
	input								rx_mac_aclk;			 //i, RX Clock
	input								reset_;  				 //i,
	input		[DATA_WIDTH-1 : 0]		mem_axis_rdata;			 //i, read_data to store in a text file
	input		[ADDR_WIDTH-1 : 0]		mem_rd_address;			 //i, address to access the memory
	input		[ 7 : 0]				mem_axis_rstrb;			 //i, read_strobe to store in a text file
	
	input								rd_done;				 //i, indicates that the read transaction is done
	input								rx_axis_mac_tvalid;       //i, to write to memory as long as valid data is high.                 
	input		[31 : 0]				rx_axis_mac_tlen;         //i, holds the length of the received data
	                                        
	input								rx_pkt_gen_sel;			  //i
	
	output reg	[ADDR_WIDTH-1 : 0]		mem_rd_start_address;	  //o, start address for each packet
	
	output reg	[31 : 0]				pkt_cnt;				  //packet count
	
	reg 		[ 7 : 0] 				memory_rd_ctrl [0:65535];	//Depth = 2^11 = 2048 for now
	reg 		[DATA_WIDTH-1 : 0]		memory_rd_data [0:65535];
	
	integer								data_8b_received_file;
	integer								ctrl_8b_received_file;
	
	integer								i, j;	
	

	initial begin
	
		data_8b_received_file 	= $fopen("C:/LMAC2_INFO/AXIS_MASTER/data_8b_received_file.txt", "w"); 		//open file
		ctrl_8b_received_file 	= $fopen("C:/LMAC2_INFO/AXIS_MASTER/ctrl_8b_received_file.txt", "w"); 		//open file
		
		//write Copyright header and first line description at beginning of the file created
		$fdisplay (data_8b_received_file, "// Copyright (C) 2018 LeWiz Communications, Inc.");
		$fdisplay (data_8b_received_file, "//\n// This library is free software; you can redistribute it and/or");
		$fdisplay (data_8b_received_file, "// modify it under the terms of the GNU Lesser General Public");
		$fdisplay (data_8b_received_file, "// License as published by the Free Software Foundation; either");
		$fdisplay (data_8b_received_file, "// version 2.1 of the License, or (at your option) any later version.");
		$fdisplay (data_8b_received_file, "//\n// This library is distributed in the hope that it will be useful,");
		$fdisplay (data_8b_received_file, "// but WITHOUT ANY WARRANTY; without even the implied warranty of");
		$fdisplay (data_8b_received_file, "// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU");
		$fdisplay (data_8b_received_file, "// Lesser General Public License for more details.");
		$fdisplay (data_8b_received_file, "//\n// You should have received a copy of the GNU Lesser General Public");
		$fdisplay (data_8b_received_file, "// License along with this library release; if not, write to the Free Software");
		$fdisplay (data_8b_received_file, "// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA");
		$fdisplay (data_8b_received_file, "//\n// LeWiz can be contacted at:  support@lewiz.com");
		$fdisplay (data_8b_received_file, "// or address:");
		$fdisplay (data_8b_received_file, "// PO Box 9276");
		$fdisplay (data_8b_received_file, "// San Jose, CA 95157-9276");
		$fdisplay (data_8b_received_file, "// www.lewiz.com");
		$fdisplay (data_8b_received_file, "//\n//    Author: LeWiz Communications, Inc.");
		$fdisplay (data_8b_received_file, "//    Language: Verilog");
		$fdisplay (data_8b_received_file, "//\n//\n\n//This file stores the 8 bit received data which needs to be compared with transmitted data (FMAC input).");
		
		$fdisplay (ctrl_8b_received_file, "// Copyright (C) 2018 LeWiz Communications, Inc.");
		$fdisplay (ctrl_8b_received_file, "//\n// This library is free software; you can redistribute it and/or");
		$fdisplay (ctrl_8b_received_file, "// modify it under the terms of the GNU Lesser General Public");
		$fdisplay (ctrl_8b_received_file, "// License as published by the Free Software Foundation; either");
		$fdisplay (ctrl_8b_received_file, "// version 2.1 of the License, or (at your option) any later version.");
		$fdisplay (ctrl_8b_received_file, "//\n// This library is distributed in the hope that it will be useful,");
		$fdisplay (ctrl_8b_received_file, "// but WITHOUT ANY WARRANTY; without even the implied warranty of");
		$fdisplay (ctrl_8b_received_file, "// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU");
		$fdisplay (ctrl_8b_received_file, "// Lesser General Public License for more details.");
		$fdisplay (ctrl_8b_received_file, "//\n// You should have received a copy of the GNU Lesser General Public");
		$fdisplay (ctrl_8b_received_file, "// License along with this library release; if not, write to the Free Software");
		$fdisplay (ctrl_8b_received_file, "// Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA");
		$fdisplay (ctrl_8b_received_file, "//\n// LeWiz can be contacted at:  support@lewiz.com");
		$fdisplay (ctrl_8b_received_file, "// or address:");
		$fdisplay (ctrl_8b_received_file, "// PO Box 9276");
		$fdisplay (ctrl_8b_received_file, "// San Jose, CA 95157-9276");
		$fdisplay (ctrl_8b_received_file, "// www.lewiz.com");
		$fdisplay (ctrl_8b_received_file, "//\n//    Author: LeWiz Communications, Inc.");
		$fdisplay (ctrl_8b_received_file, "//    Language: Verilog");
		$fdisplay (ctrl_8b_received_file, "//\n//\n\n//This file stores the 1 bit received ctrl which needs to be compared with transmitted ctrl (FMAC input).");
	
		$fclose(data_8b_received_file);
		$fclose(ctrl_8b_received_file);
		
		i		=	0;		 //index from packet start to packet end.
		j		=	0;		 //stores the index to print inside the text file.
		
		pkt_cnt	=	0;		 //stores the packet count to print inside the text file.
		
		mem_rd_start_address = 32'b0;
		
	end
	
	always @ (posedge rx_mac_aclk) begin
	
		if (rx_axis_mac_tvalid) begin
		  //write data and strobe to memories
			memory_rd_data [mem_rd_address]	 <=	 mem_axis_rdata;
			memory_rd_ctrl [mem_rd_address]	 <=	 mem_axis_rstrb;	
		end
	
	end
	  
	
	always @ (rx_axis_mac_tvalid) begin
			//always at start of tvalid, take the read address as start address.
		if (rx_axis_mac_tvalid)
			mem_rd_start_address = mem_rd_address;
	
	end
	
	always @ (rd_done) begin
	
		if (rd_done) begin
		
			pkt_cnt	=	pkt_cnt	+	1;	   //at every read done, pkt_cnt = pkt_cnt + 1.
			
			data_8b_received_file 	= $fopen("C:/LMAC2_INFO/AXIS_MASTER/data_8b_received_file.txt", "a");	  //open file
			ctrl_8b_received_file 	= $fopen("C:/LMAC2_INFO/AXIS_MASTER/ctrl_8b_received_file.txt", "a");
		
			$fdisplay (data_8b_received_file, "\n\n//pkt - %0d\n", pkt_cnt);			 //add new line packet number
			$fdisplay (ctrl_8b_received_file, "\n\n//pkt - %0d\n", pkt_cnt);
		
			$fdisplayh (data_8b_received_file, 8'hFB, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
			$fdisplayb (ctrl_8b_received_file, 1'b1, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt  );
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'h55, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			$fdisplayh (data_8b_received_file, 8'hD5, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			$fdisplayb (ctrl_8b_received_file, 1'b0, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
			j = j+1;
			
			for (i = mem_rd_start_address; i < mem_rd_address; i = i+1) begin
			
			  //if last data, check the control and write only valid data.
				if (i == (mem_rd_address - 1)) begin
					case (memory_rd_ctrl[i])
					
						8'hff: 	begin
								   //write entire QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][39:32], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][4]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][47:40], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][5]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][55:48], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);			
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][6]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][63:56], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);												
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][7]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h7f: 	begin
								   //write 7 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][39:32], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][4]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][47:40], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][5]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][55:48], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][6]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h3f: 	begin
									//write 6 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][39:32], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][4]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][47:40], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][5]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h1f: 	begin
									//write 5 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][39:32], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][4]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h0f: 	begin
									//write 4 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h07: 	begin
									//write 3 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h03: 	begin
									//write 2 bytes of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
									
									$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						8'h01: 	begin
									//write 1 byte of the QWD to the text file.
									$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);									
									$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
									j = j+1;
								end
						default:begin
						
								end
					
					endcase
					
					//write CRC data to the text file.
					$fdisplayh (data_8b_received_file, 8'hC1, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, 1'b0 , "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, 8'hC2, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, 1'b0 , "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, 8'hC3, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, 1'b0 , "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, 8'hC4, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, 1'b0 , "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, 8'hFD, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, 1'b0 , "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
				end
				else begin
					//write the data to the text file.
					$fdisplayh (data_8b_received_file, memory_rd_data [i][ 7: 0], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][0]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][15: 8], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][1]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][23:16], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][2]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][31:24], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][3]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][39:32], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][4]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][47:40], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][5]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][55:48], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][6]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
					
					$fdisplayh (data_8b_received_file, memory_rd_data [i][63:56], "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);					
					$fdisplayb (ctrl_8b_received_file, memory_rd_ctrl [i][7]	, "\t\t//Index: %3d\tPkt No.: %0d", j, pkt_cnt);
					j = j+1;
				end

			end
		
		end
		
		else begin
		
		    $fclose(data_8b_received_file);
			$fclose(ctrl_8b_received_file);
		
		end

	end
     
	
endmodule