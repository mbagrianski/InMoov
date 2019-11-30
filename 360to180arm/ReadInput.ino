//reads the input from raspberry pi 

int input = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available()){

    //converts the values of chars to integer
    input = input * (Serial.read() - '0');
    Serial.println(input);
  }
}
