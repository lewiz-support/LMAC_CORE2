#!/bin/sh

set -x
set -e

QEMU=/home/lewiz/sambashare/Software_Driver/Co-Sim/qemu/aarch64-softmmu/qemu-system-aarch64
MACHINE="-M arm-generic-fdt"
HW_DTB="-hw-dtb /tmp/dts/LATEST/SINGLE_ARCH/zcu102-arm.cosim.dtb"
DTB="-dtb ./zcu102.dtb"
SERIAL="-serial mon:stdio -display none"
NETDEV0="-netdev user,id=net0"
NETDEV1="-netdev user,id=net1"
NETDEV2="-netdev user,id=net2"
NETDEV3="-netdev user,id=net3"
NETDEV4="-netdev user,id=net4"
NET0="-net nic,model=cadence_gem,netdev=net0"
NET1="-net nic,model=cadence_gem,netdev=net1"
NET2="-net nic,model=cadence_gem,netdev=net2"
NET3="-net nic,model=cadence_gem,netdev=net3"
#NET4="-net nic,model=remote-port-net,netdev=net4"
NET4="-device remote-port-net,rp-adaptor0=/amba@0/cosim@0,rp-chan0=256,rp-chan1=266,netdev=net4"
NET_TRACE0="-object filter-dump,netdev=net0,id=dump0,file=trace0.pcap"
NET_TRACE1="-object filter-dump,netdev=net1,id=dump1,file=trace1.pcap"
NET_TRACE2="-object filter-dump,netdev=net2,id=dump2,file=trace2.pcap"
NET_TRACE3="-object filter-dump,netdev=net3,id=dump3,file=trace3.pcap"
NET_TRACE4="-object filter-dump,netdev=net4,id=dump4,file=trace4.pcap"
MACHINE_PATH="-machine-path machine-zynqmp"

#IMAGE=./Image
#  New built of ARM64
IMAGE=/home/lewiz/sambashare/Software_Driver/Co-Sim/linux/linux/arch/arm64/boot/Image

${QEMU} ${MACHINE} \
	${HW_DTB} \
	${MACHINE_PATH} \
	${SERIAL} \
	${NETDEV0} \
	${NETDEV1} \
	${NETDEV2} \
	${NETDEV3} \
	${NETDEV4} \
	${NET0} ${NET1} ${NET2} ${NET3} \
	${NET4} \
	${NET_TRACE0} \
	${NET_TRACE1} \
	${NET_TRACE2} \
	${NET_TRACE3} \
	${NET_TRACE4} \
	-m 2G -machine linux=yes -kernel ${IMAGE} \
	${DTB} \
	-append "rdinit=/sbin/init console=ttyPS0 earlycon=cdns,mmio,0xFF000000,115200n8" \
	$*
