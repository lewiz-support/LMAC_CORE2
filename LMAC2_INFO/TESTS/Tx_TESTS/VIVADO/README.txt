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

The Tx test is consist of the functional test cases and the performance test cases.

Functional test cases: to test if the numbers of packets that is being transmitted will carry the correct information.

Performance test cases: to push the maximum speed of the transmitting to test if the functionality is still under control and perform correctly. 

Simulation Tools:
1.	ModelSim
2.	Xilinx Vivado
*Note: Script used in the simulation may be different due to the diversity of the simulation tools. 

Testing procedures:

For ModelSim: Just run the script that provided in each test case.

For Vivado: 
1.	Open README.txt in a desired test case you want to run
2.	In your C:/LMAC_INFO directory, navigate to the AXIS_MASTER directory and open “memory_wr_module.v” file and target the “initial statement” at the bottom
3.	In the case test directory, 
Copy the data file path. Ex. $readmemh(C:/LMAC_INFO/… , memory_wr_data)
Copy the ctrl file path. Ex. $readmemh(C:/LMAC_INFO/… , memory_wr_ctrl)
4.	Paste both lines to the body of the initial statement
Note: Only one case can be run at each time. You can replace the existing test case or comment it out by using ‘//’ (double slash)

Example:

initial
begin
	$readmemh("C:/LMAC_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/10M_TEST_CASES/10M_PERFORMANCE_TEST_5/10M_performance_test5_ctrl.txt",memory_wr_ctrl);
	$readmemh("C:/LMAC_INFO/TESTS/Tx_TESTS/PERFORMANCE_TEST_CASES/10M_TEST_CASES/10M_PERFORMANCE_TEST_5/10M_performance_test5_data.txt",memory_wr_data); 
end

5.	Save this file.
6.	Use the provided script to run the test
