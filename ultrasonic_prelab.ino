//including necessary libraries
#include <NewPing.h>
#include <Wire.h>
//declaring pins for trigger and echo
const int trigPin = 10;
const int echoPin = 9;
float duration, distance;

void setup() {
//starting ultrasonic pins
Serial.begin(9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);  

}

void loop() {
 
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
//calculating distance based on duration
duration = pulseIn(echoPin, HIGH);
distance = (duration*.0343)/2;
//printing distance to serial monitor (press the search button
//in top right to see this output!)
Serial.print(distance);
Serial.println(" cm");
delay(1000);
}
