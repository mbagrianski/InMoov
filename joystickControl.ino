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

int joy1X = 0;
int joy1Y = 1;
int joy2X = 0;
int joy2Y = 1;

int x1, x2, y1, y2;

void setup() {
  thumb.attach(9);
  index.attach(9);
  middle.attach(9);
  ring.attach(9);
  pinkie.attach(9);
  wrist.attach(9);

  neckUpDown.attach(9);
  neckRot.attach(9);
  bicep.attach(9);
  shoulderRot.attach(9);
  shoulderOut.attach(9);
  shoulderLift.attach(9);

}

void loop() {
  x1 = analogRead(joy1X);  //rest = 512, up = 1024, down = 0
  delay(100); //need small delay to avoid errors in measurement
  y1 = analogRead(joy1Y);
  delay(100);
  x2 = analogRead(joy2X);
  delay(100);
  y2 = analogRead(joy2Y);
  delay(100);

  if (moved(x1)) {
    moveShoulderLift(x1);
  } else {
    moveShoulderLift(512);
  }
  if (moved(y1)) {
    moveShoulderOut(y1);
  } else {
    moveShoulderOut(512);
  }
  if (moved(x2)) {
    moveBicep(x2);
  } else {
    moveBicep(512);
  }
  if (moved(y2)) {
    moveShoulderRot(y2);
  } else {
    moveShoulderRot(512);
  }
}

boolean moved(int val) {
  if (val > 514 || val < 510) {
    return true;
  } else {
    return false;
  }
}

void moveShoulderLift(int val) {
  if (val < 512) {
    a = (512 - val) / 10;
    shoulderLift.write(a);
  } else if (val > 512) {
    a = (val - 512) / 10;
    shoulderLift.write(a);
  } else {
    shoulderLift.write(shoulderLift0);
  }
}

void moveShoulderOut(int val) {
  if (val < 512) {
    b = (512 - val) / 10;
    shoulderOut.write(b);
  } else if (val > 512) {
    b = (val - 512) / 10;
    shoulderOut.write(b);
  } else {
    shoulderOut.write(shoulderOut0);
  }
}
void moveBicep(int val) {
  if (val < 512) {
    c = (512 - val) / 10;
    bicep.write(c);
  } else if (val > 512) {
    c = (val - 512) / 10;
    bicep.write(c);
  } else {
    bicep.write(bicep0);
  }
}
void moveShoulderRot(int val) {
  if (val < 512) {
    d = (512 - val) / 10;
    shoulderRot.write(d);
  } else if (val > 512) {
    d = (val - 512) / 10;
    shoulderRot.write(d);
  } else {
    shoulderRot.write(shoulderRot0);
  }
}
