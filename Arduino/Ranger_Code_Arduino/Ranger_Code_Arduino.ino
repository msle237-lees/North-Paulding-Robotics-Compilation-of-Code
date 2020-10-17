#include <Servo.h>

Servo M1;
Servo M2;
Servo M3;
Servo M4;
Servo S1;
Servo S2;
Servo S3;
Servo S4;

int lights = 12;

int VA = 1500; //Motor 1
int VB = 1500; //Motor 2
int VC = 1500; //Motor 3 & 4
int VD = 1500; //Servo 1
int VE = 1500; //Servo 2
int VF = 1500; //Servo 3
int VG = 1500; //Servo 4
int VH = 1; //Lights
//1500 1500 1500 1500 1500 1500 1500 1
void setup() 
{
  Serial.begin(115200);
  pinMode(lights, OUTPUT);
  M1.attach(22);
  M2.attach(23);
  M3.attach(24);
  M4.attach(25);
  S1.attach(26);
  S2.attach(27);
  S3.attach(28);
  S4.attach(29);
}

void SerialEvent()
{
  char characterBuf[37];  //stores incoming
  int incomingLength = 0; //stores incoming length
  char *token;            //token for converting byte array to string array
  int counterNum = 1;


  if (Serial.available()) 
  {
    //    Serial.println("1");
    incomingLength = Serial.readBytesUntil('\n', characterBuf, 50);    //calculate length of byte array
    token = strtok(characterBuf, " ");  //convert to string
    VA = atoi(token);
    while (token != NULL) {   //if token doesnt find another comma it goes back to begginning

      token = strtok(NULL, ",");  //changes token to a string def of NULL
      //      Serial.println(token);

      switch (counterNum) {
        case 1:
          VB = atoi(token);
          break;
        case 2:
          VC = atoi(token);
          break;
        case 3:
          VD = atoi(token);
          break;
        case 4:
          VE = atoi(token);
          break;
        case 5:
          VF = atoi(token);
          break;
        case 6:
          VG = atoi(token);
          break;
        case 7:
          VH = atoi(token);
          break;
      }
      counterNum++;
    }
  }
}

void loop() 
{
  SerialEvent();
  M1.writeMicroseconds(VA);
  M2.writeMicroseconds(VB);
  M3.writeMicroseconds(VC);
  M4.writeMicroseconds(VC);
  S1.writeMicroseconds(VD);
  S2.writeMicroseconds(VE);
  S3.writeMicroseconds(VF);
  S4.writeMicroseconds(VG);
  if (VF == 1) {
    digitalWrite(lights, HIGH);
  }
  else {
    digitalWrite(lights, LOW);
  }
}
