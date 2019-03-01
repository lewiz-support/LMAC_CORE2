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

This test consists of 3 packets with variable lengths. 

The first number on the .png file represent the speed mode.
1G,
100M,
10M


 3 Frames Transmitted:

 1)  MAC address: Unicast, Packet Type: Normal IP.
     Packet length = 48Bytes
     No. of valid Bytes in last Quadword = 8
     
 2)  MAC address: Unicast, Packet Type: Normal IP.
     Packet Length = 47 Bytes.
     No. of valid Bytes in last Quadword = 7

 3)  MAC address: Unicast, Packet Type: Normal IP.
     Packet Length = 49 Bytes
     No. of valid Bytes in last quadword = 1.


 The Rbytes register indicates the Packet Length and FMAC_TX_PKT_CNT indicate the number of Frames Transmitted. 

 The gmii_tx_en = 1 signal indicate the beginning of frame transmission and gmii_tx_en = 0 indicate the end of frame transmission.
 
 Number of bytes between packet 1 and 2 = 11B


 Number of Bytes between packet 2 and 3  = 12B 