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

module memory_compare_8b(

	rx_mac_aclk,			//i, RX Clock
	reset_,        			//i,
	
	axis_rd_done_st,        //i, self check works at every read_done state 
	
	vld_data_flag,			//i-1, will be used for readmem in the memory_compare.v   
	   	
	pkt_cnt,				//i
	
	rx_axis_mac_tvalid,		//i
	rx_axis_mac_tbcnt       //i
	
	);

	parameter DATA_WIDTH = 64;
	parameter BCNT_WIDTH = 32;
	
	input 							rx_mac_aclk;				//i, RX Clock
	input							reset_;						//i, 
	
	input							axis_rd_done_st;			//i, self check works at every read_done state
	                                                             
	input		[31 : 0]			pkt_cnt;					//i, number of incoming packets
	
	input							rx_axis_mac_tvalid;			//i
    input		[BCNT_WIDTH-1 : 0]	rx_axis_mac_tbcnt;			//i
    
    input							vld_data_flag;				//i-1, will be used for readmem in the memory_compare.v   
    
   	reg								axis_rd_done_st_dly1;		//self check works at every read_done state
	                                        
	reg 		[ 7 : 0] 			memory_rd_data [0:65535];	//Depth = 2^13 = 8192 for now
	reg 		  					memory_rd_ctrl [0:65535];	
	reg 		[ 7 : 0] 			memory_wr_data [0:65535];	
	
	integer							i;							//stores the index to help find the wrong data.
	integer							mem_rd_start_address;		//to store start address for each packet.
	integer							mem_rd_end_address;			//to store end address for each packet.
	
	reg								is_error;					//this signal will show if the packet is received succesfully or error is present.

	
	always @ (posedge rx_mac_aclk)
		axis_rd_done_st_dly1	<=	axis_rd_done_st;
		
		
	
	always @ (rx_axis_mac_tvalid) begin
	
		if (rx_axis_mac_tvalid)
			mem_rd_start_address = mem_rd_end_address;
	
	end

	
	always @ (negedge vld_data_flag) begin
		$readmemh("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", memory_wr_data);							//read memory file at every rd_done_state
	end
	
	
	always @ (axis_rd_done_st_dly1) begin

		if (!reset_) begin
		
			mem_rd_start_address	=	0;
			mem_rd_end_address  	=	0;
			i						=	0;
			is_error            	=	1'b0;
		
		end
	
		else if (axis_rd_done_st_dly1) begin

			$readmemh("C:/LMAC2_INFO/AXIS_MASTER/data_8b_received_file.txt", memory_rd_data);			//read memory file at every rd_done_state
			$readmemb("C:/LMAC2_INFO/AXIS_MASTER/ctrl_8b_received_file.txt", memory_rd_ctrl);			//read memory file at every rd_done_state
			//$readmemh("C:/LMAC2_INFO/PHY_EMULATOR/data_file.txt", memory_wr_data);					//read memory file at every rd_done_state
			
			//start address + bcnt + 8 bytes of D5555555555555FB + 4 Bytes CRC and 1 Byte FD.
			mem_rd_end_address	=	mem_rd_start_address + rx_axis_mac_tbcnt + 13;
			
		
		end
		else begin
		
			for (i = mem_rd_start_address; i < mem_rd_end_address; i = i+1) begin
			
			   //if first packet, then initialize is_error to zero.
				if (i == mem_rd_start_address)
					is_error = 1'b0;
			
				if (memory_rd_ctrl[i] == 1'b1) begin
				
				   //display error message if data does not match
					if (memory_rd_data[i] != memory_wr_data[i]) begin
						$display("\n**ERROR: Byte at index %0d of Packet No.: %0d does not match.", i, pkt_cnt);
						$display("**Expected Data Byte: %h \tbut, we received: %h", memory_wr_data[i], memory_rd_data[i]);
						is_error = 1'b1;	
					end
					
				end
        
			end
			
			//if last data, and packet is received successfully then display PASSED message.
			if ((i == mem_rd_end_address) & (is_error == 0))
				$display("\n**PASSED: Packet No.: %0d \tis received as expected.", pkt_cnt);
		
		end
				
	end

endmodule