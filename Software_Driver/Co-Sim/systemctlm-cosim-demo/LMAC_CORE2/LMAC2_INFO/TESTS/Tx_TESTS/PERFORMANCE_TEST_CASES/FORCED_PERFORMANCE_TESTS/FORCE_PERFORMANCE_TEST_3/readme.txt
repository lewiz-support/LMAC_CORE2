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

***This test case tested the transmsion of 8 packet*** 

To run this test:

***For 1G transmission mode:
  Run the following script
  source C:/LMAC2_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/FORCED_PERFORMANCE_TESTS/FORCE_PERFORMANCE_TEST_3/script_1G.txt

***For 2.5G transmission mode:
   Run the following script
   source C:/LMAC2_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/FORCED_PERFORMANCE_TESTS/FORCE_PERFORMANCE_TEST_3/script_2p5G.txt

***For 5G transmission mode:
   Run the following script
   source C:/LMAC2_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/FORCED_PERFORMANCE_TESTS/FORCE_PERFORMANCE_TEST_3/script_5G.txt

***For 10G transmission mode:
   Run the following script
   source C:/LMAC2_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/FORCED_PERFORMANCE_TESTS/FORCE_PERFORMANCE_TEST_3/script_10G.txt
   
***Packets are pushed back to back with a gap of 2 clock cycles:

  
Expected results:
------------------------------------------------------------
The length of pkt_1 = 51 bytes 
The number of valid bytes in the last quardword = 3  
---------------------------------------------------------------
The length of pkt_2 = 77 bytes 
The number of valid bytes in the last quardword = 5 
---------------------------------------------------------------
The length of pkt_3 = 152 bytes 
The number of valid bytes in the last quardword = 8 
---------------------------------------------------------------
The length of pkt_4 = 206 bytes 
The number of valid bytes in the last quardword = 6 
---------------------------------------------------------------
The length of pkt_5 = 895 bytes 
The number of valid bytes in the last quardword = 7 
---------------------------------------------------------------
The length of pkt_6 = 1480 bytes 
The number of valid bytes in the last quardword = 8 
---------------------------------------------------------------
The length of pkt_7 = 40 bytes 
The number of valid bytes in the last quardword = 8 
---------------------------------------------------------------
The length of pkt_8 = 58 bytes 
The number of valid bytes in the last quardword = 2 