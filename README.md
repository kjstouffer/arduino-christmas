# Building
## Prerequisites
Raspberry Pi:
- arduino-ide 1.8.5+, available from arduino here:
  - https://downloads.arduino.cc/arduino-1.8.5-linuxarm.tar.xz
- project defaults have arduino-1.8.5-linuxarm.tar.xz extracted at `$HOME/arduino-ide`
- to get and extract arduino-1.8.5-linuxarm.tar.xz:
```bash
cd ~
wget https://downloads.arduino.cc/arduino-1.8.5-linuxarm.tar.xz
tar xf arduino-1.8.5-linuxarm.tar.xz
mv arduino-1.8.5 arduino-ide
```
- Additionally, `Adafruit_NeoPixel` must be installed in arduino's library folder:
```bash
git clone https://github.com/adafruit/Adafruit_NeoPixel ~/arduino-ide/Adafruit_NeoPixel
```

## compile
run `./compile.sh` to compile the arduino sketch. the build output will be in the `./build` folder

## upload
run `./upload.sh` to upload the compiled sketch to the arduino-uno connected via the raspberry pi usb port (should be `/dev/ttyACM0`)
