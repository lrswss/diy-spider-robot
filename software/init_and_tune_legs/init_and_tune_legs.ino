/* 
 *  This sketch is based on "init_legs.ino" by RegisHsu.
 *  It is used to set all servos to a 90 degree angle
 *  BEFORE mounting the servo horns to fix all leg joints.
 *  
 *  With all horns mounted the alignment of the four legs
 *  usually doesn't match 90 degrees due fixed notches on
 *  the servo gears. Use the servo_adjust[][] matrix to 
 *  fine tune the position of all 12 servos and then copy 
 *  the results to the main sketch controlling the robot.
 *  
 */

#include <Servo.h>   
Servo servo[4][3];

//define servos' ports
//leg_postions: Leg1 (front,left), Leg2 (back,left), Leg3 (front, right), Leg4 (back, right)
//leg_parts: (middle, foot, shoulder)
const int servo_pin[4][3] = { {6, 7, 5}, {3, 4, 2}, {15, 16, 14}, {18, 19, 17} };

// adjust angle to exactly move servo arms at 90 degrees to main body
const float servo_adjust[4][3] = { {-5,0,9}, {-2,0,2}, {-10,-10,-8}, {5,7,-5} }; 

void setup() {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      servo[i][j].attach(servo_pin[i][j]);
      delay(50);
    }
  }
}

void loop(void) {
  int angle;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      angle = 90 - servo_adjust[i][j];  // set to 90 degrees with optional adjustment
      servo[i][j].write(angle);
      delay(250);
    }
    delay(500);
  }
}
