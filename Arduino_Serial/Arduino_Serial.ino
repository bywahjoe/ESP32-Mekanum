//DOCUMENTATION : https://github.com/bywahjoe/ESP32-Mekanum

#include <Servo.h>
#include "ardupin.h"

Servo myservo1;
Servo myservo2;
Servo myservo3;

String recv;
int setDefaultSpeed = 100;

void maju(int myspeed = setDefaultSpeed);
void mundur(int myspeed = setDefaultSpeed);
void kiri(int myspeed = setDefaultSpeed);
void kanan(int myspeed = setDefaultSpeed);
void muterKiri(int myspeed = setDefaultSpeed);
void muterKanan(int myspeed = setDefaultSpeed);
void motorKiriA(int myspeed = setDefaultSpeed);
void motorKiriB(int myspeed = setDefaultSpeed);
void motorKananA(int myspeed = setDefaultSpeed);
void motorKananB(int myspeed = setDefaultSpeed);
void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
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

  delay(10000);//WAIT ESP BOOTING
}
void loop() {
  
    if (Serial2.available()) {
      recv = char(Serial2.read());
      recv.trim();
      if (recv.length() > 0) {
  
        Serial.println(recv);
        if (recv == "w") maju();
        else if (recv == "a") kiri();
        else if (recv == "s") mundur();
        else if (recv == "d") kanan();
        else if (recv == "q") muterKiri();
        else if (recv == "e") muterKanan();
        else if (recv == "x") stops();
        else if (recv == "t") tarik();
        else if (recv == "l") lepas();
        else if (recv == "y") camKiri();
        else if (recv == "u") camTengah();
        else if (recv == "i") camKanan();
        else if (recv == "o") freeA();
        else if (recv == "p") freeB();
        else{}
        //Serial.println("OK");
      }
    }
//  maju();
//  delay(3000);
//  stops();
//  delay(3000);
//  mundur();
//  delay(3000);
//  stops();
//  delay(3000);
  //  kiri();
  //  delay(3000);
  //  stops();
  //  delay(3000);
  //  kanan();
  //  delay(3000);
  //  stops();
  //  delay(3000);
}
void setDefaultServo() {}
void freeA(){}
void freeB(){}
void tarik() {}
void lepas() {}
void camKiri(){}
void camTengah(){}
void camKanan(){}
void motorKiriA(int myspeed) {
  int varA = 0, varB = 0;

  digitalWrite(kiriA_ENA, HIGH);
  digitalWrite(kiriA_ENB, HIGH);

  if (myspeed == 0) {
    digitalWrite(kiriA_ENA, LOW);
    digitalWrite(kiriA_ENB, LOW);
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
  analogWrite(kiriA_RPWM, varA);
  analogWrite(kiriA_LPWM, varB);

}
void motorKiriB(int myspeed) {
  int varA = 0, varB = 0;

  digitalWrite(kiriB_ENA, HIGH);
  digitalWrite(kiriB_ENB, HIGH);

  if (myspeed == 0) {
    digitalWrite(kiriB_ENA, HIGH);
    digitalWrite(kiriB_ENB, HIGH);
  }
  else if (myspeed < 0) {
    varB = abs(myspeed)+40;
  }
  else {
    varA = myspeed+40;
  }
  analogWrite(kiriB_RPWM, varA);
  analogWrite(kiriB_LPWM, varB);
}
void motorKananA(int myspeed) {
  int varA = 0, varB = 0;

  digitalWrite(kananA_ENA, HIGH);
  digitalWrite(kananA_ENB, HIGH);

  if (myspeed == 0) {
    digitalWrite(kananA_ENA, LOW);
    digitalWrite(kananA_ENB, LOW);

  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }

  analogWrite(kananA_RPWM, varA);
  analogWrite(kananA_LPWM, varB);
}
void motorKananB(int myspeed) {
  int varA = 0, varB = 0;

  digitalWrite(kananB_ENA, HIGH);
  digitalWrite(kananB_ENB, HIGH);


  if (myspeed == 0) {
    digitalWrite(kananB_ENA, LOW);
    digitalWrite(kananB_ENB, LOW);
  }
  else if (myspeed < 0) {
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
  }
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
  int valRem = 50;
  digitalWrite(kiriA_ENA, HIGH);
  digitalWrite(kiriA_ENB, HIGH);
  analogWrite(kiriA_RPWM, valRem);
  analogWrite(kiriA_LPWM, valRem);

  digitalWrite(kiriB_ENA, HIGH);
  digitalWrite(kiriB_ENB, HIGH);
  analogWrite(kiriB_RPWM, valRem);
  analogWrite(kiriB_LPWM, valRem);

  digitalWrite(kananA_ENA, HIGH);
  digitalWrite(kananA_ENB, HIGH);
  analogWrite(kananA_RPWM, valRem);
  analogWrite(kananA_LPWM, valRem);

  digitalWrite(kananB_ENA, HIGH);
  digitalWrite(kananB_ENB, HIGH);
  analogWrite(kananB_RPWM, valRem);
  analogWrite(kananB_LPWM, valRem);
}

void maju(int myspeed) {
  setMotor(myspeed, myspeed, myspeed, myspeed);
}
void mundur(int myspeed) {
  setMotor(-myspeed, -myspeed, -myspeed, -myspeed);
}

void kiri(int myspeed) {
  setMotor(-myspeed, myspeed, myspeed, -myspeed);
}
void kanan(int myspeed) {
  setMotor(myspeed, -myspeed, -myspeed, myspeed);
}
void muterKiri(int myspeed) {
  setMotor(-myspeed, -myspeed, myspeed, myspeed);
}
void muterKanan(int myspeed) {
  setMotor(myspeed, myspeed, -myspeed, -myspeed);
}
