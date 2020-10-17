/*
 * This is a code created by Michael Lees to show how the Scout teams are using their arduinos
 * Date: 10-07-2020
 */
#include <Servo.h>

Servo M1;
Servo M2;
Servo M3;
Servo S1;
Servo S2;

const int B1 = 22;
const int B2 = 23;
const int B3 = 24;
const int Joy1X = 0; //X direction of Joystick 1 handles right/left movement of ROV
const int Joy1Y = 1; //Y direction of Joystick 1 handles forward/backward movement of ROV
const int Joy2Y = 2; //Y direction of joystick 2 handles arm tilt

void setup() 
{
  M1.attach(25);
  M2.attach(26);
  M3.attach(27);
  S1.attach(28);
  S2.attach(29);
  
  pinMode(B1, INPUT);
  pinMode(B2, INPUT);
  pinMode(B3, INPUT);
  Serial.begin(9600);
}

void loop() 
{
  // Set up some intergers to store the read data from the joysticks
  int Joy1X_Data = analogRead(Joy1X);
  int Joy1Y_Data = analogRead(Joy1Y);
  int Joy2Y_Data = analogRead(Joy2Y);

  // Map the stored intergers in the Joy**_Data to values useable by the motor escs
  int M1_Data = map(Joy1Y_Data, 0, 1023, 1200, 1700);
  int M2_Data = map(Joy1Y_Data, 0, 1023, 1200, 1700);
  int Turning_Data = map(Joy1X_Data, 0, 1023, 0, 300);

  // set up the turning of the ROV. EX: if Joy1X is pointed left than make sure one motor is going faster than the other
  if (Joy1X_Data < 500) {
    M1_Data = M1_Data - Turning_Data;
    M2_Data = M2_Data + Turning_Data;
  }
  else if (Joy1X_Data > 530) {
    M1_Data = M1_Data + Turning_Data;
    M2_Data = M2_Data - Turning_Data;
  }

  // set up the variables for the push buttons
  int B1_Data = digitalRead(B1);
  int B2_Data = digitalRead(B2);

  // set up the if statements to transform buttons presses into motor data
  int M3_Data = 1500;
  
  if (B1_Data == true) {
    M3_Data = 2000;
  }
  else if (B2_Data == true) {
    M3_Data = 1000;
  }

  // Set up the arm controls
  // intergers to store the values
  int S1_Data = analogRead(Joy2Y_Data);

  // Map that value to a value useable by the servo
  int S1_Data = map(Joy2Y_Data, 0, 1023, 1000, 2000);

  // Set up the opening and closing of the claw
  // set up some variables for the pushbuttons
  int B3_Data = digitalRead(B3);

  // set up the if statments to transform button presses into servo data
  int S2_Data = 1000;
  if (B3_Data == true) {
    S2_Data = 2000;
  }

  // write the motor and servo data to the actual motors and servos
  M1.writeMicroseconds(M1_Data);
  M2.writeMicroseconds(M2_Data);
  M3.writeMicroseconds(M3_Data);
  S1.writeMicroseconds(S1_Data);
  S2.writeMicroseconds(S2_Data);
}
