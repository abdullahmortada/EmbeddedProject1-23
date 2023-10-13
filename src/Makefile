default:
	avr-gcc -Os -DF_CPU=16000000UL -mmcu=atmega328p main.c uart.c dio.c -o main.o
	avr-gcc -o main.bin main.o 
	avr-objcopy -O ihex -R .eeprom main.bin main.hex 
	sudo avrdude -F -V -c arduino -p ATMEGA328P -P /dev/ttyUSB0 -b 115200 -U flash:w:main.hex
	rm main.bin main.o 
