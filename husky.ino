#include "HUSKYLENS.h"
#include "SoftwareSerial.h"

HUSKYLENS huskylens;
SoftwareSerial mySerial(10, 11); // RX, TX -- connect to pins 10/11, NOT 0/1

const int greenLED = 5;
const int redLED = 4;
const int yellowLED = 3;

void setup() {
  Serial.begin(115200);

  pinMode(greenLED, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);

  allOff();

  mySerial.begin(9600);

  while (!huskylens.begin(mySerial)) {
    Serial.println("HuskyLens not connected!");
    delay(1000);
  }

  Serial.println("HuskyLens Ready");
}

void allOff() {
  digitalWrite(greenLED, LOW);
  digitalWrite(redLED, LOW);
  digitalWrite(yellowLED, LOW);
}

void loop() {
  

  if (!huskylens.request()) {
    Serial.println("Request failed");
    delay(100);
    return;
  }

  if (!huskylens.available()) {
    allOff();
    return;
  }

  HUSKYLENSResult result = huskylens.read();

  Serial.print("ID: ");
  Serial.println(result.ID);

  allOff(); // turn off all LEDs before lighting the correct one

  switch (result.ID) {

    case 1: // Green
      digitalWrite(greenLED, HIGH);
      break;

    case 2: // Red
      digitalWrite(redLED, HIGH);
      break;

    case 3: // Yellow
      digitalWrite(yellowLED, HIGH);
      break;

    default:
      allOff();
      break;
  }

  delay(50);
}