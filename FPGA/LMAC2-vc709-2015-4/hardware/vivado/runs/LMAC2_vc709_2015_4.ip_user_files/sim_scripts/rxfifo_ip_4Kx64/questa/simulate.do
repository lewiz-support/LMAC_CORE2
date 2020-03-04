onbreak {quit -f}
onerror {quit -f}

vsim -t 1ps -lib xil_defaultlib rxfifo_ip_4Kx64_opt

do {wave.do}

view wave
view structure
view signals

do {rxfifo_ip_4Kx64.udo}

run -all

quit -force
