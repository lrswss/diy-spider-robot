## A brief but probably incomplete history of the quadruped spider robot codebase
  
The original code for an Arduino Nano v3.0 including all (mathematical) base
functions for a crawling spider robot with a nRF24L01 based remote control
was published in early 2015 by SunFounder [1] under GPLv3.
 
Starting in fall 2015 RegisHsu published detailed instructions on how to build
a DIY 3D printed spider robot including schematics for an Arduino Pro Mini on
instructables.com [2], he seemingly had been working on since 2014 [3]. He
reused the SunFounder code adjusting parameters for his 3D design and removed
the code for the nRF24L01 wireless remote control and the adjust/verify
functions for initial leg positioning. For the later he supplied a sketch
(init_legs.ino) used once during initial setup of the spider robot. He also
added three new moves: hand_shake(), hand_wave() and dance(). In part II of 
his project on instructables.com [4] RegisHsu added some code basic for a
bluetooth remote control using a Android App.

Based on RegisHsu's code including the hooks for a command based remote control
using serial communication (SerialCommand.h) Anuchit Chalothorn contributed
some code to support an ultrasonic sensor (HC-SR04) adding obstacle avoidance
and an autonomous walking mode ("free walk"). He also added support to control
the robot with his Android Bluetooth Joypad App [6].

In March 2018 John Crombie posted a short video on YouTube [7] presenting
his attributions to the spider robot codebase [8] and also his STL remixes of
the spider's body [9] to accommodate the Arduino Nano with an standard Nano
expansion board and a DC-DC voltage converter. In his version of the sketch
he added new 11 moves (sprawl, bow, twist,...) and some code for a 2-3 cell
LiPo battery monitor with its balance connector connected to the Nanos ADC 
pins A0 to A2. He also reintroduced some code to fine tune the initial 90
degree positioning of all 12 servos.

In 2018 Mohamed Belkhir (Mega DAS) published detailed instructions on YouTube [10]
and hackster.io [11] for a bluetooth controlled quadruped spider robot with an
OLED display to mimic a face on the spider's head. He also contributed an Android
App and another custom PCB, seemingly to advertise the services of a well known
chinese PCB manufacturer. His attributions to the original code base boil down to
some functions for drawing a few facial expressions onto a small I2C driven OLED
display, controlling the color of some RGB leds and hooks for his Android
Bluetooth App to manoeuvre the spider. Interestingly, he does not mention at all
that he is just redistributing the STL files created by RigesHsu in 2015 and
only a modified version of orginal code by SunFounder. He actually replaced 
the original copyright notice by SunFounder, added his name and a BSD 2-clause
license.


References:  
[1] https://github.com/sunfounder/SunFounder_Crawling_Quadruped_Robot_Kit_for_Arduino  
[2] https://www.instructables.com/id/DIY-Spider-RobotQuad-robot-Quadruped  
[3] http://regishsu.blogspot.com/2014/09/robot1.html  
[4] https://www.instructables.com/id/DIY-Spider-Robot-PART-II-Remote-control/  
[5] https://github.com/anoochit/arduino-quadruped-robot  
[6] https://github.com/anoochit/android-robot-bt-joypad  
[7] https://www.youtube.com/watch?v=wmmPD2v2RAA  
[8] https://drive.google.com/file/d/1O0KmWBFTaUCrSZ9OJg8fOSg2bq-MI83t/view  
[9] https://www.thingiverse.com/thing:2440237  
[10] https://www.youtube.com/watch?v=fvUhFBq7Z4g  
[11] https://www.hackster.io/mega-das/arduino-spider-robot-quadruped-57b832  
