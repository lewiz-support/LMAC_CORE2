onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib gigerx_fifo_ip_256x64_opt

do {wave.do}

view wave
view structure
view signals

do {gigerx_fifo_ip_256x64.udo}

run -all

quit -force
