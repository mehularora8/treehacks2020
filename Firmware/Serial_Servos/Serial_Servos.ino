#include <Servo.h>

Servo servoR;
Servo servoT;
Servo servoC;

const int recycle = 14;
const int trash = 13;
const int compost = 12;
const int enabled = 90;
const int disabled = 180;

void setup() {
  Serial.begin(115200);
  servoR.attach(recycle);
  servoT.attach(trash);
  servoC.attach(compost);

  servoR.write(disabled);
  servoT.write(disabled);
  servoC.write(disabled);
}

void loop() {
  while (Serial.available() > 0) {
    int command = Serial.parseInt();

    if (Serial.read() == '\n') {
      Serial.println(command);
      switch (command) {
        case recycle:
          servoR.write(enabled);
          delay(3000);
          servoR.write(disabled);
          break;
        case trash:
          servoT.write(enabled);
          delay(3000);
          servoT.write(disabled);
          break;
        case compost:
          servoC.write(enabled);
          delay(3000);
          servoC.write(disabled);
          break;
      }
    }


  }

}
