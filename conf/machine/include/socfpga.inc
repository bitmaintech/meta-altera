SOC_FAMILY = "socfpga"
#require conf/machine/include/soc-family.inc

require conf/machine/include/tune-cortexa9.inc

PROVIDES+="virtual/kernel"
PREFERRED_PROVIDER_virtual/kernel = "linux-socfpga"
# update for socfpga -> change the recipe names"
PREFERRED_PROVIDER_virtual/bootloader = "u-boot-socfpga"

# Increase this everytime you change something in the kernel
MACHINE_KERNEL_PR = "r1"

KERNEL_IMAGETYPE = "zImage"

UBOOT_ENTRYPOINT = "0x80008000"
UBOOT_LOADADDRESS = "0x80008000"

SERIAL_CONSOLE = "115200 ttyS0"
