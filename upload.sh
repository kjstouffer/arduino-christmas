#!/usr/bin/env bash
source ./env_vars.sh
$ARDUINO_DIR/hardware/tools/avr/bin/avrdude \
	-C$ARDUINO_DIR/hardware/tools/avr/etc/avrdude.conf \
	-patmega328p \
	-carduino \
	-P/dev/ttyACM0 \
	-b115200 \
	-D \
	-Uflash:w:$PROJECT_DIR/build/ledtree.ino.hex:i 


