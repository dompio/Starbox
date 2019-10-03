/**
 * This is part of the Starbox Arduino project created as part of the AC22006 Physical Computing module.
 * The code below is developed for a force sensitive resistor and a lamp.
 * 
 * @authors Group 19 (Sarah Jane Hill, Dominika Piosik, Lorena Weepers, Jamie Burton, Reece Elder)
 * @version 20/03/2018
 */

// Declaration of input pin for a force sensitive resistor (FSR)
int fsrPin = A0;
// Declaration of output pin for a lamp
int lampPin = 3;

// Variable to store the input value from the FSR
int force;

int previousState = 0;  // previous state of the FSR
int currentState = 0;   // current state of the FSR

boolean latchOn = false;  // is the lamp on

void setup() 
{
  // Set fsrPin to input and lampPin to output
  pinMode(fsrPin, INPUT);
  pinMode(lampPin, OUTPUT);

  // Set the data rate to 9600 bps for communication between the Arduino and a computer
  Serial.begin(9600);
}

void loop() 
{
  // Read in the value from the FSR and print in in Serial Monitor for testing
  force = analogRead(fsrPin);
  Serial.println(force);

  // if force is higher than 40 - the value was determined in testing
  // as there is a small resistance on the FSR when the lamp is on
  if(force > 40) 
  {
    currentState = HIGH;  // change the state to HIGH - FSR touched
  }
  else
  {
    currentState = LOW;   // change the state to LOW - FSR not touched
  }

  if(currentState != previousState)   // if the state changed
  {
    if(currentState == HIGH && latchOn == false)    // if the FSR was touched and lamp is off
    {
      digitalWrite(lampPin, HIGH);    // turn lamp on
      latchOn = true;
    }
    else if(currentState == HIGH && latchOn == true)  // if the FSR was touched and lamp in on
    {
      digitalWrite(lampPin, LOW);    // turn lamp off
      latchOn = false;
    }
  }

  delay(100);

  previousState = currentState;   // set previous state to be current state
}
