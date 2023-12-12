#include <AccelStepper.h> 

AccelStepper stepper(AccelStepper::DRIVER, 3, 2);  

float flowRate = 50.0;  // mL/min 

int speed;  // steps/sec 

float syringeDiameter = 14.0;  // 14 mm or 18.5 mm 

int leadScrewPitch = 8;  // 8mm lead screw 

//BUTTONS 
const int startButtonPin = 7;  // the number of the pushbutton pin 
const int clockwiseButtonPin = 12;  // the number of the pushbutton pin 
const int counterButtonPin = 13;  // the number of the pushbutton pin 

// LIMIT SWITCH 
int limitSwitch = 6;  // the number of the limit switch pin 

//LEDs 
int red_LED = 9;  // Red led pin 
int green_LED = 10;  // Green led pin 
int blue_LED = 11;  // Blue led pin 

void setup() 
{ 
  convertFlowToSpeed();  //speed gets set in this function 
  stepper.setMaxSpeed(1000); 
  stepper.setSpeed(speed);  

  // Get all of the buttons set 
  pinMode(limitSwitch, INPUT_PULLUP);  
  pinMode(startButtonPin, INPUT_PULLUP); 
  pinMode(clockwiseButtonPin, INPUT_PULLUP); 
  pinMode(counterButtonPin, INPUT_PULLUP); 

  // get all of the LEDs set 
  pinMode(red_LED, OUTPUT); 
  pinMode(green_LED, OUTPUT); 
  pinMode(blue_LED, OUTPUT); 
} 

void loop() 
{ 
  // value between 0 and 255 for the color of the LED 
  int redVal= 0; 
  int greenVal = 0; 
  int blueVal = 0; 

  if (digitalRead(startButtonPin) == LOW) { 
    // set the speed 
    convertFlowToSpeed();  

    greenVal = 255; 
  } 
  else {  
    speed = 0; 
    
    redVal = 255; 
    greenVal = 175;  
  } 

  if (digitalRead(counterButtonPin) == LOW) { 
    speed = -50; 
  } 

  else if (digitalRead(limitSwitch) == HIGH){ 
    speed = 0;  
    redVal = 255; 
    greenVal = 0; 
  } 

  else if (digitalRead(clockwiseButtonPin) == LOW) { 
    speed = 50; 
  }  

  analogWrite(red_LED, redVal); 
  analogWrite(green_LED, greenVal); 
  analogWrite(blue_LED, blueVal); 

  stepper.setSpeed(speed); 
  stepper.runSpeed(); 
} 

// set the global speed variable here based on flow rate 
void convertFlowToSpeed(){  
  float area = (3.141592 * pow(syringeDiameter / 10.0, 2)) / 4.0; 
  speed = ((flowRate/60.0) * 250.0)/area;  
} 
