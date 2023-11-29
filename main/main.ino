#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 3, 2); 

float flowRate = 0.0;  // In (mL/min). This will be used to determine speed. Will change with Potentiometer

int speed;  //this will change depending on the Potentiometer reading...should it be a float?

float syringeDiameter = 1.0;

//POTENTIOMETER STUFF
// INPUT: Potentiometer should be connected to 5V and GND
/*
int potPin = A3; // Potentiometer output connected to analog pin 3
int potVal = 0; // Variable to store the input from the potentiometer

potVal = analogRead(potPin);   // read the potentiometer value at the input pin
*/

//BUTTON STUFF
const int button1Pin = 2;  // the number of the pushbutton pin
int button1State = 0;  // variable for reading the pushbutton status

//two more buttons for extra credit
/*
const int button2Pin = 3;  // the number of the pushbutton pin
int button2State = 0;  // variable for reading the pushbutton status

const int button3Pin = ;  // the number of the pushbutton pin
int button3State = 0;  // variable for reading the pushbutton status
*/

// LIQUID CRYSTAL DISPLAY
/*
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
*/

// LIMIT SWITCH
int limitSwitch = 8;  // the number of the limit switch pin

void setup()
{
  Serial.begin(9600);  // it doesn't look like it, but this allows you to print

  convertFlowToSpeed(); //speed gets get in this function

  stepper.setMaxSpeed(1000); // not sure if this is what it's supposed to be
  stepper.setSpeed(speed); 
  
  // probably set flow rate here with a function if we're feeling saucy

  pinMode(limitSwitch, INPUT_PULLUP); 

  pinMode(button1Pin, INPUT);

  //more stuff here for extra credit
}

void loop()
{
   //potentiometer
  /*
  potVal = analogRead(potPin);   // read the potentiometer value at the input pin
  Serial.write(potVal);  // print the value pooped by the potentiometer
  */
  

  button1State = digitalRead(button1Pin);
  if (button1State == HIGH) {
    flowRate = 10.0; //random value for lols, but it should be based on potentiometer
  } else {
    flowRate = 0;
  }

  // Here's some code for other button stuff that I felt like writing
  //for clockwise motion?
  /*
  button2State = digitalRead(button2Pin);
  if (button2State == HIGH) {
    speed = 100; //random value for lols, but it should be based on potentiometer
  } else {
    speed = 0;
  }

  // set speed to negative for the other way...crazy
*/
  if (digitalRead(limitSwitch) == 1){
    // this is when the switch is clicked
    flowRate = 0;  // I would assume this would stop the motor by eventually setting speed to 0, but I have been wrong before
  }

  convertFlowToSpeed(); 

  // should this go here??? I mean maybe. seems weird to constantly set speed but I feel like it makes sense
  stepper.setSpeed(speed);
  stepper.runSpeed();
}

// run this in setup and in loop
void convertFlowToSpeed(){ 
  //helpful to know that each step is 1.8 degrees and 200 steps is a full rotation
  //should speed be a float???
  //need to also account for syringe pump diameter
  speed = flowRate * 100; //This is a placeholder, there will be correct stuff here later I hope
}

// a possibly useful button function
/*
int buttonPressed(uint8_t button) {
  static uint16_t lastStates = 0;
  uint8_t state = digitalRead(button);
  if (state != ((lastStates >> button) & 1)) {
    lastStates ^= 1 << button;
    return state == HIGH;
  }
  return false;
}*/

// for display, probably a funciton for calculating amount of time remaining cause I don't wanna write the code in the loop
/*float timeRemaining(){
  // dang, we'll probably need to have the position, I hope the library has a built in position, but we'll need to calc pos anyways
  return 0;
}*/
