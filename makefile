.DEFAULT_GOAL :=all

TOOLCHAIN=avr
CC=avr
# the include files are stored at "/usr/lib/avr/include" under linux

OUT_FOLDER = out
FILE_NAME = network_exmaple

ELF_FILE = $(FILE_NAME).elf
HEX_FILE = $(FILE_NAME).hex
LST_FILE = $(FILE_NAME).lst
MAP_FILE = $(FILE_NAME).map

#CPU=atmega328p
CPU=atmega32

CFLAGS = -Wall -Wextra -Wpedantic -O0 -mmcu=$(CPU) -I. -I./interfaces -I./hardware_abstraction_layer/$(CPU) -DWHO_AM_I=\"$(FILE_NAME)\" -std=c11

SRC_FILES_C = $(wildcard *.c)
SRC_FILES_ASM += $(wildcard *.asm)
SRC_FILES_CPP += $(wildcard *.cpp)

SRC_FILES_C += $(wildcard hardware_abstraction_layer/$(CPU)/*.c)
SRC_FILES_C += $(wildcard library/*.c)

INC_FILES = $(wildcard *.h)
INC_FILES += $(wildcard *.hpp)
INC_FILES += $(wildcard interfaces/*.h)
INC_FILES += $(wildcard hardware_abstraction_layer/$(CPU)/*.h)
INC_FILES += $(wildcard interfaces/*.hpp)

OBJ = $(patsubst %.c, $(OUT_FOLDER)/%.o, $(SRC_FILES_C))
OBJ += $(patsubst %.asm, $(OUT_FOLDER)/%.o, $(SRC_FILES_ASM))
OBJ += $(patsubst %.cpp, $(OUT_FOLDER)/%.o, $(SRC_FILES_CPP))

DEBS= $(INC_FILES) makefile

#PORT=/dev/ttyUSB0
PORT=/dev/serial/by-id/usb-Silicon_Labs_myAVR_-_mySmartUSB_light_mySmartUSBlight-0001-if00-port0

all: setup $(ELF_FILE) $(LST_FILE) $(HEX_FILE)
	@echo 
	$(CC)-size $(ELF_FILE)
	@echo

$(ELF_FILE): $(OBJ)
	$(CC)-gcc  $(OBJ) $(CFLAGS) -Wl,-Map=$(MAP_FILE) -o $(ELF_FILE)

./$(OUT_FOLDER)/%.o: %.asm $(DEBS)
	$(CC)-as -g -c $< -o $@	

./$(OUT_FOLDER)/%.o: %.c $(DEBS)
	$(CC)-gcc $(CFLAGS) -c $< -o $@
	
./$(OUT_FOLDER)/%.o: %.cpp $(DEBS)
	$(CC)-g++ $(CFLAGS) -c $< -o $@

$(LST_FILE): $(ELF_FILE)
	$(CC)-objdump -d $(ELF_FILE) > $(LST_FILE)

$(HEX_FILE): $(ELF_FILE)
	$(CC)-objcopy -O ihex -R .eeprom $(ELF_FILE) $(HEX_FILE)

download: download_$(CPU)

download_atmega328p: all
	avrdude -v -patmega328p -carduino -P$(PORT) -b57600 -D -Uflash:w:$(HEX_FILE):i 

download_atmega32: all
	avrdude -v -patmega32 -cstk500v2 -P$(PORT) -Uflash:w:$(HEX_FILE):i 

rebuild: clean all

clean:
	rm -rf $(OUT_FOLDER) *.elf *.lst *.img *.map *.hex

install_dep:
	sudo apt install avr-libc avrdude build-essential 

setup: $(OUT_FOLDER)/library $(OUT_FOLDER)/hardware_abstraction_layer/$(CPU)

$(OUT_FOLDER)/library:
	mkdir -p $(OUT_FOLDER)
	mkdir -p $(OUT_FOLDER)/library

$(OUT_FOLDER)/hardware_abstraction_layer/$(CPU):
	mkdir -p $(OUT_FOLDER)	
	mkdir -p $(OUT_FOLDER)/hardware_abstraction_layer/$(CPU)
