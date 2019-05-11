NAME = obj

# make        # build & write == write
# make build  # just make axf
# make clean  # clean files
# make write  # write to stm32

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

# src
C_SRCS = src/main.c

C_HEADERS = src/stddef.h src/lpc810.h src/vectors.h src/uart.h

LD = lpc810.ld

# build
OBJS = main.o

EXECUTABLES = $(NAME).axf $(NAME).bin $(NAME).hex

all: $(NAME).bin $(NAME).axf
	$(MAKE) write

build: $(NAME).axf

$(OBJS): $(C_SRCS) $(C_HEADERS)
	$(GCC) -std=gnu99 -Os -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0plus -mthumb -o "$@" "$<"

$(NAME).axf: $(OBJS)
	$(GCC) -nostartfiles -Wl,-Map="$(NAME).map" -Xlinker --gc-sections -mthumb -mcpu=cortex-m0plus -mthumb-interwork -T "$(LD)" -o $@ $(OBJS)
	$(SIZE) "$@"

%.hex: %.axf
	$(OBJCOPY) -O ihex "$<" "$@"

%.bin: %.axf
	$(OBJCOPY) -O binary "$<" "$@"

clean:
	$(RM) $(OBJS) $(NAME).map $(EXECUTABLES) 

write: $(NAME).hex
	$(LPC21WRITER) -control $(NAME).hex $(USB_SERIAL_PORT) 115200 1200

.PRECIOUS: $(NAME).bin
