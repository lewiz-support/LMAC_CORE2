#!/bin/sh

set -x
set -e

PL=/home/lewiz/sambashare/Software_Driver/Co-Sim/systemctlm-cosim-demo/zynqmp_lmac2_demo

LD_LIBRARY_PATH=/opt/systemc-2.3.3/lib-linux64/ ${PL} \
	unix:./machine-zynqmp/qemu-rport-_amba@0_cosim@0 \
	100000
