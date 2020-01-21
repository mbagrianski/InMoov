#include <Wire.h>
#include <Servo.h>

Servo thumb;
Servo index;
Servo middle;
Servo ring;
Servo pinkie;
Servo wrist;

Servo neckUpDown;
Servo neckRot;
Servo bicep;//360 deg servo
Servo shoulderRot;//360 deg servo
Servo shoulderOut;//360 deg servo
Servo shoulderLift;//360 deg servo

int bicep0 = 94;
int shoulderRot0 = 96;
int shoulderOut0 = 114;//up = 118
int shoulderLift0 = 89;

int a, b, c, d;
int gripCount = 0;

int joy1X = A0;
int joy1Y = A1;
int joy2X = A2;
int joy2Y = A3;

int button = A5;

int x1, x2, y1, y2;

void setup() {
  Serial.begin(9600);
  thumb.attach(9);
  index.attach(8);
  middle.attach(13);
  ring.attach(12);
  pinkie.attach(3);
  wrist.attach(10);

  //neckUpDown.attach(9);
  //neckRot.attach(9);
  bicep.attach(5);
  shoulderRot.attach(7); //94
  shoulderOut.attach(6);
  shoulderLift.attach(4);

  thumb.write(0);
  index.write(0);
  middle.write(0);
  ring.write(0);
  pinkie.write(0);
  wrist.write(90);

  //neckUpDown.attach(9);
  //neckRot.attach(9);
  bicep.write(bicep0);
  shoulderRot.write(shoulderRot0);
  shoulderOut.write(shoulderOut0);
  shoulderLift.write(shoulderLift0);

  pinMode(button, INPUT);

}

void loop() {
  x1 = analogRead(joy1X);  //rest = 512, up = 1024, down = 0
  delay(10); //need small delay to avoid errors in measurement
  y1 = analogRead(joy1Y);
  delay(10);
  x2 = analogRead(joy2X);
  delay(10);
  y2 = analogRead(joy2Y);
  delay(10);
  


  if (moved(y1)) {
    moveShoulderLift(y1);
  } else {
    moveShoulderLift(512);
  }
  if (moved(x1)) {
    moveShoulderOut(x1);
  } else {
    moveShoulderOut(512);
  }
  if (moved(y2)) {
    moveBicep(y2);
  } else {
    moveBicep(512);
  }
  if (moved(x2)) {
    moveShoulderRot(x2);
  } else {
    moveShoulderRot(512);
  }

  if (digitalRead(button) == LOW) {
    gripUnGrip();
  }
    Serial.println(digitalRead(button));



}
boolean moved(int val) {
  if (val > 520 || val < 500) {
    return true;
  } else {
    return false;
  }
}

void moveShoulderLift(int val) {
  if (val < 512) {
    a = (512 - val) / 10;
    shoulderLift.write(shoulderLift0 + a);
  } else if (val > 512) {
    a = (val - 512) / 10;
    shoulderLift.write(shoulderLift0 - a);
  } else {
    shoulderLift.write(shoulderLift0);
  }
}

void moveShoulderOut(int val) {
  if (val < 512) {
    b = (512 - val) / 10;
    shoulderOut.write(shoulderOut0 - b);
  } else if (val > 512) {
    b = (val - 512) / 10;
    shoulderOut.write(shoulderOut0 + b);
  } else {
    shoulderOut.write(shoulderOut0);
  }
}
void moveBicep(int val) {
  if (val < 512) {
    c = (512 - val) / 10;
    bicep.write(bicep0 + c);
  } else if (val > 512) {
    c = (val - 512) / 10;
    bicep.write(bicep0 - c);
  } else {
    bicep.write(bicep0);
  }
}
void moveShoulderRot(int val) {
  if (val < 512) {
    d = (512 - val) / 10;
    shoulderRot.write(shoulderRot0 - d);
  } else if (val > 512) {
    d = (val - 512) / 10;
    shoulderRot.write(shoulderRot0 + d);
  } else {
    shoulderRot.write(shoulderRot0);
  }
}

void gripUnGrip() {
  if (gripCount % 2 == 0) {
    thumb.write(0);
    index.write(0);
    middle.write(0);
    ring.write(0);
    pinkie.write(0);
    wrist.write(90);
  } else {
    thumb.write(90);
    index.write(120);
    middle.write(180);
    ring.write(140);
    pinkie.write(90);
    wrist.write(90);
  }
  delay(300);
  gripCount++;
}
