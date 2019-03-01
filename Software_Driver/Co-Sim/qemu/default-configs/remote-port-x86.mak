# Instead of cluttering the source-code with #ifdefs, we enable
# all the necessary features in the x86 models.
# x86_64 configs can include this file for convinience.
CONFIG_PCI_GENERIC=y
CONFIG_PLATFORM_BUS=y
CONFIG_XILINX=y
CONFIG_ZYNQ=y
CONFIG_XLNX_ZYNQMP=y
CONFIG_XILINX_AXI=y
CONFIG_SSI=y
CONFIG_XILINX_SPI=y
CONFIG_XILINX_SPIPS=y
CONFIG_STREAM=y
CONFIG_PTIMER=y
CONFIG_CADENCE=y
CONFIG_SI57X=y
CONFIG_REMOTE_PORT=y
CONFIG_REMOTE_PORT_PCI=y
