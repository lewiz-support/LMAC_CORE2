onbreak {quit -f}
onerror {quit -f}

vsim -voptargs="+acc" -t 1ps -L secureip -L fifo_generator_v13_0_1 -L xil_defaultlib -lib xil_defaultlib xil_defaultlib.rxfifo_ip_4Kx64

do {wave.do}

view wave
view structure
view signals

do {rxfifo_ip_4Kx64.udo}

run -all

quit -force
