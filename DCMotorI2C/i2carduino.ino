#include <Wire.h>
#define SLAVE_ADDRESS 0x04
#define LED  13
int number = 0;
int rec = 0;

const int switchPin = 2;    // switch input
const int motor1Pin = 3;    // H-bridge leg 1 (pin 2, 1A)
const int motor2Pin = 4;    // H-bridge leg 2 (pin 7, 2A)
const int enablePin = 9;    // H-bridge enable pin

void setup() {
  // set the switch as an input:
  pinMode(switchPin, INPUT); 
 
  // set all the other pins you're using as outputs:
  pinMode(motor1Pin, OUTPUT);
  pinMode(motor2Pin, OUTPUT);
  pinMode(enablePin, OUTPUT);
 
  // set enablePin high so that motor can turn on:
  digitalWrite(enablePin, HIGH);

  pinMode(LED, OUTPUT);

  // I2C Setup
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(sendData);
  Serial.println("Ready!");
}
void loop() {
  // if the switch is high, motor will turn on one direction:
    if (digitalRead(switchPin) == HIGH) {
      digitalWrite(enablePin, LOW);
      ::number = 0;
    }
    // if the switch is low, motor will turn in the other direction:
    else {
      ::number = 1;
      digitalWrite(enablePin, HIGH);
      digitalWrite(motor1Pin, HIGH);  // set leg 1 of the H-bridge high
      digitalWrite(motor2Pin, LOW);   // set leg 2 of the H-bridge low
    }
}
void receiveData(int byteCount) {
  Serial.print("receiveData");
  while (Wire.available()) {
    rec = Wire.read();
    Serial.print("data received: ");
    Serial.println(number);
    if (number == 1) {
      Serial.println(" LED ON");
      digitalWrite(LED, HIGH);
    } else {
      Serial.println(" LED OFF");
      digitalWrite(LED, LOW);
    }
  }
}
void sendData() {
  Wire.write(number);
}
