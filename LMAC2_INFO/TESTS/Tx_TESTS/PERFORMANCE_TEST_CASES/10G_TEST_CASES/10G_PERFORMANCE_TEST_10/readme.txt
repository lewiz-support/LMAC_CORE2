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
For the maximum performance,the minimum activited time of wrempty  singal should be push to 12ns (not including the first pkt)

To run this test:

1.Run the following script
source C:/LMAC2_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/10G_TEST_CASES/10G_PERFORMANCE_TEST_10/script_10G.txt


Expected results:
---------------------------------------------------------------
The length of pkt_1 = 203 bytes 
The number of valid bytes in the last quardword = 3 
The number of bytes in gap = 16 
---------------------------------------------------------------
The length of pkt_2 = 40 bytes 
The number of valid bytes in the last quardword = 8 
The number of bytes in gap = 11
---------------------------------------------------------------
The length of pkt_3 = 68 bytes 
The number of valid bytes in the last quardword = 4 
The number of bytes in gap = 15
---------------------------------------------------------------
The length of pkt_4 = 77 bytes 
The number of valid bytes in the last quardword = 5 
The number of bytes in gap = 14
---------------------------------------------------------------
The length of pkt_5 = 1375 bytes 
The number of valid bytes in the last quardword = 7 
The number of bytes in gap = 12
---------------------------------------------------------------
The length of pkt_6 = 58 bytes 
The number of valid bytes in the last quardword = 2 
The number of bytes in gap = 17
---------------------------------------------------------------
The length of pkt_7 = 46 bytes 
The number of valid bytes in the last quardword = 6 
The number of bytes in gap = 13
---------------------------------------------------------------
The length of pkt_8 = 73 bytes 
The number of valid bytes in the last quardword = 1 
The number of bytes in gap = 18