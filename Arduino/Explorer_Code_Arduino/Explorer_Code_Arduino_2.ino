#include <Servo.h>

Servo M1;
Servo M2;
Servo M3;
Servo M4;
Servo S1;
Servo S2;
Servo S3;
Servo S4;

int VA = 0; //1000-2000
int VB = 0; //1000-2000
int VC = 0; //1000-2000
int VD = 0; //1000-2000
int VE = 0; //1000-2000
int VF = 0; //1000-2000
int VG = 0; //1000-2000
int VH = 0; //1000-2000
int VI = 0; //1 or 0

int Lights = 13;

void setup()
{
  Serial.begin(115200);
  Serial.println();
  pinMode(Lights, OUTPUT);
  M1.attach(22);
  M2.attach(23);
  M3.attach(24);
  M4.attach(25);
  S1.attach(30);
  S2.attach(34);
  S3.attach(38);
  S4.attach(42);
}

void SerialEvent()
{
  char characterBuf[37];  //stores incoming
  int incomingLength = 0; //stores incoming length
  char *token;            //token for converting byte array to string array
  int counterNum = 1;
  //1503,1503,1500,1503,1523,1000,1500,0

  if (Serial.available()) {
    //    Serial.println("1");
    incomingLength = Serial.readBytesUntil('\n', characterBuf, 50);    //calculate length of byte array
    token = strtok(characterBuf, ",");  //convert to string
    VA = atoi(token);
    //    Serial.println(token);
    while (token != NULL) {   //if token doesnt find another comma it goes back to beginning

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

        case 8:
          VI = atoi(token);
          break;
      }
      counterNum++;
    }
  }
}
void loop()
{
  if (Serial.available()) {
    SerialEvent();

    M1.writeMicroseconds(VA);
    M2.writeMicroseconds(VB);
    M3.writeMicroseconds(VC);
    M4.writeMicroseconds(VD);
    S1.writeMicroseconds(VE);
    S2.writeMicroseconds(VF);
    S3.writeMicroseconds(VG);
    S4.writeMicroseconds(VH);

    if (VI == 1) {
      digitalWrite(Lights, HIGH);
    }
    else {
      digitalWrite(Lights, LOW);
    }
  }
  Serial.print("M1: ");
  Serial.print(VA);
  Serial.print("  ");
  Serial.print("M2: ");
  Serial.print(VB);
  Serial.print("  ");
  Serial.print("M3: ");
  Serial.print(VC);
  Serial.print("  ");
  Serial.print("M4: ");
  Serial.print(VD);
  Serial.print("  ");
  Serial.print("S1: ");
  Serial.print(VE);
  Serial.print("  ");
  Serial.print("S2: ");
  Serial.print(VF);
  Serial.print("  ");
  Serial.print("S3: ");
  Serial.print(VG);
  Serial.print("  ");
  Serial.print("S4: ");
  Serial.print(VH);
  Serial.print("  ");
  Serial.print("Lights: ");
  Serial.print(VI);
  Serial.println();
}
