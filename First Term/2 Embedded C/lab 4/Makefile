SHELL=C:/Windows/System32/cmd.exe


CC =arm-none-eabi-
CFLAGS = -mcpu=cortex-m4 -gdwarf-2 -g
INC = -I .
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
AS=$(wildcard *.s)	
AsOBJ =$(AS:.s=.o)
Project_name=Toggle_Led_Tiva


all: $(Project_name).bin
	@echo "============Build is done============"

# startup.o: startup.c
# 	$(CC)as.exe $(CFLAGS) $< -o $@

%.o: %.c
	$(CC)gcc.exe -c $(INCS) $(CFLAGS)  $< -o $@

$(Project_name).elf: $(OBJ) $(AsOBJ)
	$(CC)ld.exe -T linker_script.ld $(OBJ) $(AsOBJ) -o $@ -Map=Map_file.map
	cp $(Project_name).elf $(Project_name).axf

$(Project_name).bin: $(Project_name).elf
	$(CC)objcopy -O binary $< $@

clean_all:
	rm *.o *.bin *.elf *.axf

clean:
	rm *.bin *.elf