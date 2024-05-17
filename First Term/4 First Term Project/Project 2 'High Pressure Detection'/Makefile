SHELL=C:/Windows/System32/cmd.exe


CC =arm-none-eabi-
CFLAGS = -mcpu=cortex-m3 -mthumb -gdwarf-2
INC = -I .
SRC =$(wildcard *.c)
OBJ =$(SRC:.c=.o)
AS=$(wildcard *.s)	
AsOBJ =$(AS:.s=.o)
Project_name=High_Pressure_Detection


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
	rm *.o *.bin *.elf

clean:
	rm *.bin *.elf