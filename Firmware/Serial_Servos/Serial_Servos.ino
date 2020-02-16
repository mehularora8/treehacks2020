#include <Servo.h>

Servo servoR;
Servo servoT;
Servo servoC;

const int recycle = 15;
const int trash = 13;
const int compost = 12;

void setup() {
  Serial.begin(115200);
  servoR.attach(recycle);
  servoT.attach(trash);
  servoC.attach(compost);

  servoR.write(0);
  servoT.write(0);
  servoC.write(0);
}

void loop() {
  while (Serial.available() > 0) {
    int command = Serial.parseInt();

    if (Serial.read() == '\n') {
      switch (command) {
        case recycle:
          servoR.write(180);
          delay(3000);
          servoR.write(0);
          break;
        case trash:
          servoT.write(180);
          delay(3000);
          servoT.write(0);
          break;
        case compost:
          servoC.write(180);
          delay(3000);
          servoC.write(0);
          break;
      }
    }


  }

}
