onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib gigerx_bcnt_fifo_ip_256x16_opt

do {wave.do}

view wave
view structure
view signals

do {gigerx_bcnt_fifo_ip_256x16.udo}

run -all

quit -force
