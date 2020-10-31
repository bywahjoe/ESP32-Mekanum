#include <Servo.h>
#include "ardupin.h"

Servo myservo1;
Servo myservo2;
Servo myservo3;

char recv;

void maju(int myspeed = 150);
void mundur(int myspeed = -150);

void setup() {
  Serial.begin(115200);
  //SERVO
  myservo1.attach(pin_servo1);
  myservo2.attach(pin_servo2);
  myservo3.attach(pin_servo3);
  setDefaultServo();
  //MOTOR
  pinMode(kiriA_ENA, OUTPUT);
  pinMode(kiriA_ENB, OUTPUT);
  pinMode(kiriA_RPWM, OUTPUT);
  pinMode(kiriA_LPWM, OUTPUT);

  pinMode(kiriB_ENA, OUTPUT);
  pinMode(kiriB_ENB, OUTPUT);
  pinMode(kiriB_RPWM, OUTPUT);
  pinMode(kiriB_LPWM, OUTPUT);

  pinMode(kananA_ENA, OUTPUT);
  pinMode(kananA_ENB, OUTPUT);
  pinMode(kananA_RPWM, OUTPUT);
  pinMode(kananA_LPWM, OUTPUT);

  pinMode(kananB_ENA, OUTPUT);
  pinMode(kananB_ENB, OUTPUT);
  pinMode(kananB_RPWM, OUTPUT);
  pinMode(kananB_LPWM, OUTPUT);
}
void loop() {
  if (Serial.available()) {

    recv = Serial.read();

    Serial.println(recv);
    if (recv == 'w') maju();
    else if (recv == 'a') kiri();
    else if (recv == 's') mundur();
    else if (recv == 'd') kanan();
    else if (recv == 't') tarik();
    else if (recv == 'l') lepas();

  } else {
    stops();
  }

}
void setDefaultServo() {}
void tarik() {}
void lepas() {}
void motorKiriA(int myspeed = 150) {
  int varA = 0, varB = 0;
  if (myspeed == 0) {
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
  digitalWrite(kiriA_ENA, HIGH);
  digitalWrite(kiriA_ENB, HIGH);
  analogWrite(kiriA_RPWM, varA);
  analogWrite(kiriA_LPWM, varB);

}
void motorKiriB(int myspeed = 150) {
  int varA = 0, varB = 0;
  if (myspeed == 0) {
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
  digitalWrite(kiriB_ENA, HIGH);
  digitalWrite(kiriB_ENB, HIGH);
  analogWrite(kiriB_RPWM, varA);
  analogWrite(kiriB_LPWM, varB);
}
void motorKananA(int myspeed = 150) {
  int varA = 0, varB = 0;
  if (myspeed == 0) {
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
  digitalWrite(kananA_ENA, HIGH);
  digitalWrite(kananA_ENB, HIGH);
  analogWrite(kananA_RPWM, varA);
  analogWrite(kananA_LPWM, varB);
}
void motorKananB(int myspeed = 150) {
  int varA = 0, varB = 0;
  if (myspeed == 0) {
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
  digitalWrite(kananB_ENA, HIGH);
  digitalWrite(kananB_ENB, HIGH);
  analogWrite(kananB_RPWM, varA);
  analogWrite(kananB_LPWM, varB);
}
void setMotor(int kiriA, int kiriB, int kananA, int kananB) {
  motorKiriA(kiriA);
  motorKiriB(kiriB);
  motorKananA(kananA);
  motorKananB(kananB);
}
void stops() {
  setMotor(0, 0, 0, 0);
}
void rem() {


}
void maju(int myspeed = 150) {
  setMotor(myspeed, myspeed, myspeed, myspeed);
}
void mundur(int myspeed = -150) {
  setMotor(myspeed, myspeed, myspeed, myspeed);
}
void kiri() {

}
void kanan() {

}
