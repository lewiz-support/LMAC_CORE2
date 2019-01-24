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
$readmemh("C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/memory_wr_ctrl_162_163_165B.txt",memory_wr_ctrl);
$readmemh("C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/memory_wr_data_162_163_165B.txt",memory_wr_data);

2.Run the following script for speed mode 1G, 10G, 5G, and 2.5G
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/Script_1G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/Script_10G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/Script_5G.txt
source C:/LMAC2_INFO/TESTS/Tx_TESTS/FUNCTIONAL_TEST_CASES/TEST_128_256B/TEST_162_163_165B/Script_2p5G.txt


Expected results:
---------------------------------------------------------------
The length of pkt_1 = 162 bytes 

The number of valid bytes in the last quardword = 2 

---------------------------------------------------------------
The length of pkt_2 = 163 bytes 

The number of valid bytes in the last quardword = 3 

---------------------------------------------------------------
The length of pkt_3 = 165 bytes 

The number of valid bytes in the last quardword = 5 