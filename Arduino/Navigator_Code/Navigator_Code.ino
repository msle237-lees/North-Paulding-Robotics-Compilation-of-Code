#include <XBOXOLD.h>
#include <usbhub.h>

#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

USB Usb;
USBHub  Hub1(&Usb); 
XBOXOLD Xbox(&Usb);

// Everything above is needed for the Xbox controller to work correctly
// The include statements/variables below are used to transform the xbox data to motor/servo data

#include <Servo.h>

Servo M1; // Horizontal Right Motor
Servo M2; // Horizontal Left Motor
Servo M3; // Vertical Motor
Servo S1; // Camera Servo
Servo S2; // Tilt Servo
Servo S3; // Open/Close Servo


// These variables initialize what data we are writing to the servo and setting all of them to their midpoint/stop position.
int M1_Data = 1500;
int M2_Data = 1500;
int M3_Data = 1500;
int S1_Data = 1500;
int S2_Data = 1500;
int S3_Data = 1500;
int Turning_Data = 0;

void setup() {
  Serial.begin(115200);
  // These lines tell the arduino what pins the motors/servos are connected to
  M1.attach(22);
  M2.attach(23);
  M3.attach(24);
  S1.attach(25);
  S2.attach(26);
  S3.attach(27);

  // Write all motors/servos to their stop/midposition in order to not break anything
  M1.writeMicroseconds(M1_Data);
  M2.writeMicroseconds(M2_Data);
  M3.writeMicroseconds(M3_Data);
  S1.writeMicroseconds(S1_Data);
  S2.writeMicroseconds(S2_Data);
  S3.writeMicroseconds(S3_Data);
  
#if !defined(__MIPSEL__)
  while (!Serial); 
#endif
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); // halt
  }
  Serial.print(F("\r\nXBOX Library Started"));
}
void loop() {
  Usb.Task();
  if (Xbox.XboxConnected) {
    if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500 || Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500 || Xbox.getAnalogHat(RightHatX) > 7500 || Xbox.getAnalogHat(RightHatX) < -7500 || Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
      if (Xbox.getAnalogHat(LeftHatX) > 7500 || Xbox.getAnalogHat(LeftHatX) < -7500) {
        // LeftHatX will be for turning the ROV (M1 and M2)
        // Turning data will be between 0 and 200 depending on what way the joystick is pushed and how far (Will always return to 0)
        Turning_Data = map(Xbox.getAnalogHat(LeftHatX), 7500, 32767, 0, 200);
        if (Xbox.getAnalogHat(LeftHatX) > 7500) {
          M1_Data = M1_Data - Turning_Data;
          M2_Data = M2_Data + Turning_Data;
        }
        else if (Xbox.getAnalogHat(LeftHatX) < -7500) {
          M1_Data = M1_Data + Turning_Data;
          M2_Data = M2_Data - Turning_Data;
        }
      }
      if (Xbox.getAnalogHat(LeftHatY) > 7500 || Xbox.getAnalogHat(LeftHatY) < -7500) {
        // LeftHatY will be for moving the ROV forward or backward (M1 and M2)
        // M1_Data and M2_Data will be between 1200 and 1800 depending on what way the joystick is pushed and how far (Will always return to 1500)
        M1_Data = map(Xbox.getAnalogHat(LeftHatY), -32767, 32767, 1200, 1800);
        M2_Data = map(Xbox.getAnalogHat(LeftHatY), -32767, 32767, 1200, 1800);
      }
      if (Xbox.getAnalogHat(RightHatY) > 7500 || Xbox.getAnalogHat(RightHatY) < -7500) {
        // RightHatY will be for moving the arm tilt up and down (S2)
        // S2_Data will be between 1200 and 1800 depending on what way the joystick is pushed and how far. (It will always return to 1500)
        S2_Data = map(Xbox.getAnalogHat(RightHatY), -32767, 32767, 1200, 1800);
      }
      Serial.println();
    }

    if (Xbox.getButtonClick(UP)) {
      // Will be for moving the ROV up (M3) 
      // Will be 1800 if held.
      M3_Data = 1800;
    }
    else if (Xbox.getButtonClick(DOWN)) {
      // Will be for moving the ROV down (M3)
      // Will be 1200 if held.
      M3_Data = 1200;
    }
    else {
      M3_Data = 1500;
    }

    if (Xbox.getButtonPress(A)) {
      // Will be for tilting the camera down (S1)
      // Will decrement S1_Data by 10
      S1_Data = S1_Data - 10;
    }
    if (Xbox.getButtonPress(B)) {
      // Will be for tilting the camera up (S1)
      // Will increment S1_Data by 10
      S1_Data = S1_Data + 10;
    }
    if (Xbox.getButtonPress(L1)) {
      // Will be for opening and closing the claw (S3)
      // Will be 1800 if pressed and 1200 if released
      S3_Data = 1800;
    }
    else {
      S3_Data = 1200;
    }
  }
  delay(1);
}
