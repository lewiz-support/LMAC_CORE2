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


FMAC_RX_PKT_CNT1518_LO register is forced to the maximum 32 bit value -> ffffffff and then remove the force
8 packets are received with below mentioned number of bytes in each packet
pkt1 - 51
pkt2 - 64
pkt3 - 83
pkt4 - 234
pkt5 - 318
pkt6 - 512
pkt7 - 1041
pkt8 - 2041

We have 1 packet with number of bytes in range 1024 to 1518, so, the FMAC_RX_PKT_CNT1518_LO register gets updated with the value 0 and the FMAC_RX_PKT_CNT1518_HI gets updated with the value 1
Clear signal is provided from the axi_master by asserting the 7th bit of the fmac_ctrl signal from the axi_master
Once the clear signal is provided, the FMAC_RX_PKT_CNT1518_LO and FMAC_RX_PKT_CNT1518_HI changes its value to 0 and accordingly the mac_regdout signal in the axi_master
The value of the register FMAC_RX_PKT_CNT1518_HI is read and displayed in mac_regdout signal in axi_master for the host address 182C