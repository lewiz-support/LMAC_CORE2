//
//
// Copyright (C) 2019 LeWiz Communications, Inc. 
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

The following describes the software folders released.
The following apply to both LeWiz's LMAC CORE2 and LMAC CORE1 Ethernet controllers
This code is released to illustrate how to code driver for LMAC CORE2 and 1.
It works with the co-simulator from Xilinx.
For code in the CO-SIM folder, these can be used as reference. To actually install the co-simulation
environment, you need to follow Xilinx's instructions.  See also:
https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842060/QEMU

Where the info refered to a demo,
** To watch the DEMO VIDEO, please visit the link below **

	https://www.youtube.com/watch?v=PMsvJDp8lCQ


--------------------------------

------ Source folder:

The source folder contains the source code of the Ethernet MAC driver file (lmac2.c) for LeWiz's LMAC CORE2.

This driver file can also be found under Co-Sim\linux\linux\drivers\net\ethernet\lewiz


-------- Co-Sim Folder:

-Linux: This folder contains the Linux kernel along with the driver code for Lewiz Ethernet MAC and others.

-systemctlm-cosim-demo: This folder contains the systemC code for lewiz LMAC CORE2. All systemC programmable logic code and Verilog files are contained in this folder. 
The programmable logic code needs to be compiled before using.

-posh-qemu: This folder contains the scripts for running programmable logic code (PL) and qemu code (PS) in the demo. 
It also contains the pcap file captured during a co-sim run. 

-qemu: The qemu hardware and device tree codes are contained in this folder. This code is only for reference that you can compare to your installed version. This code cannot be run as is without installing as instructed by Xilinx.
       For installing the qemu, please follow the steps "Building device tree" on the following website.

       https://xilinx-wiki.atlassian.net/wiki/spaces/A/pages/18842060/QEMU 


Once you've built QEMU and device-tree's, jump to this project:

-->	clone systemctlm-cosim-demo repository from github (Software_Driver/Co-Sim/).

	You'll need to build the SystemC libraries from Accellera and install them on your Linux system. 

-->	You'll need to create a .config.mk in the systemctlm-cosim-demo directory to point where 
	your SystemC libraries are located and to enable Verilog and Verilator.

-->	If you go to Accelleras download page (Google for it) you'll find the systemC libraries with TLM included. 
	Download 2.3.3 and untar the tarball and you'll find a file called INSTALL.

-->	The install file has examples.
	We used:    ../configure --prefix=/opt/systemc-2.3.3/
	Then: make install


-->	The following is what my .config.mk file looks like.
	$ cat .config.mk
	SYSTEMC = /opt/systemc-2.3.2
	HAVE_VERILOG=y
	HAVE_VERILOG_VERILATOR=y

After that, you should follow the BUILD steps in the README on the github repository.

After building you should have a systemctlm-cosim-demo/zynqmp_lmac2_demo file.


Before you run, you need some directories to store the results of the run.
The following are the directories we used:
"somedir" and "machine-zynqmp"

To run the demo, you'll need two Linux shell terminals.

run shell scripts fom posh-qemu directory on two different terminal
one shell: ./qemu-run.sh
second shell: ./pl-run.sh


	






 