SHELL=C:/Windows/System32/cmd.exe

CC = arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -gdwarf-2 -g
INCS = -I .
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
AS = $(wildcard *.s)
ASOBJ = $(AS:.s=.o)
Project_name = Toggle_Led

all: $(Project_name).bin
	@echo "============ Build is done ============"

%.o: %.s
	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS) $< -o $@

$(Project_name).elf: $(OBJ) $(ASOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(ASOBJ) -o $@ -Map=Map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy -O binary $< $@

clean_all:
	rm -f *.o *.bin *.elf

clean:
	rm -f *.bin *.elf
