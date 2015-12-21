
#include <Servo.h>
Servo PlucoRekaL;
Servo PlucoRekaR;
Servo Serce;

const int magneticPin = 12;     // the number of the hall effect sensor pin

const int ledPinStress =  5;     // the number of the LED pin stres
const int ledPinRelax =  3;

const int PlucoRekaLeft = 9;    // the number of the servo left pin stres
const int PlucoRekaRight = 6;
const int Heart = 11;

//const int touch1 = 0;
const int touch2 = 8; // apacative sensor1


// variables will change:
          
//int dotyk1 = 0;       // variable for reading the capacative sensor1 status
int dotyk2 = 0;
int magState = HIGH;// variable for reading the capacative sensor2 status
int stan = 0;

 
void setup() {
  // initialize the LED pin as an output:
  pinMode(ledPinStress, OUTPUT);  
  pinMode(ledPinRelax, OUTPUT); 

  
 PlucoRekaL.attach(PlucoRekaLeft);
 PlucoRekaR.attach(PlucoRekaRight);
 Serce.attach(Heart);
 
 
  // initialize the hall effect sensor pin as an input:
  pinMode(magneticPin, INPUT);
digitalWrite(magneticPin,HIGH);  
}
 
void loop()
{
  //dotyk1 = readCapacitivePin(touch1);
  dotyk2 = readCapacitivePin(touch2);
    
  magState = digitalRead(magneticPin); // read the state of the hall effect sensor:

   
  while (stan == 0) 
  {
    digitalWrite(ledPinRelax, LOW);
    digitalWrite(ledPinStress, LOW);
    PlucoRekaL.write(40);
    PlucoRekaR.write(60);
    Serce.write(60);
    delay(800);
      PlucoRekaL.write(60);
    PlucoRekaR.write(40);
    Serce.write(40);
    delay(900);
    if (dotyk2>2) {stan=1;}
   if (magState == LOW) {stan=2;}
  } 

  
  if ( stan==1)
  {
  
    // turn Relax on: 
  for (int i=0; i <= 15; i++) 
 { 
    digitalWrite(ledPinRelax, HIGH);
    digitalWrite(ledPinStress, LOW);
    PlucoRekaL.write(40);
    PlucoRekaR.write(60);
    Serce.write(40);
    delay(700);
      PlucoRekaL.write(60);
    PlucoRekaR.write(40);
    Serce.write(60);
    delay(800);
 }
stan=0; 
  } 
  
  if (stan=2)
   
  {
    // turn stress mode:
     digitalWrite(ledPinRelax, LOW);
    digitalWrite(ledPinStress, HIGH);
    PlucoRekaL.write(40);
    PlucoRekaR.write(60);
    Serce.write(40);
    delay(300);
      PlucoRekaL.write (60);
    PlucoRekaR.write(40);
    Serce.write(60);
    delay(300);
     //dotyk1 = readCapacitivePin(touch1);
  dotyk2 = readCapacitivePin(touch2);
  if (dotyk2>2) {stan=1;}
  
  }
   if (dotyk2>2) {stan=1;}
   if (magState == LOW) {stan=2;}
}



uint8_t readCapacitivePin(int pinToMeasure) {
  // Variables used to translate from Arduino to AVR pin naming
  volatile uint8_t* port;
  volatile uint8_t* ddr;
  volatile uint8_t* pin;
  // translate the input pin number from
  //  Arduino pin number to the AVR PORT, PIN, DDR,
  
  byte bitmask;
  port = portOutputRegister(digitalPinToPort(pinToMeasure));
  ddr = portModeRegister(digitalPinToPort(pinToMeasure));
  bitmask = digitalPinToBitMask(pinToMeasure);
  pin = portInputRegister(digitalPinToPort(pinToMeasure));
  // Discharge the pin first by setting it low and output
  *port &= ~(bitmask);
  *ddr  |= bitmask;
  delay(1);
  uint8_t SREG_old = SREG; //back up the AVR Status Register
  // Prevent the timer IRQ from disturbing  measurement
  noInterrupts();
  // Make the pin an input with the internal pull-up on
  *ddr &= ~(bitmask);
  *port |= bitmask;

  //  unrolling of the loop decreases the number of hardware cycles between each read of the pin,
  //  increasing sensitivity.
  uint8_t cycles = 17;
       if (*pin & bitmask) { cycles =  0;}
  else if (*pin & bitmask) { cycles =  1;}
  else if (*pin & bitmask) { cycles =  2;}
  else if (*pin & bitmask) { cycles =  3;}
  else if (*pin & bitmask) { cycles =  4;}
  else if (*pin & bitmask) { cycles =  5;}
  else if (*pin & bitmask) { cycles =  6;}
  else if (*pin & bitmask) { cycles =  7;}
  else if (*pin & bitmask) { cycles =  8;}
  else if (*pin & bitmask) { cycles =  9;}
  else if (*pin & bitmask) { cycles = 10;}
  else if (*pin & bitmask) { cycles = 11;}
  else if (*pin & bitmask) { cycles = 12;}
  else if (*pin & bitmask) { cycles = 13;}
  else if (*pin & bitmask) { cycles = 14;}
  else if (*pin & bitmask) { cycles = 15;}
  else if (*pin & bitmask) { cycles = 16;}

  // End of timing-critical section; turn interrupts back on if they were on before, or leave them off if they were off before
  SREG = SREG_old;

  // Discharge the pin by setting it low and output

  *port &= ~(bitmask);
  *ddr  |= bitmask;

  return cycles;
}

