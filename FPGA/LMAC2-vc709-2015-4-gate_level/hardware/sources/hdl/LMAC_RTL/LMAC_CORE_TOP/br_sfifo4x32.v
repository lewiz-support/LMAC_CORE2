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


module br_sfifo4x32

(
			 aclr,

			wrclk,     	   //i,Clk for writing data 
			wrreq,     	   //i, request to write 
			data,          //i, Data coming in           
			wrfull,    	   //o,indicates fifo is full or not (To avoid overiding)
                       
		    rdclk,     	   //i, Clk for reading data
			rdreq,     	   //i, Request to read from FIFO
			q, 	    	  //o, Data coming out
			rdempty,  	   //o, indicates fifo is empty or not (to avoid underflow)
			rdusedw    	   //o, number of slots currently in use for reading

);	  //setting default values
	parameter WIDTH = 32,
			  DEPTH = 4,
			  PTR	= 2;
			  
			  
			input wire aclr;

			input  wire 				wrclk;   	// Clk for writing data
			input  wire 				wrreq;   	// request to write
			input  wire [WIDTH-1 : 0]	data;    	// Data coming in 
			output wire					wrfull;  	// indicates fifo is full or not (To avoid overiding)
		                                         
		    input  wire 				rdclk;   	// Clk for reading data
			input  wire 				rdreq;   	// Request to read from FIFO 
			output wire [WIDTH-1 : 0]	q; 	    	// Data coming out
			output wire 				rdempty; 	// indicates fifo is empty or not (to avoid underflow)
			output wire [PTR  : 0] 		rdusedw; 	// number of slots currently in use for reading


            wire		[PTR+1  : 0]	data_count;     // number of slots currently in use for writting  

	assign	rdusedw	=	{data_count[2:0]};
	
	
	//ACTUAL DEPTH of the FIFO_IP is 16, as VIVADO does not provide FIFO with depth of 4.
	br_sfifo_ip_4x32 	
						//#(.WIDTH (8),		
					  	//	  .DEPTH (4096),
					 	//	  .PTR	 (12) )		
 											
    br_sfifo_ip_4x32 (
			.srst	(aclr),		
			
			.clk	(wrclk),			// Clk to write data
			.wr_en	(wrreq),	      	// write enable                                                
			.din	(data),		  		// write data                                                 
			.full	(wrfull),	      	// indicates fifo is full or not (To avoid overiding)           
			.data_count(data_count),	// wrusedw -number of locations filled in fifo
                                                                                                               
			.rd_en	(rdreq),	     	// i-1, read enable of data FIFO                                    
			.dout	(q),		     	// Dataout of data FIFO                              
			.empty	(rdempty)	    	// indicates fifo is empty or not (to avoid underflow)      
		 );
		 
		 
endmodule