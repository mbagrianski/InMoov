#include <Wire.h>
#include <Servo.h>

Servo thumb;//initialize servos being used
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

//Our 360 degree servos were modified by us, so each has a slightly different no-movement angle. 
//We use these variables to simplify the code structure.

int bicep0 = 94; 
int shoulderRot0 = 96;
int shoulderOut0 = 114;//up = 118
int shoulderLift0 = 89;

//These are variables that we'll use to convert the joystick potentiometer reading to 
//a value that we add onto the servo zero val. This increases the speed in one direction or another.

int a, b, c, d; 

int joy1X = A0; //configure which pins belong to which potentiometer
int joy1Y = A1;
int joy2X = A2;
int joy2Y = A3;

int x1, x2, y1, y2; //These are variables that store raw potentiometer readings.

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
  shoulderRot.attach(7);
  shoulderOut.attach(6);
  shoulderLift.attach(4);

  thumb.write(0);
  index.write(0);
  middle.write(0);
  ring.write(0);
  pinkie.write(0);
  wrist.write(90); //the servo motors tend to move a little each time we reset, so this keeps them from
  //moving too far and breaking a joint.

}

void loop() { //main code
  x1 = analogRead(joy1X);  //rest = 512, up = 1024, down = 0. Assign a reading to a variable
  y1 = analogRead(joy1Y);
  x2 = analogRead(joy2X);
  y2 = analogRead(joy2Y);

  if (moved(x1)) { //if joystick has been moved, move the corresponding motor by the value of that joystick.
    moveShoulderLift(x1);
  } else {
    moveShoulderLift(512); //otherwise 'move' the motor by the neutral value, which keeps it from turning.
  }
  if (moved(y1)) { //etc. Cycle through all potentiometers.
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
  delay(10); //delay to avoid errors in measurement.
}

boolean moved(int val) { //checks if potentiometer has moved. Although in theory it should return
  //512 at neutral position, the real-life potentiometer may have deviations, therefore we use this to account for that.
  if (val > 520 || val < 500) {
    return true;
  } else {
    return false;
  }
}

void moveShoulderLift(int val) { //methods that are unique to each motor
  if (val < 512) {//if moved one way
    a = (512 - val) / 10; //convert the pot reading to something the servo can accelerate by. You can adjust 
    //the /10 if you wish to experiment.
    shoulderLift.write(shoulderLift0 + a);//tell servo to go to neutral position + the reading from the joystick.
  } else if (val > 512) {//if moved the other way
    a = (val - 512) / 10;
    shoulderLift.write(shoulderLift0 - a);
  } else {
    shoulderLift.write(shoulderLift0);//otherwise stop the motor
  }
}

void moveShoulderOut(int val) {//etc.
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
