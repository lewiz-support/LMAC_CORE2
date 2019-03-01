// The following COPYRIGHT and legend (marked as comment "//") are applicable for this
// README file and the images (*.PNG file) associated with this test.
//
//
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

--> Case06-Test02                                                                                                                          
                                                                                                                                           
	- Packet Gap				 : 10 Bytes of idle patterns                                                                                               
	                                                                                                                                          
	- Packet1 : Broadcast		 : 1st QWD Destination MAC: "ffff_ffff_ffff"                                                                       
				Normal IP Packet : 2nd QWD "0045_0008"                                                                                                 
				Size			 : 1371 Bytes                                                                                                                   
				                                                                                                                                       
	                                                                                                                                          
	- Packet2 : Multicast		 : 1st QWD Destination MAC: "0000_005e_0001"                                                                        
				Normal IP Packet : 2nd QWD "0000_0081"                                                                                                 
				Size			 : 257 Bytes                                                                                                                     
				                                                                                                                                       
	- Packet3 : Unicast		 	 : 1st QWD Destination MAC: "af4e_0032_1200"                                                                       
				VLAN Packet 	 : 2nd QWD "0000_0081"                                                                                                 
				Size			 : 493 Bytes                                                                                                                    
				                                                                                                                                       
	- Data Memory File			 : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/rx_pkt_gen_data.mem                   
                                                                                                  
	- Control Memory File		 : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/rx_pkt_gen_ctrl.mem                 
                                                                                                  
	- Simulation Script File 10G : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/Script_c06t02_10B_pkt_gap_10G.txt
							 5G  : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/Script_c06t02_10B_pkt_gap_5G.txt                 
						   2p5G  : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/Script_c06t02_10B_pkt_gap_2p5G.txt             						   
						     1G  : C:/LMAC2_INFO/TESTS/Rx_TESTS/CASE06_10B_PACKETGAP/TEST02_EOF05/VLAN_PKT/Script_c06t02_10B_pkt_gap_1G.txt             