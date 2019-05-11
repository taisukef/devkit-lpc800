NAME = obj

# make        # build & write == write
# make clean  # clean files
# make write  # write to computer

.PHONY: all build write clean

# settings
LPC21WRITER = /Users/fukuno/data/c/lpc21isp_197k/lpc21isp
USB_SERIAL_PORT = /dev/tty.SLAB_USBtoUART

# commands
GCC         = arm-none-eabi-gcc
OBJCOPY     = arm-none-eabi-objcopy
OBJDUMP     = arm-none-eabi-objdump
SIZE        = arm-none-eabi-size
RM          = rm -rf


EXECUTABLES = $(NAME).hex

all:
	$(MAKE) write

write: $(NAME).hex
	$(LPC21WRITER) -control $(NAME).hex $(USB_SERIAL_PORT) 115200 1200
