AVRDUDE = /usr/share/arduino/hardware/tools/avrdude

CFLAGS = -Wall
LIBS = -lm -lcore

INC_DIRS = ""
INC_DIRS += 

SRC=$(wildcard *.c)

all: $(SRC)
	avr-g++ -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -funsigned-char -funsigned-bitfields -fno-exceptions -mmcu=atmega16 -DF_CPU=1000000UL -MMD -MP -MF"effects/breathe.d" -MT"effects/breathe.o" -c -o "effects/breathe.o" "../effects/breathe.cpp"

flash:
	./ard-reset-arduino.py /dev/ttyACM0 --verbose --caterina
	/usr/share/arduino/hardware/tools/avrdude -pm32u4 -cavr109 -P/dev/ttyACM0  -Uflash:w:Debug/bike-lights.hex:a
