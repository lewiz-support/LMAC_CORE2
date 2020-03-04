vlib work
vlib msim

vlib msim/fifo_generator_v13_0_1
vlib msim/xil_defaultlib

vmap fifo_generator_v13_0_1 msim/fifo_generator_v13_0_1
vmap xil_defaultlib msim/xil_defaultlib

vcom -work fifo_generator_v13_0_1 -64 -93 \
"../../../ipstatic/fifo_generator_v13_0_1/simulation/fifo_generator_vhdl_beh.vhd" \
"../../../ipstatic/fifo_generator_v13_0_1/hdl/fifo_generator_v13_0_rfs.vhd" \

vcom -work xil_defaultlib -64 -93 \
"../../../../LMAC2_vc709_2015_4.srcs/sources_1/ip/txfifo_ip_1024x64/sim/txfifo_ip_1024x64.vhd" \

