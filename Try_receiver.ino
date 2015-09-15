
#include <IRremote.h>
#include <LedControlMS.h>
#include <Servo.h>  // servo library


int receiver = 13;
int servoPin = 8;
LedControl lc=LedControl(12,10,9,1);
Servo servo;  // servo control object

//shapes display
byte squareShape[8] = {B11111111,B10000001,B10000001,B10000001,B10000001,B10000001,B10000001,B11111111};
byte circleShape[8] = {B00111100,B01000010,B10000001,B10000001,B10000001,B10000001,B01000010,B00111100};
byte zigzagShape[8] = {B01111110,B00000010,B01111110,B01000000,B01111110,B00000010,B00011110,B00010000};
byte forwardShape[8] = {B00011000,B00001100,B00000110,B11111111,B11111111,B00000110,B00001100,B00011000};
byte backwardShape[8] = {B00011000,B00110000,B01100000,B11111111,B11111111,B01100000,B00110000,B00011000};
byte rightShape[8] = {B00011000,B00111100,B01111110,B11011011,B10011001,B00011000,B00011000,B00011000};
byte leftShape[8] = {B00011000,B00011000,B00011000,B10011001,B11011011,B01111110,B00111100,B00011000};
byte stopShape[8] = {B00111100,B01011010,B10011001,B10011001,B10011001,B10011001,B01011010,B00111100};

//IReceiver
IRrecv irrecv(receiver);           // create instance of 'irrecv'
decode_results results;            // create instance of 'decode_results'

//Motors
// motor one
int enA = 11;
int in1 = 2;
int in2 = 3;
// motor two
int enB = 6;
int in3 = 4;
int in4 = 5;
int speed = 255;
int defaultDuration = 300;

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Raw Data + Button Decode Test");
  irrecv.enableIRIn(); // Start the receiver

  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);

  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  servo.attach(servoPin);

  penUp();
}

//IReceiver
void translateIR() // takes action based on IR code received
// describing Car MP3 IR codes 
{

  switch(results.value)

  {
    
  case 0xFF629D:  
    Serial.println("FORWARD"); 
    forward(defaultDuration);
    displayForward();
    delay(300);
    sstop(1000);
    break;
    
  case 0xFFA857:  
    Serial.println("BACKWARDS"); 
    backward(defaultDuration);
    displayBackward();
    delay(300);
    sstop(1000);
    break;

  case 0xFFC23D:  
    Serial.println("RIGHT"); 
    right(defaultDuration);
    displayRight();
    delay(120);
    sstop(1000);
    break;
    
  case 0xFF22DD:  
    Serial.println("LEFT"); 
    left(defaultDuration);
    displayLeft();
    delay(120);
    sstop(1000);
    break;

  case 0xFF02FD:  
    Serial.println("STOP"); 
    displayStop();
    sstop(1000);
    break;

  case 0xFF906F:  
    Serial.println("UP"); 
    penUp();
    break;
    
  case 0xFFE01F:  
    Serial.println("DOWN"); 
    penDown();
    break;   
    
  case 0xFFA25D:  
    Serial.println(" CH-            "); 
    break;
     
  case 0xFFE21D:  
    Serial.println(" CH+            "); 
    break;

  case 0xFF6897:  
    Serial.println(" 0              "); 
    break;

  case 0xFF9867:  
    Serial.println(" 100+           "); 
    break;

  case 0xFFB04F:  
    Serial.println(" 200+           "); 
    break;

  case 0xFF30CF:  
    Serial.println("1"); 
    displaySquare();
    drawSquare();
    sstop(1000);
    break;

  case 0xFF18E7:  
    Serial.println("2"); 
    displayCircle();
    drawCircle();
    sstop(1000);
    break;

  case 0xFF7A85:  
    Serial.println("3"); 
    displayZigzag();
    drawZigzag();
    sstop(1000);
    break;

  case 0xFF10EF:  
    Serial.println("4"); 
    displayCircle();
    drawBackwardCircle();
    sstop(1000);
    break;

  case 0xFF38C7:  
    Serial.println(" 5              "); 
    break;

  case 0xFF5AA5:  
    Serial.println(" 6              "); 
    break;

  case 0xFF42BD:  
    Serial.println(" 7              "); 
    break;

  case 0xFF4AB5:  
    Serial.println(" 8              "); 
    break;

  case 0xFF52AD:  
    Serial.println(" 9              "); 
    break;

  default: 
    Serial.println(" other button   ");

  }

  delay(500);
}

//Movement
void set_speed(int pin, int speed)
{
  //if(pin == enA)
  //  analogWrite(pin, 200);
  //else
    digitalWrite(pin, HIGH);
}

void forward(int duration)
{
  Serial.println("Forward");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  set_speed(enA, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  set_speed(enB, speed);
  delay(duration);
}

void backward(int duration)
{
  Serial.println("Backward");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  set_speed(enA, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  set_speed(enB, speed);
  delay(duration);
}

void right(int duration)
{
  Serial.println("Right");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  set_speed(enA, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  set_speed(enB, speed);
  delay(duration);
}

void left(int duration)
{
  Serial.println("Left");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  set_speed(enA, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  set_speed(enB, speed);
  delay(duration);
}

void sstop(int duration)
{
  // now turn off motors
  Serial.println("Off");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);  
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  
  delay(duration);
}

void drawSquare()
{
  Serial.println("drawSquare start");
  penDown();
  // malben - starts from the lower left corner
  forward(1100);
  right(270);  
  forward(800);
  right(270);
  forward(1100);
  right(270);
  forward(800);
  right(270); 
  penUp(); 
}

void drawCircle()
{
  Serial.println("drawCircle start");
  penDown();
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);  
  set_speed(enA, speed);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW); 
  set_speed(enB, speed);
  delay(1500);
  penUp(); 
}

void drawBackwardCircle()
{
  Serial.println("drawBackwardCircle start");
  penDown();
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  
  set_speed(enA, speed);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH); 
  set_speed(enB, speed);
  delay(1500);
  penUp(); 
}

void drawZigzag()
{
  Serial.println("drawZigzag start");
  penDown();
  // forward zigzag
  right(100);
  forward(300);
  left(200);
  forward(300);
  right(200);
  forward(300);
  left(200);
  forward(300);
  right(100);
  penUp(); 
}

//LED shapes
void displaySquare(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,squareShape[i]);
  }
}

void displayCircle(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,circleShape[i]);
  }
}

void displayZigzag(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,zigzagShape[i]);
  }
}

void displayForward(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,forwardShape[i]);
  }
}

void displayBackward(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,backwardShape[i]);
  }
}

void displayRight(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,rightShape[i]);
  }
}

void displayLeft(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,leftShape[i]);
  }
}

void displayStop(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,stopShape[i]);
  }
}

//Servo
void penDown()
{
  servo.write(90);
  Serial.println("Pen Down");
}

void penUp()
{
  servo.write(180);
  Serial.println("Pen Up");
}


void loop() {
  
  if (irrecv.decode(&results)) {
    translateIR(); 
    irrecv.resume();
  }

  //sstop(1000);

}
