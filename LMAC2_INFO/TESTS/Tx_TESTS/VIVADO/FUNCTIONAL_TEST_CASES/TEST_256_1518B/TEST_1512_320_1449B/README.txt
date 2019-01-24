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


***This test case tested the transmsion of 3 packets*** 

To run this test:

1.Copy the path for memory data and ctrl
$readmemh("C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/memory_wr_ctrl_1512_320_1449B.txt",memory_wr_ctrl);
$readmemh("C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/memory_wr_data_1512_320_1449B.txt",memory_wr_data);

2.Run the following script for speed mode 1G, 10G, 5G, and 2.5G
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/Script_1G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/Script_10G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/Script_5G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_256_1518B/TEST_1512_320_1449B/Script_2p5G.txt


Expected results:
---------------------------------------------------------------
The length of pkt_1 = 1512 bytes 

The number of valid bytes in the last quardword = 8 

---------------------------------------------------------------
The length of pkt_2 = 320 bytes 

The number of valid bytes in the last quardword = 8 

---------------------------------------------------------------
The length of pkt_3 = 1449 bytes 

The number of valid bytes in the last quardword = 1 