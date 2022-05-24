// For I2C       
#include <Wire.h>       
// Libraries for Matrix       
#include "Adafruit_LEDBackpack.h"       
#include "Adafruit_GFX.h"       
Adafruit_8x8matrix matrix = Adafruit_8x8matrix();

#include <NewPing.h> // We use NewPing to control the Ultrasonic Sensors #include <LiquidCrystal_I2C.h>



//ultrasonic pins
const int trigPin = 9;
const int echoPin = 10;

//ultrasonic 2 pins
const int trigPin2 = 11;
const int echoPin2 = 12;

float duration, distance, duration2, distance2;  

    
void setup() {       
Serial.begin(9600);       
// Good idea to send data to both        
// device and serial as it helps with       
// troubleshooting.               
// set the address       
matrix.begin(0x70); 
pinMode(trigPin, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin2, INPUT);
       
}    

 
void loop() {       

//ultrasonic 1
digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);
distance = (duration*.0343)/2;


//ultrasonic 2
digitalWrite(trigPin2, LOW);
delayMicroseconds(2);
digitalWrite(trigPin2, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin2, LOW);

duration2 = pulseIn(echoPin2, HIGH);
distance2 = (duration2*.0343)/2;


//calculate which ultrasonic sensor is closer
float difference = (distance2 - distance);

// Make sure where led 0x0 is:       
// And it is working       
matrix.setTextSize(1);       
matrix.setTextColor(LED_ON);   
// clear the matrix       
matrix.clear();       
// position the cursor      
matrix.setCursor(0,0);
//looking forward if detected object is in between,
//also acts as animation from left to right motion
//THIS NUMBER CAN BE TOGGLED TO YOUR SATISFACTION
if  (abs(difference) < 30 )  {
    matrix.drawCircle(3,3,3, LED_ON);
    matrix.drawPixel(3,3, LED_ON);
    matrix.drawPixel(3,4, LED_ON);
    matrix.drawPixel(4,3, LED_ON);
    matrix.drawPixel(4,4, LED_ON);
    matrix.writeDisplay();
}

//looking far right
else if (difference > 0) {
    matrix.drawCircle(3,3,3, LED_ON);
    matrix.drawPixel(3,2, LED_ON);
    matrix.drawPixel(3,3, LED_ON);
    matrix.drawPixel(4,2, LED_ON);
    matrix.drawPixel(4,3, LED_ON);
    matrix.writeDisplay();
  }
//looking far left
else {
    matrix.drawCircle(3,4,3, LED_ON);
    matrix.drawPixel(3,4, LED_ON);
    matrix.drawPixel(3,5, LED_ON);
    matrix.drawPixel(4,4, LED_ON);
    matrix.drawPixel(4,5, LED_ON);
    matrix.writeDisplay();
  }

  
 
float AnalogValue;
AnalogValue = analogRead(A0);
//brightness from ldr
//set to 3 different values
if ((1-(AnalogValue / 1023)) * 15 > 10) {
  matrix.setBrightness(12.5);
}
else if ((1-(AnalogValue / 1023)) * 15 <= 10 && (1-(AnalogValue / 1023)) * 15 > 5) {
  matrix.setBrightness(7.5);
}
else {
  matrix.setBrightness(2.5);
}
//atrix.setBrightness( (1-(AnalogValue / 1023)) * 15);
Serial.println((1-(AnalogValue / 1023)) * 15);
// how fast eyes move and brightness changes    
//THIS NUMBER CAN BE TOGGLED TO YOUR SATISFACTION
//a larger number means a more laggy animation, a smaller number
//makes it twitchy  
   delay(300);
 }        
