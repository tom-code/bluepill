
CROSS_COMPILE = arm-none-eabi-
CC = $(CROSS_COMPILE)gcc
CXX = $(CROSS_COMPILE)gcc
OBJCOPY = $(CROSS_COMPILE)objcopy
CPUFLAGS = -mcpu=cortex-m3 -mthumb
CFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS) -DSTM32F1 -Ilibopencm3/include
CXXFLAGS = -Wall -Wextra -g3 -O0 -MD $(CPUFLAGS) -DSTM32F1 -Ilibopencm3/include -fno-exceptions -fno-rtti
LDFLAGS = $(CPUFLAGS) -nostartfiles -Llibopencm3/lib -Wl,-T,pill.ld
LDLIBS = -lopencm3_stm32f1 -lc -lnosys

OBJ = main.o test.o usart.o

test1.elf: $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)


.PHONY: clean
clean:
	rm -f *.o *.bin *.elf *.d

%.bin: %.elf
	$(OBJCOPY) -O binary $< $@

all: test1.bin
