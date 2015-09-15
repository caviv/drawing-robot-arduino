// connect motor controller pins to Arduino digital pins
// motor one
int enA = 11;
int in1 = 2;
int in2 = 3;
// motor two
int enB = 6;
int in3 = 4;
int in4 = 5;
// servo pen
int servoPin = 13;
int speed = 255;


//Include for servo
#include <Servo.h>  // servo library
//Define Servo
Servo servo;  // servo control object

void set_speed(int pin, int speed)
{
  //if(pin == enA)
  //  analogWrite(pin, 200);
  //else
    digitalWrite(pin, HIGH);
}


void setup()
{
  Serial.begin (9600);

  servo.attach(servoPin);
  
  // set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
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
  Serial.println("Right");
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

  // malben - starts from the lower left corner
  forward(1100);
  right(270);  
  forward(800);
  right(270);
  forward(1100);
  right(270);
  forward(800);
  right(270);  
}
void drawZigzag()
{
  Serial.println("drawZigzag start");

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
}

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

void loop()
{
  penUp();
  delay(7000);
  
  penDown();
  drawSquare();

  penUp();
  sstop(1000);
  right(200);
  forward(300);
  left(200);

  //sstop(1000);

  penDown();
  drawZigzag();

  sstop(1000);
}
