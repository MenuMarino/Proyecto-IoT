#include <SoftwareSerial.h>

SoftwareSerial espSerial(17, 16); // RX, TX

int relayPin = 3;

#define SECONDS 1000

void setup() {
  Serial.begin(9600);
  espSerial.begin(9600);
  pinMode(relayPin, OUTPUT);
}

void prender_agua(){
  digitalWrite(relayPin, LOW); // Activa el motor de agua
}

void apagar_agua() {
  digitalWrite(relayPin, HIGH); // Desactiva el motor de agua
}

void loop() {
  int sensorValue = analogRead(A14);
  espSerial.print(sensorValue);

  if (sensorValue > 400 && sensorValue < 900) {
    Serial.println("Prender ");
    Serial.println(sensorValue);
    prender_agua();
  } else {
    Serial.println("Apagar ");
    Serial.println(sensorValue);
    apagar_agua();
  }
    delay(3 * SECONDS);
}
