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

}

void loop() {
  updateSensor();
  lcd.setCursor(0, 0);
  lcd.print("UP=motor_sel0-11");
  lcd.setCursor(0, 1);
  lcd.print("Motor: ");
  lcd.print(motor);

  if (sensor > 1000) {

  } else if (sensor > 700) {
    lcd.clear();
    lcd.print("select");
    delay(200);
    setMotor();
  } else if (sensor > 500) {
    lcd.clear();
    lcd.print("left");
    delay(200);
  } else if (sensor > 300) {
    lcd.clear();
    lcd.print("down");
    delay(200);
  } else if (sensor > 100) {
    lcd.clear();
    lcd.print("up");
    //delay(200);
    switchMotor();
  } else {
    lcd.clear();
    lcd.print("right");
    delay(200);
    Serial.println(sensor);
  }
}

void switchMotor() {
  if (motor < 11) {
    motor++;
  } else {
    motor = 0;
  }
  delay(200);
}

void setMotor() {
  updateSensor();

  while (sensor < 700 || sensor > 1000) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Motor ");
    lcd.print(motor);
    lcd.print(" pos -/+");

    if (sensor > 500 && sensor < 700) { //left
      decrementMotor();
    } else if (sensor > 300) { //down

    } else if (sensor > 100) { //up

    } else { //right
      incrementMotor();
    }
    lcd.setCursor(0, 1);
    lcd.print("Degrees ");
    lcd.print(motorVal);

    updateSensor();
    delay(140);
  }
  sendMsg();

}

void incrementMotor() {
  if (motorVal <= 180) {
    motorVal++;
  } else {
    error("Ex_lim+");
  }
  delay(10);
}

void decrementMotor() {
  if (motorVal >= 0) {
    motorVal--;
  } else {
    error("Ex_lim-");
  }
  delay(10);
}

void error(String message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Error : ");
  lcd.print(message);
  delay(1000);
}

void updateSensor() {
  sensor = analogRead(analogPin);
  Serial.println(sensor);
  delay(10);
}

void sendMsg() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Sending motor ");
  lcd.print(motor);
  lcd.setCursor(0, 1);
  lcd.print(" ");
  lcd.print(motorVal);
  lcd.print(" deg");
  byte x = motor;
  byte y = motorVal;
  Wire.beginTransmission(8);
  Wire.write(x);
  Wire.write(y);
  Wire.endTransmission();
  delay(1000);
  lcd.clear();
}
