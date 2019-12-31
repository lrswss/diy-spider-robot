/*
 * Sketch to test if all 12 servos are working 
 * and are located in the right position on each
 * of the four legs of the spider robot. This
 * sketch should be run BEFORE mounting the legs
 * to robot.
 */

#include <Servo.h>
Servo servo[4][3];

// Leg1 (front,left) { 6, 7, 5 }
// Leg2 (back,left) { 3, 4, 2 },
// Leg3 (front, right) { 15, 16, 14 },
// Leg4 (back, right) { 18, 19, 17 }
// Leg Servos: { middle, foot, shoulder }
const int servo_pin[4][3] = { { 6, 7, 5 }, { 3, 4, 2 }, { 15, 16, 14 }, { 18, 19, 17 } };

void setup()
{
  //initialize all servos
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      servo[i][j].attach(servo_pin[i][j]);
      delay(20);
    }
  }
}

void loop(void)
{
  int pos = 0;
  
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      for (pos = 0; pos <= 180; pos += 5) { // moves servos from 0 degrees to 180 degrees
      servo[i][j].write(pos);               // tell servo to go to position in variable 'pos'
      delay(15);                            // waits 15ms for the servo to reach the position
      }
      for (pos = 180; pos >= 0; pos -= 5) {
        servo[i][j].write(pos);
        delay(15);
      }
      delay(200);
    }
    delay(1000);
  }
}
