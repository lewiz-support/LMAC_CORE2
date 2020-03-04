onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L secureip -L fifo_generator_v13_0_1 -L xil_defaultlib -lib xil_defaultlib xil_defaultlib.ipcs_fifo_ip

do {wave.do}

view wave
view structure
view signals

do {ipcs_fifo_ip.udo}

run -all

quit -force
