#include<Wire.h>
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 8, en = 9, d4 = 4, d5 = 5, d6 = 6, d7 = 7;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int motor = 0, motorVal = 90;

const int analogPin = A0;
int sensor;

void setup() {
  Serial.begin(9600); //Starts Serial Com
  Wire.begin(); //Begins I2C communication at pin (A4,A5)
  lcd.begin(16, 2);
  lcd.print("hello, world!");
}

void loop() {
  updateSensor();
  if (sensor > 1000) {

  } else if (sensor > 700) {
    lcd.clear();
    lcd.print("select");
    delay(200);
  } else if (sensor > 500) {
    lcd.clear();
    lcd.print("left");
    delay(200);
    switchMotor();
  } else if (sensor > 300) {
    lcd.clear();
    lcd.print("down");
    delay(200);
  } else if (sensor > 100) {
    lcd.clear();
    lcd.print("up");
    delay(200);
  } else {
    lcd.clear();
    lcd.print("right");
    delay(200);
  }
}

void switchMotor() {
  if (motor < 5) {
    motor++;
  } else {
    motor = 0;
  }
}

void setMotor(int motor, double pos) {
  updateSensor();
    
  while (sensor < 700 || sensor > 1000) {
    
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor ");
    lcd.print(motor);
    lcd.print(" pos -/+");
  
    if (sensor > 500) { //left      
      lcd.setCursor(0, 1);
      decrementMotor();
      lcd.print(motorVal);
    } else if (sensor > 300) { //down
      
    } else if (sensor > 100) { //up
      
    } else { //right
      lcd.setCursor(0, 1);
      incrementMotor();
      lcd.print(motorVal);
    }    
    updateSensor();    
  }

  if(sensor > 700){
    sendMsg(motor, motorVal);
  }
}

void incrementMotor(){
  if(motorVal <= 180){
    motorVal++;
  }else{
    error("Ex_lim+");
  }
}

void decrementMotor(){
  if(motorVal >= 0){
    motorVal--;
  }else{
    error("Ex_lim-");
  }
}

void error(String message){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error : ");
  lcd.print(message);  
  delay(1000);
}

void updateSensor(){
  sensor = analogRead(analogPin);
  Serial.println(sensor);
}

void sendMsg(int motor, double motorVal){
  byte x = motor;
  byte y = motorVal;
  Wire.beginTransmission(8); 
  Wire.write(x); 
  Wire.write(y); 
  Wire.endTransmission();
}
