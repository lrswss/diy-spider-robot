/* IR Remote Control Detective v4 
   http://www.technoblogy.com/show?24A9
   
   David Johnson-Davies - www.technoblogy.com - 8th May 2018
   ATtiny85 @ 1 MHz (internal oscillator; BOD disabled)

   Lars Wessels - 24th February 2019
   Removed OLED Display code, use SoftSerial instead
   
   CC BY 4.0
   Licensed under a Creative Commons Attribution 4.0 International license: 
   http://creativecommons.org/licenses/by/4.0/ 
*/

#include <SoftwareSerial.h>

#define IR_RECV_PIN 3 // Pin 2 on Attiny85
#define TX_PIN 1 // Pin 6 on Attiny85
#define RX_PIN 2 // Pin 7 on Attiny85


SoftwareSerial SoftSerial(RX_PIN, TX_PIN);  // RX, TX


// Setup **********************************************
  
void setup() {
  SoftSerial.begin(9600);
  // Set up Timer/Counter1 (assumes 1MHz clock)
  TCCR1 = 7<<CS10;            // No compare matches ; /64
  // Set up pin change interrupt on PB3
  PCMSK = 1<<PCINT3;          // Interrupt on PB3
  GIMSK = 1<<PCIE;            // Enable pin change interrupts
  SoftSerial.println("Attiny85 IR Decoder");
}

void loop() {
  // Everything done under interrupt!
}


void ReceivedCode(char IRtype, unsigned int Address, unsigned int Command) {
  if (IRtype>32) {
    SoftSerial.print("IR-Type: ");
    SoftSerial.println(IRtype);
  } else {
    SoftSerial.print("IR-Type: ");
    SoftSerial.print("S");
    SoftSerial.print((IRtype/10)+'0');
    SoftSerial.print((IRtype%10)+'0');
  }
  SoftSerial.print("Address: ");
  SoftSerial.println(Address);
  SoftSerial.print("Command: ");
  SoftSerial.println(Command);
}

// Globals
volatile unsigned long RecdData;
volatile int Bit, Edge;
volatile char IRtype;
  
// Protocol timings
const int Micros = 64; // Number of microseconds per TCNT1 count

const int SonyIntro = 2400/Micros;
const int SonyMean = 900/Micros;

const int NECIntro = 9000/Micros;
const int NECGap = 4500/Micros;
const int NECPulse = 562/Micros;
const int NECMean = 1125/Micros;

const int SamsungIntro = 5000/Micros;
const int SamsungGap = 5000/Micros;

const int RC5Half = 889/Micros;    // 0.889ms
const int RC5Full = 1778/Micros;
const int RC5Mean = 1334/Micros;

// Interrupt service routine - called on Timer/Counter1 overflow
ISR(TIMER1_OVF_vect) {
  ReceivedCode(Bit, RecdData>>7, RecdData & 0x7F);
  TIMSK = TIMSK & ~(1<<TOIE1);                  // Disable overflow interrupt
  TCNT1 = 250;
}

// Interrupt service routine - called on each edge of PB3
ISR(PCINT0_vect) {
  static int Mid;  // Edge: 0 = falling, 1 = rising
  int Time = TCNT1;
  if (TIFR & 1<<TOV1) { IRtype = 0; Edge = 1; }        // Overflow
  else if (Edge != (PINB>>PINB3 & 1));                 // Ignore if wrong edge
  else if (IRtype == 0) {
  
    // End of intro pulse
    if (abs(Time - RC5Half) < 5) {
      IRtype = 'R'; RecdData = 0x2000; Bit = 12; Edge = 0; Mid = 0;
    } else if (abs(Time - RC5Full) < 5) {
      IRtype = 'R'; RecdData = 0x2000; Bit = 11; Edge = 0; Mid = 1;
    } else if ((abs(Time - SonyIntro) < 5) && (Edge == 1)) {
      IRtype = 'S'; RecdData = 0; Bit = 0;
      TIMSK = TIMSK | 1<<TOIE1;                        // Enable overflow interrupt
    } else if (abs(Time - SamsungIntro) < 18) {
      IRtype = 'M'; RecdData = 0; Bit = -1; Edge = 0;  // Ignore first falling edge
    } else if (abs(Time - NECIntro) < 18) { 
      IRtype = 'N'; RecdData = 0; Bit = -1; Edge = 0;  // Ignore first falling edge
    }
  
  // Data bit
  } else if (IRtype == 'R') {
    Edge = !Edge;
    if ((Time < RC5Mean) && Mid) {
      Mid = 0;
    } else {
      Mid = 1;
      RecdData = RecdData | ((unsigned long) Edge<<Bit);
      if (Bit == 0) ReceivedCode('R', RecdData>>6 & 0x1F,
        (~(RecdData>>6) & 0x40) | (RecdData & 0x3F));
      Bit--;
    }
  } else if (IRtype == 'S') {
    if (Time > SonyMean) RecdData = RecdData | ((unsigned long) 1<<Bit);
    Bit++;
  } else if ((IRtype == 'N') || (IRtype == 'M')) {
    if (Time > NECMean && Bit >= 0) RecdData = RecdData | ((unsigned long) 1<<Bit);
    Bit++;
    if (Bit == 32) ReceivedCode(IRtype, RecdData & 0xFFFF, RecdData>>16);
  }
  
  TCNT1 = 0;                  // Clear counter
  TIFR = TIFR | 1<<TOV1;      // Clear overflow
}
