
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)g++
OBJCOPY = $(CROSS_COMPILE)objcopy
CPUFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS) -DSTM32F1 -Ilibopencm3/include
CXXFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS) -DSTM32F1 -Ilibopencm3/include -fno-exceptions -fno-rtti -fno-common -ffunction-sections -fdata-sections
LDFLAGS = $(CPUFLAGS) -nostartfiles -Llibopencm3/lib -Wl,-T,pill.ld -static
LDLIBS = -lstdc++_nano -lc_nano -lopencm3_stm32f1 -lnosys

OBJ = main.o program.o usart.o usb.o

test1.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)


.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.d

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

all: test1.bin
