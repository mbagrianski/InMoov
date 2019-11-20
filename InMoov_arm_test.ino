#include <Servo.h>

Servo myservo;

int potpin = A0;
int val;
int maxVal = 500; //maximum value of the potentiometer
int minVal = 0; //minimum value of the potentiometer
int specified = 0; //specify angle you want to set arm to (0-90 degrees)
int servoC = 96; //set this to servo 0 rotation angle

void setup() {
  Serial.begin(9600); 
  myservo.attach(9);
}

void loop() {
  val = analogRead(potpin);            
  val = map(val, minVal, maxVal, 0, 90);     
  if(val < specified){
    servoC--; //if the servo doesn't center, invert (change ++ to -- and vice versa)
    myservo.write(servoC);
  }else if(val > specified){
    servoC++;
    myservo.write(servoC);
  }
  delay(10);
  Serial.println(servoC);
}
