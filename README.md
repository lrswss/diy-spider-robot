# Yet another DIY Quadruped Spider Robot

## Description

Arduino sketch for a crawling quadruped (4 legs with 3 servos each)
spider robot with IR remote control, ultrasonic distance sensor,
neopixel headlights, a beeper and HC-05 based bluetooth uplink.

## Required Arduino Libraries

Before compiling the code for an Arduino Nana (328p) target make sure
that the following libraries are installed:

- Servo by Michael Margolis
- [FlexiTimer2 by Wim Leers](https://github.com/wimleers/flexitimer2)
- NewPing by Tim Eckel (for optional Ultrasonic Sensor HC-SR04)
- EasyNeoPixels by Evelyn Masso (for optional Neopixel Headlights)
- NeoSWSerial by SlashDevin (for optional attiny85 IR decoder board)

All libraries but FlexiTimer2 can be downloaded using the [Arduino IDE 
library manager](https://www.arduino.cc/en/Guide/Libraries).

## Codebase

For a brief but probably incomplete history of the quadruped spider robot
codebase originally published by SunFounder in 2015 please refer to this
[summary](https://github.com/lrswss/diy-spider-robot/blob/master/software/codebase/README.md).

## Contributing

Pull requests are welcome! For major changes, please open an issue first to
discuss what you would like to change.

## License

Some parts of the software were published under the MIT license others under the GPLv3.  
Please check the source files for details.
