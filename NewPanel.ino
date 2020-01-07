// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int analogPin = A0;
int sensor;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  sensor = analogRead(analogPin);
  Serial.println(sensor);=-6  if(sensor > 1000){
    
  }else if(sensor > 700){
    lcd.clear();
    lcd.print("select");
  }else if(sensor > 500){
    lcd.clear();
    lcd.print("left");
  }else if(sensor > 300){
    lcd.clear();
    lcd.print("down");
  }else if(sensor > 100){
    lcd.clear();
    lcd.print("up");
  }else{
    lcd.clear();
    lcd.print("right");
  }
  // print the number of seconds since reset:
}
