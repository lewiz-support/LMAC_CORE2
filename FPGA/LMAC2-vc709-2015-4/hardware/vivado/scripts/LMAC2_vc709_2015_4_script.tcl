#
# Copyright (C) 2018 LeWiz Communications, Inc. 
# 
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
# 
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
# 
# You should have received a copy of the GNU Lesser General Public
# License along with this library release; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
# 
# LeWiz can be contacted at:  support@lewiz.com
# or address:  
# PO Box 9276
# San Jose, CA 95157-9276
# www.lewiz.com




# Vivado Launch Script

#### Change design settings here #######
set design LMAC2_vc709_2015_4 
set rtl_top LMAC2_vc709_2015_4
set sim_top board
set device xc7vx690t-2-ffg1761
set bit_settings v7_LMAC2_bit_rev1_0.xdc
# Valid choices for TRD_MODE are LOOPBACK, BASE, FULL, NODDR3
set TRD_MODE "FULL"
########################################
# Setting proper parameters for chosen TRD mode
if {$TRD_MODE == "LOOPBACK"} {
  set BASE_ONLY 0
  set LOOPBACK_ONLY 1
  set NO_DDR3 1
} elseif {$TRD_MODE == "BASE"} {
  set BASE_ONLY 1
  set LOOPBACK_ONLY 0
  set NO_DDR3 0
} elseif {$TRD_MODE == "NODDR3"} {
  set BASE_ONLY 0
  set LOOPBACK_ONLY 0
  set NO_DDR3 1
} else {
  set BASE_ONLY 0
  set LOOPBACK_ONLY 0
  set NO_DDR3 0
}
########################################

# Project Settings
create_project -name ${design} -force -dir "./runs" -part ${device}
set_property source_mgmt_mode DisplayOnly [current_project]

set_property top ${rtl_top} [current_fileset]


  if {$LOOPBACK_ONLY} {
    puts "Using DMA Loopback design with no DDR3 or Ethernet"
    set_property verilog_define { {DMA_LOOPBACK=1} {USE_PVTMON=1} } [current_fileset]
  } elseif {$BASE_ONLY} {
    puts "Using PCIe, DMA, DDR3, and Virtual FIFO, but no Ethernet"
    set_property verilog_define { {USE_DDR3_FIFO=1} {BASE_ONLY=1} {USE_PVTMON=1} } [current_fileset]
  } elseif {$NO_DDR3} {
    puts "Using PCIe, DMA, Ethernet, but no DDR3"
    set_property verilog_define { {USE_XPHY=1} {USE_PVTMON=1} } [current_fileset]
  } else {
    puts "Using full Targeted Reference Design, with DDR3 and Ethernet"
    set_property verilog_define { {USE_DDR3_FIFO=1} {USE_XPHY=1} {USE_PVTMON=1} } [current_fileset]
  }

# Project Constraints
  if {$LOOPBACK_ONLY} {
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_trd_loopback.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/${bit_settings}
  } elseif {$BASE_ONLY} {
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_trd_base.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/${bit_settings}
  } elseif {$NO_DDR3} {
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_xgemac_xphy.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_conn_trd_noddr3.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/${bit_settings}
  } else {
    # FULL case
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_xgemac_xphy.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/v7_LMAC2_base.xdc
    add_files -fileset constrs_1 -norecurse ../sources/constraints/${bit_settings}
  }

  
  if {!$LOOPBACK_ONLY && !$BASE_ONLY} {
    read_ip -files {../sources/ip_catalog/ten_gig_eth_pcs_pma_ip_shared_logic_in_core/ten_gig_eth_pcs_pma_ip_shared_logic_in_core.xci} 
  }
  
  
  # Other Custom logic source files
  read_verilog "../sources/hdl/common/synchronizer_simple.v"

  
  if {!$LOOPBACK_ONLY && !$BASE_ONLY} {
    read_verilog "../sources/hdl/network_path/network_path_shared.v"
  }
  
  
  read_vhdl "../sources/hdl/pvtmon/kcpsm6.vhd"
  read_vhdl "../sources/hdl/pvtmon/power_test_control.vhd"
  read_vhdl "../sources/hdl/pvtmon/vc709_power_test.vhd"
  read_vhdl "../sources/hdl/pvtmon/power_test_control_program.vhd"
  
  if {!$LOOPBACK_ONLY || !$BASE_ONLY} {
    read_vhdl "../sources/hdl/clock_control/clock_control.vhd"
    read_vhdl "../sources/hdl/clock_control/clock_control_program.vhd"
  }
  
#  read_verilog "../sources/hdl/pipe_clock.v"
  read_verilog "../sources/hdl/LMAC2_vc709_2015_4.v"
  read_verilog "../sources/hdl/LMAC_RTL/LMAC_SYNTH/LMAC_SYNTH.v"
  read_verilog "../sources/hdl/LMAC_RTL/LPBK_MODULE/LPBK_MODULE.v" 
    
  generate_target {synthesis simulation} [get_ips]


#Setting Synthesis options
set_property strategy Flow_PerfOptimized_High [get_runs synth_1]
#Setting Implementation options
set_property steps.phys_opt_design.is_enabled true [get_runs impl_1]

# Pick best strategy for different runs
  if {$TRD_MODE == "LOOPBACK"} {
	set_property strategy Performance_RefinePlacement [get_runs impl_1]
  } elseif {$TRD_MODE == "BASE"} {
	set_property strategy Performance_NetDelay_medium [get_runs impl_1]
  } elseif {$TRD_MODE == "NODDR3"} {
	set_property strategy Performance_ExplorePostRoutePhysOpt [get_runs impl_1]
  } else {
	set_property strategy Performance_Explore [get_runs impl_1]
  } 

# Set up Simulations
set_property top ${sim_top} [get_filesets sim_1]
set_property include_dirs { ../sources/testbench ../sources/testbench/dsport ../sources/testbench/include ../sources/hdl/gen_chk ./} [get_filesets sim_1]

  if {$LOOPBACK_ONLY} {
    set_property verilog_define { {USE_PIPE_SIM=1} {SIMULATION=1} {DMA_LOOPBACK=1} } [get_filesets sim_1]
  } elseif {$BASE_ONLY} {
    set_property verilog_define { {USE_PIPE_SIM=1} {SIMULATION=1} {USE_DDR3_FIFO=1} {BASE_ONLY=1} {x4Gb=1} {sg107E=1} {x8=1}} [get_filesets sim_1]
  } elseif {$NO_DDR3} {
    set_property verilog_define { {USE_PIPE_SIM=1} {SIMULATION=1} {USE_XPHY=1} {NW_PATH_ENABLE=1} } [get_filesets sim_1]
  } else {
    set_property verilog_define { {USE_PIPE_SIM=1} {SIMULATION=1} {USE_DDR3_FIFO=1} {USE_XPHY=1} {NW_PATH_ENABLE=1} {x4Gb=1} {sg107E=1} {x8=1}} [get_filesets sim_1]
  }

# Vivado Simulator settings
set_property -name xsim.simulate.xsim.more_options -value {-testplusarg TESTNAME=basic_test} -objects [get_filesets sim_1]
#set_property xsim.simulate.runtime {50us} [get_filesets sim_1]

# Default to MTI
set_property target_simulator ModelSim [current_project]

add_files -fileset sim_1 "../sources/testbench/board.v"




