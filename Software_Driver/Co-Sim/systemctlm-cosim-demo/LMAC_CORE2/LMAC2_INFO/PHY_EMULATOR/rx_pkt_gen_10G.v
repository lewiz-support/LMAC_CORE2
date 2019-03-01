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

`timescale 1ns/1ps

module rx_pkt_gen_10G(
	x_clk,
	reset_,
	
	fmac_speed,
	
	data_out,
	ctrl_out,
	
	tb_rx_pkt_gen_en,
	tb_rx_pkt_gen_addr_offset,
	tb_rx_pkt_gen_read_cnt,
	
	addr_incr,
	
	test
	);

  input x_clk;
  input reset_;
  
  input	[2:0]	fmac_speed;		//fmac_speed = 3'b000	-	10G
                                //fmac_speed = 3'b001	-	1G
                                //fmac_speed = 3'b010	-	2.5G
                                //fmac_speed = 3'b011	-	RSVD
  								//fmac_speed = 3'b100	-	RSVD
                                //fmac_speed = 3'b101	-	5G
                                //fmac_speed = 3'b110	-	RSVD
                                //fmac_speed = 3'b111	-	RSVD
  

  output reg	[63:0]	data_out;
  output reg	[ 7:0]	ctrl_out;
  
  output reg     		addr_incr;
  
  output 			 	test;				//o-1 debug
  

//=========== signals ===========

  input [10:0]  tb_rx_pkt_gen_read_cnt;		//# of qwds - 1 (if pkt is 7, provide as 6 here)
  input [63:0]  tb_rx_pkt_gen_addr_offset;	//start
  input 	  	tb_rx_pkt_gen_en;			//pulse
  

  reg [10:0]  tb_rx_pkt_gen_read_cnt_int;
  reg [63:0]  tb_rx_pkt_gen_addr_offset_int;
  reg		  tb_rx_pkt_gen_en_dly1;
  
  wire [63:0] d_out;
  wire [ 7:0] c_out;
  reg  [10:0] rx_pkt_gen_addr;
  
  reg	[1:0]	cntr_5g;    
  reg   [1:0]	cntr_2_5g;
  reg   [2:0]	cntr_1g; 
  
  
  parameter[7:0] 
	DAT_0  	= 8'h01 ,
	DAT_1	= 8'h02 ,
	DAT_2	= 8'h04 ,
	DAT_3	= 8'h08 ,
	DAT_4	= 8'h10 ,
	DAT_5	= 8'h20 ,
	DAT_6   = 8'h40 ,
	DAT_7   = 8'h80 ;

  reg [8:0] gmii_state ;

parameter [10:0] MAX_RD_CNT = 180; 		//full rate mix 74 and 192 pkts



assign test = 1'b0;

 
always @ (posedge x_clk)
	begin
		if (!reset_)
			begin
				gmii_state	<= DAT_0;
                data_out   	<= 64'h0707070707070707;	
                ctrl_out	<= 8'hFF;
              
 			 	tb_rx_pkt_gen_read_cnt_int	 <= 11'h0;
 				tb_rx_pkt_gen_addr_offset_int <= 64'h0;
 				tb_rx_pkt_gen_en_dly1	  	 <= 1'b0;
 				
 				rx_pkt_gen_addr		<= 11'h0;
 				
             end //if
           
          else
           begin
           
 		    tb_rx_pkt_gen_en_dly1 <= tb_rx_pkt_gen_en;
 		   
	        tb_rx_pkt_gen_read_cnt_int	<=
	        		//load
	        	tb_rx_pkt_gen_en ? tb_rx_pkt_gen_read_cnt :
	        		//keep
	        	tb_rx_pkt_gen_read_cnt_int; 
	        
	        tb_rx_pkt_gen_addr_offset_int	<= 
	        	//load
	        	tb_rx_pkt_gen_en ? tb_rx_pkt_gen_addr_offset :
	        	//keep
	        	tb_rx_pkt_gen_addr_offset_int;

	 		rx_pkt_gen_addr	<= 
	 				//load
	 				tb_rx_pkt_gen_en_dly1 ? tb_rx_pkt_gen_addr_offset_int :
	 				//reach limit, reloading
	 				//count up
	 				((rx_pkt_gen_addr <= (tb_rx_pkt_gen_addr_offset_int + tb_rx_pkt_gen_read_cnt_int)) & addr_incr) ? rx_pkt_gen_addr+1:	 				
	 				//hold			
	 				rx_pkt_gen_addr;
	 				

			//========== RX_PKT_GEN_PLAYBACK ==========	
			//write byte by byte for 1G gige mode
			if ((fmac_speed == 3'b001) & ((c_out != 8'hff) | ((c_out[0] == 1'b1) & (d_out[7:0] == 8'hFD)) | ((c_out[7] == 1'b1) & (d_out[63:56] == 8'hFB)))) begin
				case(gmii_state)
        	
					DAT_0:	// Transmit Byte 0
					begin
						
						gmii_state	<= 	DAT_1;
        			
						data_out 	<= 	{56'h07070707070707, d_out[7:0]};
						ctrl_out 	<= 	{7'b1111111, c_out[0]};
					
					end
					
					DAT_1:	// Transmit Byte 1
					begin
					
						gmii_state	<= 	DAT_2;
        			
						data_out 	<= 	{56'h07070707070707, d_out[15:8]};
						ctrl_out 	<= 	{7'b1111111, c_out[1]};
						
					end
					
					DAT_2:	// Transmit Byte 2
					begin
						
						gmii_state	<= 	DAT_3;
        			
						data_out 	<= 	{56'h07070707070707, d_out[23:16]};
						ctrl_out 	<= 	{7'b1111111, c_out[2]};
						
					end
					
					DAT_3:	// Transmit Byte 3
					begin
					
						gmii_state	<= 	DAT_4;
        			
						data_out 	<= 	{56'h07070707070707, d_out[31:24]};
						ctrl_out 	<= 	{7'b1111111, c_out[3]};
						
					end
					
					DAT_4:	// Transmit Byte 4
					begin
					
						gmii_state	<= 	DAT_5;
        			
						data_out 	<= 	{56'h07070707070707, d_out[39:32]};
						ctrl_out 	<= 	{7'b1111111, c_out[4]};
						
					end
					
					DAT_5:	// Transmit Byte 5
					begin
					
						gmii_state	<= 	DAT_6;
        			
						data_out 	<= 	{56'h07070707070707, d_out[47:40]};
						ctrl_out 	<= 	{7'b1111111, c_out[5]};
						
					end
					
					DAT_6:	// Transmit Byte 6
					begin
					
						gmii_state	<= 	DAT_7;
        			
						data_out 	<= 	{56'h07070707070707, d_out[55:48]};
						ctrl_out 	<= 	{7'b1111111, c_out[6]};
						
					end
					
					DAT_7:	// Transmit Byte 7
					begin
						
						gmii_state	<= 	DAT_0;
        			
						data_out 	<= 	{56'h07070707070707, d_out[63:56]};
						ctrl_out 	<= 	{7'b1111111, c_out[7]};
						
					end
					
					default:
					begin
						gmii_state 	<=	DAT_0;
					end
			
				endcase
			end
			
			//write entire QWD for 10, 5 and 2.5 GIG mode
			else begin
				data_out  	<= d_out	;
				ctrl_out	<= c_out	;
			end	
			                      	  
	       end //else
		
	end	//always
	
	
always @ (posedge x_clk) begin

	if(!reset_)
		begin
		
			cntr_5g			<=	1'b0;
			cntr_2_5g		<=	2'b0;
			cntr_1g			<=	3'b0;
			addr_incr		<=	1'b0;

		end
		
	else
		begin
		
			//start counter at every 'tb_rx_pkt_gen_en'
			if (tb_rx_pkt_gen_en) begin
			
				cntr_5g			<=	1'b0;
				cntr_2_5g		<=	2'b0;
				cntr_1g			<=	3'b0;
				addr_incr		<=	1'b0;
			
			end
			else begin
		
				case (fmac_speed)
				
					//10G increment address at every clk
					3'b000: begin
					
								addr_incr		<=	1'b1;
					
							end
					
					//1G increment address after every 8 clks		
					3'b001: begin
					
								cntr_1g			<=	cntr_1g + 1'b1;
								
								if (cntr_1g == 3'b111) begin
									addr_incr	<=	1'b1;
									cntr_1g		<=	3'b0;
								end
								else
									addr_incr	<=	1'b0;
					
							end
						
					//2.5G increment address after every 4 clks	
					3'b010: begin
								
								cntr_2_5g		<=	cntr_2_5g + 1'b1;
								
								if (cntr_2_5g == 2'b11) begin
									addr_incr	<=	1'b1;
									cntr_2_5g	<=	2'b0;
								end
								else
									addr_incr	<=	1'b0;
									
							end
					
					//5G increment address after every 2 clks		
					3'b101: begin
					
								cntr_5g		<=	cntr_5g + 1'b1;
								
								if (cntr_5g == 1'b1) begin
									addr_incr	<=	1'b1;
									cntr_5g		<=	1'b0;
								end
								else
									addr_incr	<=	1'b0;
									
							end
							
					default: begin
					
								cntr_5g			<=	1'b0;
								cntr_2_5g		<=	2'b0;
								cntr_1g			<=	3'b0;
								addr_incr		<=	1'b0;
					
							end
							
				endcase
				
			end
		
		end
		
end
		

//synopsys translate_off
reg [(32*8)-1 : 0] ascii_gmii_state;

always@(gmii_state)
begin
	case(gmii_state)
	DAT_0: 	ascii_gmii_state = "DAT_0";
	DAT_1: 	ascii_gmii_state = "DAT_1";
	DAT_2: 	ascii_gmii_state = "DAT_2";
	DAT_3: 	ascii_gmii_state = "DAT_3";
	DAT_4: 	ascii_gmii_state = "DAT_4";
	DAT_5: 	ascii_gmii_state = "DAT_5";
	DAT_6: 	ascii_gmii_state = "DAT_6";
	DAT_7: 	ascii_gmii_state = "DAT_7";
	default:ascii_gmii_state = "unknown";
	endcase
end
//synopsys translate_on

	

//========== STORAGE ==========	

rx_pkt_gen2kx64 rx_pkt_gen2kx64_inst (
	
	.data		(64'b0),
	.rdaddress 	(rx_pkt_gen_addr),
	.clock 		(x_clk),
	.wraddress 	(11'b0),
	.wren 		(1'b0),
	.q 			(d_out)               
	
	);
	
rx_pkt_gen2kx8 rx_pkt_gen2kx8_inst (
	
	.data		(8'b0),
	.rdaddress 	(rx_pkt_gen_addr),
	.clock 		(x_clk),
	.wraddress 	(11'b0),
	.wren 		(1'b0),
	.q 			(c_out)               

	);
	
endmodule
