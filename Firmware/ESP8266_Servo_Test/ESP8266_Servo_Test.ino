#include <Servo.h>

Servo servo;

void setup() {
  servo.attach(12);
}

void loop() {
  int pos;

  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos); 
    delay(15);          
  }
  for (pos = 180; pos >= 0; pos -= 1) { 
    servo.write(pos);              
    delay(15);                       
  }
}
