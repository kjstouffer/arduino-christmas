#!/usr/bin/env bash
source ./env_vars.sh
$ARDUINO_DIR/arduino-builder \
	-logger=machine \
	-hardware $ARDUINO_DIR/hardware \
	-tools $ARDUINO_DIR/tools-builder \
	-tools $ARDUINO_DIR/hardware/tools/avr \
	-built-in-libraries $ARDUINO_DIR/libraries \
	-fqbn=arduino:avr:uno \
	-ide-version=10805 \
	-build-path $PROJECT_DIR/build \
	-warnings=none \
	-build-cache $PROJECT_DIR/build \
	-prefs=build.warn_data_percentage=75 \
	-prefs=runtime.tools.avrdude.path=$ARDUINO_DIR/hardware/tools/avr \
	-prefs=runtime.tools.avr-gcc.path=$ARDUINO_DIR/hardware/tools/avr \
	$PROJECT_DIR/ledtree.ino
