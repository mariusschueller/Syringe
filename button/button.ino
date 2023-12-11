#include <AccelStepper.h>

AccelStepper stepper(AccelStepper::DRIVER, 3, 2); 

// In (mL/min). This will be used to determine speed. Will change with Potentiometer
//Will be a max
float maxFlowRate = 50.0;
float flowRate = maxFlowRate;

int speed;  //this will change depending on the Potentiometer reading...should it be a float?

float syringeDiameter = 14.0; //14 mm or 18.5 mm according to what I measured

 //8mm lead screw
int leadScrewPitch = 8;

//BUTTON STUFF
const int startButtonPin = 7;  // the number of the pushbutton pin
const int clockwiseButtonPin = 12;  // the number of the pushbutton pin

const int counterButtonPin = 13;  // the number of the pushbutton pin


// LIMIT SWITCH
int limitSwitch = 6;  // the number of the limit switch pin


//LED CODE HERE
int red_LED = 9;
int green_LED = 10;
int blue_LED = 11;

//POTENTIOMETER STUFF
// INPUT: Potentiometer should be connected to 5V and GND

int potPin = A3; // Potentiometer output connected to analog pin 3
int potVal = analogRead(potPin);  // Variable to store the input from the potentiometer


void setup()
{
  Serial.begin(9600);  // it doesn't look like it, but this allows you to print

  convertFlowToSpeed(); //speed gets get in this function

  stepper.setMaxSpeed(1000); // not sure if this is what it's supposed to be
  stepper.setSpeed(speed); 
  
  // probably set flow rate here with a function if we're feeling saucy

  pinMode(limitSwitch, INPUT_PULLUP); 

  pinMode(startButtonPin, INPUT_PULLUP);
  pinMode(clockwiseButtonPin, INPUT_PULLUP);
  pinMode(counterButtonPin, INPUT_PULLUP);

  pinMode(red_LED, OUTPUT);
  pinMode(green_LED, OUTPUT);
  pinMode(blue_LED, OUTPUT);
}

void loop()
{
  int redVal= 0;
  int greenVal = 0;
  int blueVal = 0;



  if (digitalRead(startButtonPin) == LOW) {
    potVal = analogRead(potPin);   // read the potentiometer value at the input pin
    // Serial.write(potVal);  // print the value pooped by the potentiometer

    //idk the actual conversion here but base on maximum flow rate eq: 1023 * x = maxFlowRate
    Serial.print("pot val:");
    Serial.println(potVal);
    
    flowRate = (maxFlowRate * potVal) / 1023.0; 
    Serial.print("flow rate: ");
    Serial.println(flowRate);
    
    // LED COLOR SHOULD BE GREEN  
    greenVal = 255;
  } else {  // syrige is paused
    flowRate = 0;

    //YELLOW LED
    redVal = 255;
    greenVal = 175; //hopefully for a darker yellow
    blueVal = 0;
  }
  
  convertFlowToSpeed(); 




  if (digitalRead(limitSwitch) == HIGH){
    // this is when the switch is clicked

    speed = 0; //setting speed so that flow rate is remembered
    

    // CHANGE LED TO RED
    redVal = 255;
    greenVal = 0;
    blueVal = 0;

    //print 0 here
  }

  else if (digitalRead(clockwiseButtonPin) == LOW) {
    speed = 50;

    //print conversion from 50 here
    Serial.println(convertSpeedToFlow(speed));
  }

  else if (digitalRead(counterButtonPin) == LOW) {
    speed = -50;

    //print conversion from -50 here
    Serial.println(convertSpeedToFlow(speed));
  }
  else {
    Serial.println(flowRate);
  }
  analogWrite(red_LED, redVal);
  analogWrite(green_LED, greenVal);
  analogWrite(blue_LED, blueVal);

  // should this go here??? I mean maybe. seems weird to constantly set speed but I feel like it makes sense
  stepper.setSpeed(speed);
  stepper.runSpeed();
}

// run this in setup and in loop
void convertFlowToSpeed(){ 
  float area = (3.141592 * pow(syringeDiameter / 10.0, 2)) / 4.0;
  Serial.print("area: ");
  Serial.println(area);


  Serial.print("max flow rate: ");
  Serial.println(maxFlowRate);

  // Serial.println((flowRate/60.0));
  speed = ((maxFlowRate/60.0) * 250.0)/area; //change to flowRate

  Serial.println(((maxFlowRate/60.0) * 250.0)/area);
  Serial.println(speed);
}

float convertSpeedToFlow(int spd){
  return (60 * spd * ((3.141592 * pow(syringeDiameter * 10, 2)) / 4)) / 250;
}
