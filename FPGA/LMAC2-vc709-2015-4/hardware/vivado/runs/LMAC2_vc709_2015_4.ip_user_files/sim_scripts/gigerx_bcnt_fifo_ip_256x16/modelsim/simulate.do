onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L secureip -L fifo_generator_v13_0_1 -L xil_defaultlib -lib xil_defaultlib xil_defaultlib.gigerx_bcnt_fifo_ip_256x16

do {wave.do}

view wave
view structure
view signals

do {gigerx_bcnt_fifo_ip_256x16.udo}

run -all

quit -force
