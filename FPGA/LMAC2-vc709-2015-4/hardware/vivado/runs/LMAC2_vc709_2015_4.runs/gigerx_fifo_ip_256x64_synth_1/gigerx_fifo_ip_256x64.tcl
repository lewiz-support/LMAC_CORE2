# 
# Synthesis run script generated by Vivado
# 

set_msg_config -id {Common 17-41} -limit 10000000
set_msg_config -id {HDL 9-1061} -limit 100000
set_msg_config -id {HDL 9-1654} -limit 100000
create_project -in_memory -part xc7vx690tffg1761-2

set_param project.compositeFile.enableAutoGeneration 0
set_param synth.vivado.isSynthRun true
set_msg_config -source 4 -id {IP_Flow 19-2162} -severity warning -new_severity info
set_property webtalk.parent_dir C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.cache/wt [current_project]
set_property parent.project_path C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.xpr [current_project]
set_property default_lib xil_defaultlib [current_project]
set_property target_language Verilog [current_project]
set_property vhdl_version vhdl_2k [current_fileset]
set_property verilog_define {USE_DDR3_FIFO=1 USE_XPHY=1 USE_PVTMON=1} [current_fileset]
read_ip c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64.xci
set_property is_locked true [get_files c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64.xci]

read_xdc dont_touch.xdc
set_property used_in_implementation false [get_files dont_touch.xdc]
synth_design -top gigerx_fifo_ip_256x64 -part xc7vx690tffg1761-2 -mode out_of_context
rename_ref -prefix_all gigerx_fifo_ip_256x64_
write_checkpoint -noxdef gigerx_fifo_ip_256x64.dcp
catch { report_utilization -file gigerx_fifo_ip_256x64_utilization_synth.rpt -pb gigerx_fifo_ip_256x64_utilization_synth.pb }
if { [catch {
  file copy -force C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.runs/gigerx_fifo_ip_256x64_synth_1/gigerx_fifo_ip_256x64.dcp c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64.dcp
} _RESULT ] } { 
  send_msg_id runtcl-3 error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
  error "ERROR: Unable to successfully create or copy the sub-design checkpoint file."
}
if { [catch {
  write_verilog -force -mode synth_stub c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_stub.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a Verilog synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}
if { [catch {
  write_vhdl -force -mode synth_stub c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_stub.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create a VHDL synthesis stub for the sub-design. This may lead to errors in top level synthesis of the design. Error reported: $_RESULT"
}
if { [catch {
  write_verilog -force -mode funcsim c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_sim_netlist.v
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the Verilog functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}
if { [catch {
  write_vhdl -force -mode funcsim c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_sim_netlist.vhdl
} _RESULT ] } { 
  puts "CRITICAL WARNING: Unable to successfully create the VHDL functional simulation sub-design file. Post-Synthesis Functional Simulation with this file may not be possible or may give incorrect results. Error reported: $_RESULT"
}

if {[file isdir C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.ip_user_files/ip/gigerx_fifo_ip_256x64]} {
  catch { 
    file copy -force c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_stub.v C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.ip_user_files/ip/gigerx_fifo_ip_256x64
  }
}

if {[file isdir C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.ip_user_files/ip/gigerx_fifo_ip_256x64]} {
  catch { 
    file copy -force c:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.srcs/sources_1/ip/gigerx_fifo_ip_256x64/gigerx_fifo_ip_256x64_stub.vhdl C:/SUNNY2/LMAC2-vc709-2015-4/hardware/vivado/runs/LMAC2_vc709_2015_4.ip_user_files/ip/gigerx_fifo_ip_256x64
  }
}
