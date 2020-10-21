#include <Servo.h>
#include <SoftwareSerial.h>
SoftwareSerial mySerial(0,1);
#define motorL1 2
#define motorL2 3
#define motorR1 4
#define motorR2 5

#define TRIG_PIN 6
#define ECHO_PIN 7
#define TIME_OUT 5000

float GetDistance()
{
  long duration, distanceCm;

  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration = pulseIn(ECHO_PIN, HIGH, TIME_OUT);

  // convert to distance
  distanceCm = duration / 29.1 / 2;
  if(distanceCm <= 1) distanceCm = 200;

  return distanceCm;
}

void motor1(int k) {
  if (k == 1) {
    digitalWrite(motorR1, HIGH);
    digitalWrite(motorR2, LOW);
  } else {
    digitalWrite(motorR2, HIGH);
    digitalWrite(motorR1, LOW);
  }
}
void motor2(int k) {
  if (k == 1) {
    digitalWrite(motorL2, HIGH);
    digitalWrite(motorL1, LOW);
  } else {
    digitalWrite(motorL1, HIGH);
    digitalWrite(motorL2  , LOW);
  }
}
void moveStop() {
  digitalWrite(motorR1, 0);
  digitalWrite(motorR2, 0);
  digitalWrite(motorL1, 0);
  digitalWrite(motorL2, 0);
}
Servo myservo;

int distance = 100;

int lookRight()
{
  myservo.write(50);
  delay(500);
  int distance = GetDistance();
  delay(100);
  myservo.write(115);
  return distance;
}

int lookLeft()
{
  myservo.write(170);
  delay(500);
  int distance = GetDistance();
  delay(100);
  myservo.write(115);
  return distance;
  delay(100);
}

void moveForward() {
  motor1(1);
  motor2(1);
  delay(5);
}

void moveBackward() {
  motor1(0);
  motor2(0);
  delay(5);
}

void turnRight() {
  motor1(1);
  motor2(0);
}

void turnLeft() {
  motor1(0);
  motor2(1);
}

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  myservo.attach(9);
  myservo.write(115);
  Serial.begin(115200);
  delay(2000);
  distance = GetDistance();
  delay(100);
  distance = GetDistance();
  delay(100);
  distance = GetDistance();
  delay(100);
  distance = GetDistance();
  delay(100);
}

int distanceR = 0;
int distanceL =  0;

void loop() {
  delay(20);

  if (GetDistance() <= 15)
  {
    Serial.println(GetDistance());
    mySerial.println(GetDistance());
    delay(1000);
    moveStop();
    delay(100);
    moveBackward();
    delay(200);
    moveStop();
    delay(200);
    distanceR = lookRight();
    distanceL = lookLeft();
    delay(200);

    if (distanceR >= distanceL)
    {
      turnRight();
      delay(100);
      moveStop();
    } else
    {
      turnLeft();
      delay(100);
      moveStop();
    }
  } else
  {
    moveForward();
    Serial.println(GetDistance());
  }
}
