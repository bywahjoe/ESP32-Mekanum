#include <Servo.h>
#include "ardupin.h"

#define read1 digitalRead(A1)
#define read2 digitalRead(A2)
#define read3 digitalRead(A3)
#define read4 digitalRead(A4)
#define read5 digitalRead(A5)

byte bitSensor;
//----------PID---------------//
int error = 0;
int lastError = 0;
byte kp = 22;
byte kd = 100;
byte SPEED = 100;
int MIN_SPEED = -90;
byte MAX_SPEED = 100;
//----------------------------//

Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
//SETTING SERVO

//DEFAULT
int interval = 2;
int interval2 = 5;
//motion servo   -- balik lepas
int mservo1 = 90,bservo1=90;   
int mservo2 = 90,bservo2=140;
int mservo3 = 89,bservo3=0;
int mservo4 = 140,bservo4=50;

int servo1 = 65;
int servo2 = 140;
int servo3 = 140;
int servo4 = 90;

int nowservo1 = servo1;
int nowservo2 = servo2;
int nowservo3 = servo3;
int nowservo4 = servo4;

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
int go=1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200);
  
  myservo1.attach(pin_servo1);
  myservo2.attach(pin_servo2);
  myservo3.attach(pin_servo3);
  myservo4.attach(pin_servo4);
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
  //motionServo();
  
  //myservo3.write(5);
  delay(10000);//WAIT ESP BOOTING
  
}

void loop() {

//if(go==1){
//  strategi();
//  go++;
//  }
  
    if (Serial2.available()) {
    recv = char(Serial2.read());
    recv.trim();
    if (recv.length() > 0) {

      // Serial.println(recv);
      if (recv == "w") maju();
      else if (recv == "a") kiri();
      else if (recv == "s") mundur();
      else if (recv == "d") kanan();
      else if (recv == "q") muterKiri();
      else if (recv == "e") muterKanan();
      else if (recv == "x") stops();
      else if (recv == "t") plusC();
      else if (recv == "y") minA();
      else if (recv == "u") plusA();
      else if (recv == "l") minC();
      else if (recv == "i") minB();
      else if (recv == "p") setDefaultServo();
      else if (recv == "o") plusB();
      else if (recv == "n") plusDir();
      else if (recv == "m") minDir();
      else if (recv == "b") {otomatis();recv="";/*go++;*/}
      else {recv="";}
      Serial2.end();
      Serial2.begin(115200);
      recv="";
      //Serial.println("OK");
    }
  recv="";
  }else{recv="";}

}

void strategi(){
    
    percabangan(1, 1000,1000);
    belok_kiri(150,100);
    percabangan(1, 1000,0);
    motionServo2();
    percabangan(1, 1000,0);
    motionServo();
//    
    belok_kiri(150,100);
    percabangan(1, 1000,0);
    percabangan(1, 1000,1000);
    belok_kanan(150,100);
    percabangan(1, 1000,0);

}
void otomatis(){
  strategi();  
  
}

void setDefaultServo() {
  myservo1.write(servo1);
  myservo2.write(servo2);
  myservo3.write(servo3);
  myservo4.write(servo4);

  nowservo1 = servo1;
  nowservo2 = servo2;
  nowservo3 = servo3;
  nowservo4 = servo4;
}
void motionServo2(){
  myservo1.write(servo1);
 
  myservo3.write(mservo3);
  myservo2.write(mservo2);
  myservo4.write(mservo4);
  delay(2000);
  }
void motionServo(){
  
//
////int mservo1 = 90,bservo1=90;   
////int mservo2 = 90,bservo2=140;
////int mservo3 = 80,bservo3=0;
////int mservo4 = 140,bservo4=50;
//
for(int i=mservo4;i>=bservo4;i-=5){
    myservo4.write(i);
    delay(200); 
}
 for(int i=mservo2;i<=bservo2;i+=5){
    myservo2.write(i);
    delay(200); 
}
 for(int i=mservo3;i>=bservo3;i-=5){
    myservo3.write(i);
    delay(200); 
}

    delay(2000);
    myservo4.write(servo4);
    delay(4000);

   
////int mservo2 = 90,bservo2=140;
////int mservo3 = 80,bservo3=0;
////int mservo4 = 140,bservo4=50;
//int servo1 = 90;
//int servo2 = 140;
//int servo3 = 140;
//int servo4 = 90;
 for(int i=bservo2;i>=servo2;i-=5){
    myservo2.write(i);
    delay(200); 
}
 for(int i=bservo3;i<=servo3;i+=2){
    myservo3.write(i);
    delay(200); 
}
myservo4.write(servo4);
myservo1.write(servo1);
    
}

