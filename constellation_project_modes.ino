/**
 * This is part of the Starbox Adruino project created as part of the AC22006 Physical Computing module.
 * The code below is developed for a stepper motor, a joystick and 3 buttons.
 * 
 * @authors Group 19 (Sarah Jane Hill, Dominika Piosik, Lorena Weepers, Jamie Burton, Reece Elder)
 * @version 20/03/2018
 */
 
// Declarations of analog input pins for joystick
const int Y_pin = A1;

// Declarations of digital output pins for stepper motor
const int A_pin = 8;
const int B_pin = 9;
const int C_pin = 10;
const int D_pin = 11;

// Declarations of input pins for buttons
const int button1Pin = 2;
const int button2Pin = 4;

// Declarations of variables representing the state of buttons
int button1State = 0;
int button2State = 0;

int currentStep = 3;    // number of current step
int numberOfSteps = 0;  // number of single steps made in one move

int joystickValue = 0;  // input value from joystick (on the Y axis)

int mode = 0;   // number of mode selected

bool stepDirection = true; // true for clockwise, false for counter-clockwise

void setup() 
{
  // Set the mode of button pins to input
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  // Set the mode of stepper pins to output
  pinMode(A_pin, OUTPUT);
  pinMode(B_pin, OUTPUT);
  pinMode(C_pin, OUTPUT);
  pinMode(D_pin, OUTPUT);

  // Initialise pin values as LOW
  digitalWrite(A_pin, LOW);
  digitalWrite(B_pin, LOW);  
  digitalWrite(C_pin, LOW); 
  digitalWrite(D_pin, LOW);
     
  Serial.begin(115200);

  Serial.println("*********************************");
  Serial.println(" ");
  Serial.println("   Welcome to Starbox!");
  Serial.println(" ");
  Serial.println("*********************************");
  Serial.println(" ");
  Serial.println("Choose mode:");
  Serial.println("Press 1 to choose Joystick mode");
  Serial.println("Press 2 to choose Auto mode");
} 

void loop() 
{
  if(mode == 0)   // if mode is equal to the initial value (no mode selected)
  {
    selectMode();
  }
  else
  {
    switch(mode)
    {
      case 1:
        joystickRead();
        break;
      case 2:
        stepDirection = true; // set the direction to clockwise
        
        // check if the user wants to use joystick to come back to previous slide
        joystickRead();  
         
        // rotate clockwise
        for(int i = 0; i < 256; i++)
        {
          stepper();
        }

        // wait for 10 seconds (short delay for demonstration purposes)
        delay(10000);
        break;
    }
  }
}

/**
 * Read input from buttons and set the mode (auto/joystick)
 */
int selectMode()
{
    button1State = digitalRead(button1Pin);     // read the input from button number 1
    button2State = digitalRead(button2Pin);     // read the input from button number 2
  
    if(button1State == HIGH)                  // if button 1 was pressed
    {
      Serial.println(" ");
      Serial.println("Joystick mode selected.");
      mode = 1;
    }
    else if(button2State == HIGH)             // if button 2 was pressed
    {
      Serial.println(" ");
      Serial.println("Auto mode selected.");
      mode = 2;
    }
}

/**
 * Control the motor
 */
void stepper()
{
  switch(currentStep)
  {
    case 0:
      digitalWrite(A_pin, HIGH);
      digitalWrite(B_pin, LOW);  
      digitalWrite(C_pin, LOW); 
      digitalWrite(D_pin, LOW);
      break;
     case 1:
      digitalWrite(A_pin, LOW);
      digitalWrite(B_pin, HIGH);  
      digitalWrite(C_pin, LOW); 
      digitalWrite(D_pin, LOW);
      break;
     case 2:
      digitalWrite(A_pin, LOW);
      digitalWrite(B_pin, LOW);  
      digitalWrite(C_pin, HIGH); 
      digitalWrite(D_pin, LOW);
      break;
     case 3:
      digitalWrite(A_pin, LOW);
      digitalWrite(B_pin, LOW);  
      digitalWrite(C_pin, LOW); 
      digitalWrite(D_pin, HIGH);
      break;
  }

  numberOfSteps++;    // increment the number of single moves 

  if(stepDirection == true)   // if clockwise
  {
    currentStep++;

    if(currentStep > 3)   // if all steps were carried out
    {
      currentStep = 0;    // come back to the first one
    }
  }
  else if(stepDirection == false)   // if counter-clockwise
  {
    currentStep--;    // repeat the steps backwards
    
    if(currentStep < 0)   // if all steps were carried out
    {
      currentStep = 3;    // come back to the last one since going backwards
    }
  }

  delay(5); // minimal delay to make the stepper work properly and as fast as possible
  
}

/**
 * Read in the current joystick value and if joystick mode is on - rotate
 */
int joystickRead()
{
  joystickValue = analogRead(Y_pin);  // read in the value along Y-axis
  Serial.println(joystickValue);

  if((joystickValue > 400) && (joystickValue < 480))  // values determined in testing
  {
    stepDirection = false;  // counter-clockwise direction selected
    
    // if joystick mode is on
    if(mode == 1)
    {
        // rotate counter-clockwise
        for(int i = 0; i < 256; i++)
        {
          stepper();
        }
    }
  }
  else if(joystickValue > 570)
  {
    stepDirection = true;   // clockwise direction selected
    // if joystick mode is on
    if(mode == 1) 
    {
        // rotate clockwise
        for(int i = 0; i < 256; i++)
        {
          stepper();
        }
    }
  }
  
  joystickValue = 0;  // reset the input value
}   

