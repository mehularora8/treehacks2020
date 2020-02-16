#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <Servo.h>

const String HTTP_URL = "http://yestrashcan.azurewebsites.net/";

const int SERIAL_BAUD = 115200;
const String WIFI_SSID = "treehacks_24ghz";
const String WIFI_PWD = "";

const int TRASHCAN_EMPTY_HEIGHT = 40;
const int TRASHCAN_FULL_HEIGHT = 2;

const int TRASH_SERVO_PIN = 14;
const int RECYCLE_SERVO_PIN = 13;
const int COMPOST_SERVO_PIN = 12;

const int TRASH_TRIG_PIN = 4;
const int TRASH_ECHO_PIN = 5;
const int RECYCLE_TRIG_PIN = 4;
const int RECYCLE_ECHO_PIN = 16;
const int COMPOST_TRIG_PIN = 4;
const int COMPOST_ECHO_PIN = 15;

const int SERVO_ENABLED_ANGLE = 90;
const int SERVO_DISABLED_ANGLE = 180;

const int OPEN_TIME = 3000;

Servo servoT;
Servo servoR;
Servo servoC;

void postToWebsite() {
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    HTTPClient http;    //Declare object of class HTTPClient

    http.begin(HTTP_URL);      //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header

    String message = "id=";
    message += 1;
    message += "&trash=";
    delay(200);
    message += getUltrasonicMeasurement(TRASH_TRIG_PIN, TRASH_ECHO_PIN);
    message += "&compost=";
    delay(200);
    message += getUltrasonicMeasurement(COMPOST_TRIG_PIN, COMPOST_ECHO_PIN);
    message += "&recycling=";
    delay(200);
    message += getUltrasonicMeasurement(RECYCLE_TRIG_PIN, RECYCLE_ECHO_PIN);

    Serial.println(message);
    int httpCode = http.POST(message);
    String payload = http.getString();                                        //Get the response payload

    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload

    http.end();  //Close connection

  } else {

    Serial.println("Error in WiFi connection");

  }
}

int getUltrasonicMeasurement(int trig, int echo) {
  unsigned long t1;
  unsigned long t2;
  unsigned long pulse_width;
  float cm;
  float inches;

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  while (digitalRead(echo) == 0); // wait till we get a response
  t1 = micros();
  while (digitalRead(echo) == 1);
  t2 = micros();
  pulse_width = t2 - t1;

  inches = pulse_width / 148.0;

  return map(inches, TRASHCAN_EMPTY_HEIGHT, TRASHCAN_FULL_HEIGHT, 0, 100);
}


void setup() {
  Serial.begin(SERIAL_BAUD);         // Serial debug
  WiFi.begin(WIFI_SSID, WIFI_PWD);   // WiFi

  servoT.attach(TRASH_SERVO_PIN);
  servoR.attach(RECYCLE_SERVO_PIN);
  servoC.attach(COMPOST_SERVO_PIN);

  servoT.write(SERVO_DISABLED_ANGLE);
  servoR.write(SERVO_DISABLED_ANGLE);
  servoC.write(SERVO_DISABLED_ANGLE);

  pinMode(TRASH_TRIG_PIN, OUTPUT);
  digitalWrite(TRASH_TRIG_PIN, LOW);
  pinMode(TRASH_ECHO_PIN, INPUT);
  pinMode(RECYCLE_TRIG_PIN, OUTPUT);
  digitalWrite(RECYCLE_TRIG_PIN, LOW);
  pinMode(RECYCLE_ECHO_PIN, INPUT);
  pinMode(COMPOST_TRIG_PIN, OUTPUT);
  digitalWrite(COMPOST_TRIG_PIN, LOW);
  pinMode(COMPOST_ECHO_PIN, INPUT);

  while (WiFi.status() != WL_CONNECTED) {  //Wait for the WiFI connection completion

    delay(500);
    Serial.println("Waiting for connection...");

  }
  Serial.println("Connected to WiFi");

}

int resetTime = 0;
bool needToReset = false;

void loop() {


  if (needToReset & millis() > resetTime + 3000) {
    servoT.write(SERVO_DISABLED_ANGLE);
    servoR.write(SERVO_DISABLED_ANGLE);
    servoC.write(SERVO_DISABLED_ANGLE);

    delay(1000);

    postToWebsite();
    needToReset = false;

  }
  while (Serial.available() > 0) {
    int command = Serial.parseInt();



    if (Serial.read() == '\n') {
      switch (command) {
        case 0:
          Serial.println("trash");
          servoT.write(SERVO_ENABLED_ANGLE);
          resetTime = millis();
          needToReset = true;
          break;
        case 1:
          Serial.println("recycle");
          servoR.write(SERVO_ENABLED_ANGLE);
          resetTime = millis();
          needToReset = true;
          break;
        case 2:
          Serial.println("compost");
          servoC.write(SERVO_ENABLED_ANGLE);
          resetTime = millis();
          needToReset = true;
          break;
        case 3:
          Serial.println("nothing");
          servoT.write(SERVO_DISABLED_ANGLE);
          servoR.write(SERVO_DISABLED_ANGLE);
          servoC.write(SERVO_DISABLED_ANGLE);

          break;
      }

      delay(500);
    }


  }

}