void minC() {
  int val = nowservo4 - interval2;
  val = constrain(val, 0, 180);
  nowservo4 = val;
  myservo4.write(val);
}
void plusC() {
  int val = nowservo4 + interval2;
  val = constrain(val, 0, 180);
  nowservo4 = val;
  myservo4.write(val);
}
void minA() {
  int val = nowservo3 - interval;
  val = constrain(val, 0, 180);
  nowservo3 = val;
  myservo3.write(val);
}
void plusA() {
  int val = nowservo3 + interval;
  val = constrain(val, 0, 180);
  nowservo3 = val;
  myservo3.write(val);
}
void minB() {
  int val = nowservo2 - 2;
  val = constrain(val, 0, 180);
  nowservo2 = val;
  myservo2.write(val);
}
void plusB() {
  int val = nowservo2 + 2;
  val = constrain(val, 0, 180);
  nowservo2 = val;
  myservo2.write(val);
}
void minDir() {
  int val = nowservo1 - interval;
  val = constrain(val, 0, 172);
  nowservo1 = val;
  myservo1.write(val);
}
void plusDir() {
  int val = nowservo1 + interval;
  val = constrain(val, 0, 172);
  nowservo1 = val;
  myservo1.write(val);
}

void remDelay(int waktu) {
  int valRem = 50;
  digitalWrite(kiriA_ENA, LOW);
  digitalWrite(kiriA_ENB, LOW);
  analogWrite(kiriA_RPWM, valRem);
  analogWrite(kiriA_LPWM, valRem);

  digitalWrite(kiriB_ENA, LOW);
  digitalWrite(kiriB_ENB, LOW);
  analogWrite(kiriB_RPWM, valRem);
  analogWrite(kiriB_LPWM, valRem);

  digitalWrite(kananA_ENA, LOW);
  digitalWrite(kananA_ENB, LOW);
  analogWrite(kananA_RPWM, valRem);
  analogWrite(kananA_LPWM, valRem);

  digitalWrite(kananB_ENA, LOW);
  digitalWrite(kananB_ENB, LOW);
  analogWrite(kananB_RPWM, valRem);
  analogWrite(kananB_LPWM, valRem);
  delay(waktu);
}
int readSensor() {
  //Serial.println(sensor1);
  bitSensor = ((!read1 * 1) + (!read2 * 2) + (!read3 * 4) + (!read4 * 8)
               + (!read5 * 16));
  return bitSensor;

}
void followLine() {
  int sensor = readSensor();
  //  Serial.println(sensor);
  switch (sensor) {
    case 1: error = -4;  break;
    case 3: error = -3;  break;
    case 2: error = -2;  break;
    case 6: error = -1;  break;
    case 4: error = 0;  break; //tengah
    case 12: error = 1;  break;
    case 8: error = 2;  break;
    case 24: error = 3;  break;
    case 16: error = 4;  break;
  }

  int rateError = error - lastError;
  lastError = error;

  int moveVal = (int)(error * kp) + (rateError * kd);

  int moveLeft = SPEED + moveVal;
  int moveRight = SPEED - moveVal;


  moveLeft = constrain(moveLeft, MIN_SPEED, MAX_SPEED);
  moveRight = constrain(moveRight, MIN_SPEED, MAX_SPEED);
  //  Serial.print(moveLeft);
  //  Serial.print(",");
  //  Serial.println(moveRight);
  setMotor(moveLeft, moveLeft, moveRight, moveRight);
}

void percabangan(int xcount, int lama_henti,int delayMaju)
{
  int x = 0;
  while (x < xcount)
  {
    followLine();
    if (!read1 && !read2 && !read3 && !read4 && !read5)
    {
      x++;
    }
    while(!read1&&!read2&&!read3&&!read4&&!read5)
    {
    followLine();
//    maju(80);

    }
  }
   maju(80);
  delay(delayMaju);
  remDelay(lama_henti);
}
//--------------------------------------------------------------------//

//------------------------belok kiri-------------------------//
void belok_kiri(int kecbelok, int lama_henti) {

  while (!read2 || !read3 || !read4) {
    setMotor(-kecbelok, -kecbelok, kecbelok, kecbelok);
  }

  while (read2 && read3 && read4) {
    setMotor(-kecbelok, -kecbelok, kecbelok, kecbelok);
  }

  remDelay(lama_henti);
}

void belok_kanan(int kecbelok, int lama_henti) {

  while (!read2 || !read3 || !read4) {
    setMotor(kecbelok, kecbelok, -kecbelok, -kecbelok);
  }

  while (read2 && read3 && read4) {
    setMotor(kecbelok, kecbelok, -kecbelok, -kecbelok);
  }

  remDelay(lama_henti);
}
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
    varB = abs(myspeed) + 40;
  }
  else {
    varA = myspeed + 40;
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
  digitalWrite(kiriA_ENA, LOW);
  digitalWrite(kiriA_ENB, LOW);
  analogWrite(kiriA_RPWM, valRem);
  analogWrite(kiriA_LPWM, valRem);

  digitalWrite(kiriB_ENA, LOW);
  digitalWrite(kiriB_ENB, LOW);
  analogWrite(kiriB_RPWM, valRem);
  analogWrite(kiriB_LPWM, valRem);

  digitalWrite(kananA_ENA, LOW);
  digitalWrite(kananA_ENB, LOW);
  analogWrite(kananA_RPWM, valRem);
  analogWrite(kananA_LPWM, valRem);

  digitalWrite(kananB_ENA, LOW);
  digitalWrite(kananB_ENB, LOW);
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
