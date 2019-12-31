/* 
 * IR Receiver/Decoder for Attiny85
 * 
 * Decodes IR codes from a cheap chinese remote control
 * and sends short commands via SoftSerial to other MCU
 * 
 * Copyright (c) 2019 Lars Wessels
 * 
 * Permission is hereby granted, free of charge, to any person 
 * obtaining a copy of this software and associated documentation 
 * files (the "Software"), to deal in the Software without 
 * restriction, including without limitation the right to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 * OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR 
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Attiny85 Pinout:
 *               ------
 *  (SS)PB5 - 1 |  \/  | 8 - Vcc
 *      PB3 - 2 |      | 7 - PB2 (SCK)  + SCL
 *      PB4 - 3 |      | 6 - PB1 (MISO)
 *      GND - 4 |      | 5 - PB0 (MOSI) + SDA
 *               ------
 * - IR Receiver is connected to Pin 3
 * - Status LED on Pin 5
 * - TX to other MCU RX on Pin 2            
 * 
 */

// https://github.com/z3t0/Arduino-IRremote
// To disable unused decoders in "IRremoteInt.h" or the code 
// won't fit into Attinys flash; actually disabled all decoders
// since my chinese remote didn't match neither one; commands
// are hard coded (see below)
#include <IRremote.h>
#include <SoftwareSerial.h>

#define LED_PIN 0      // Pin 5 on Attiny85
#define IR_RECV_PIN 4  // Pin 3
#define TX_PIN 3       // Pin 2
#define RX_PIN 2       // Pin 7 (not used)

SoftwareSerial SoftSerial(RX_PIN, TX_PIN); // RX, TX
IRrecv irrecv(IR_RECV_PIN);
decode_results results;

void setup() {
  SoftSerial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  irrecv.enableIRIn(); // start the receiver
  SoftSerial.println("Attiny85 IR Receiver/Decoder ready...");
}

void loop() {
  if (irrecv.decode(&results)) {
    digitalWrite(LED_PIN, HIGH);
    switch(results.value) {
      case 0x511DBB:
        SoftSerial.println("U");  // up
        break;
      case 0x52A3D41F:
        SoftSerial.println("L");  // left
        break;     
      case 0x20FE4DBB:
        SoftSerial.println("R");  // right
        break;
      case 0xA3C8EDDB:
        SoftSerial.println("D");  // down
        break;
      case 0xD7E84B1B:
        SoftSerial.println("K");  // ok
        break;
      case 0xC101E57B:
        SoftSerial.println("1");
        break;
      case 0x97483BFB:
        SoftSerial.println("2");
        break;
      case 0xF0C41643:
        SoftSerial.println("3");
        break;
      case 0x9716BE3F:
        SoftSerial.println("4");
        break;      
      case 0x3D9AE3F7:
        SoftSerial.println("5");
        break;     
      case 0x6182021B:
        SoftSerial.println("6");
        break;
      case 0x8C22657B:
        SoftSerial.println("7");
        break;  
      case 0x488F3CBB:
        SoftSerial.println("8");
        break;        
      case 0x449E79F:
        SoftSerial.println("9");
        break; 
      case 0x1BC0157B:
        SoftSerial.println("0");
        break;    
      case 0x32C6FDF7:
        SoftSerial.println("S");  // star
        break;     
      case 0x3EC3FC1B:
        SoftSerial.println("P");  // pound sign
        break;                    
      default:
        SoftSerial.println(results.value, HEX);
    }
    irrecv.resume(); // receive the next value
  }
  digitalWrite(LED_PIN, LOW);
}
