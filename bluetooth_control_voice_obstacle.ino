#include <Servo.h>
#include "AFMotor_R4.h"

#define Echo A0
#define Trig A1
#define motor 10
#define Speed 170
#define spoint 103

char value;
int distance;
int Left;
int Right;
int L = 0;
int R = 0;

// Modes: 0 = Manual, 1 = Auto, 2 = Voice
int mode = 0;

Servo servo;
AF_DCMotor M1(1);
AF_DCMotor M2(2);
AF_DCMotor M3(3);
AF_DCMotor M4(4);

void setup() {
  Serial.begin(9600);
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  servo.attach(motor);
  servo.write(spoint);

  M1.setSpeed(Speed);
  M2.setSpeed(Speed);
  M3.setSpeed(Speed);
  M4.setSpeed(Speed);

  Serial.println("Starting in MANUAL BLUETOOTH MODE");
  Serial.println("Send '1' for Auto, '2'/'4' for Manual, '3' for Voice Mode");
}

void loop() {
  // Always listen for mode commands
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);

    if (value == '1') {
      mode = 1;
      Stop();
      Serial.println("Switched to AUTO (Obstacle Avoidance) Mode");
      delay(500);
    } 
    else if (value == '2' || value == '4') {
      mode = 0;
      Stop();
      Serial.println("Switched to MANUAL (Bluetooth Control) Mode");
      delay(500);
    } 
    else if (value == '3') {
      mode = 2;
      Stop();
      Serial.println("Switched to VOICE CONTROL Mode");
      delay(500);
    }
  }

  // Run behavior based on mode
  if (mode == 1) {
    Obstacle();  // Auto Mode
  } 
  else if (mode == 0) {
    Bluetoothcontrol();  // Manual Bluetooth Control
  } 
  else if (mode == 2) {
    voicecontrol();  // Voice Mode
  }
}

/* ----------------- MANUAL BLUETOOTH CONTROL ----------------- */
void Bluetoothcontrol() {
  if (value == 'U') forward();
  else if (value == 'D') backward();
  else if (value == 'L') left();
  else if (value == 'R') right();
  else if (value == 'S') Stop();
}

/* ----------------- OBSTACLE AVOIDANCE MODE ----------------- */
void Obstacle() {
  distance = ultrasonic();

  if (distance <= 12) {
    Stop();
    backward();
    delay(100);
    Stop();

    L = leftsee();
    servo.write(spoint);
    delay(800);
    R = rightsee();
    servo.write(spoint);

    if (L < R) {
      right();
      delay(500);
      Stop();
      delay(200);
    } else if (L > R) {
      left();
      delay(500);
      Stop();
      delay(200);
    }
  } else {
    forward();
  }
}

/* ----------------- VOICE CONTROL MODE ----------------- */
void voicecontrol() {
  if (Serial.available() > 0) {
    value = Serial.read();
    Serial.println(value);

    if (value == '^') {        // Forward command
      forward();
    } 
    else if (value == '-') {   // Backward
      backward();
    } 
    else if (value == '<') {   // Left
      L = leftsee();
      servo.write(spoint);
      if (L >= 10) {
        left();
        delay(500);
        Stop();
      } else {
        Stop();
      }
    } 
    else if (value == '>') {   // Right
      R = rightsee();
      servo.write(spoint);
      if (R >= 10) {
        right();
        delay(500);
        Stop();
      } else {
        Stop();
      }
    } 
    else if (value == '*') {   // Stop
      Stop();
    }
  }
}

/* ----------------- ULTRASONIC SENSOR ----------------- */
int ultrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(4);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);

  long t = pulseIn(Echo, HIGH);
  long cm = t / 29 / 2;
  return cm;
}

/* ----------------- MOTOR CONTROL FUNCTIONS ----------------- */
void forward() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void backward() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void right() {
  M1.run(BACKWARD);
  M2.run(BACKWARD);
  M3.run(FORWARD);
  M4.run(FORWARD);
}

void left() {
  M1.run(FORWARD);
  M2.run(FORWARD);
  M3.run(BACKWARD);
  M4.run(BACKWARD);
}

void Stop() {
  M1.run(RELEASE);
  M2.run(RELEASE);
  M3.run(RELEASE);
  M4.run(RELEASE);
}

/* ----------------- SERVO SCANNING FUNCTIONS ----------------- */
int rightsee() {
  servo.write(20);
  delay(800);
  Left = ultrasonic();
  return Left;
}

int leftsee() {
  servo.write(180);
  delay(800);
  Right = ultrasonic();
  return Right;
}
