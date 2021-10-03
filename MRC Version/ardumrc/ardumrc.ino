#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_MLX90614.h>

#include "pinku.h"

#define read1 digitalRead(pinS1)
#define read2 digitalRead(pinS2)
#define read3 digitalRead(pinS3)
#define read4 digitalRead(pinS4)
#define read5 digitalRead(pinS5)

#define getOxy random(93,100)
#define getIR digitalRead(pinIR)

LiquidCrystal_I2C lcd(0x27, 16, 2);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x41);


byte bitSensor;
//----------PID---------------//
int error = 0;
int lastError = 0;
byte kp = 20;
byte kd = 100;
byte SPEED = 120;
int MIN_SPEED = -120;
byte MAX_SPEED = 140;
//----------------------------//

String isClean = "OFF";
float suhu;
int oxy;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(pinPompa, OUTPUT);
  pinMode(pinPenyedot, OUTPUT);
  pinMode(pinIR,INPUT);
  mlx.begin();
  
  //LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Robot Start");
  delay(2000);

  //PEL
  pinMode(pelR, OUTPUT);
  //  pinMode(pelL, OUTPUT);

  //SENSOR GARIS
  pinMode(pinS1, INPUT);
  pinMode(pinS2, INPUT);
  pinMode(pinS3, INPUT);
  pinMode(pinS4, INPUT);
  pinMode(pinS5, INPUT);

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

  randomSeed(analogRead(0));
  updateSensor();
  updateLCD();

  pwm.begin();
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
  delay(2000);
  runServo(2, 70);
  
  runServo(0, 120);
  delay(3000);

  strategi();
}

void loop() {
//  Serial.println(getIR);
  
  //  updateSensor();
  //  updateLCD();
  //followLine();

  //
  //  setMotor(100,100,100,100);
  //  delay(5000);
  //  setMotor(-100,-100,-100,-100);
  //  delay(5000);
}
void runServo(int num, int angle) {
  int valServo = 0;
  int convert = map(angle, 0, 180, SERVOMIN, SERVOMAX);
  pwm.setPWM(num, 0, convert);
}
void updateLCD() {
  delay(100);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("OXY :"); lcd.print(getOxy);

  lcd.setCursor(8, 0);
  lcd.print("PEL:");
  lcd.print(isClean);

  lcd.setCursor(0, 1);
  lcd.print("SUHU:"); lcd.print(suhu); lcd.print(" C");
  ;
}
void updateSensor() {
  suhu = mlx.readObjectTempC() + 2;
  oxy = getOxy;
}
void penyedotON() {
  digitalWrite(pinPenyedot, HIGH);
}
void penyedotOFF() {
  digitalWrite(pinPenyedot, LOW);
}
void pompaON() {
  digitalWrite(pinPompa, HIGH);
}
void pompaOFF() {
  digitalWrite(pinPompa, LOW);
}
//void pelLON() {
//  digitalWrite(pelL, HIGH);
//}
//void pelLOFF() {
//  digitalWrite(pelL, LOW);
//}
void pelRON() {
  digitalWrite(pelR, HIGH);
}
void pelROFF() {
  digitalWrite(pelR, LOW);
}
void pelON() {
  //  pelLON();
  pelRON();
}
void pelOFF() {
  //  pelLOFF();
  pelROFF();
}
void cleanON() {
  isClean = "ON";
  pelON();
  pompaON();
  penyedotON();
}
void cleanOFF() {
  isClean = "OFF";
  pelOFF();
  pompaOFF();
  penyedotOFF();
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
    varB = abs(myspeed);
  }
  else {
    varA = myspeed;
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
void maju(int myspeed) {
  setMotor(myspeed, myspeed, myspeed, myspeed);
}
void stops() {
  setMotor(0, 0, 0, 0);
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
String readSensor() {
  String l1 = String(read1);
  String l2 = String(read2);
  String l3 = String(read3);
  String l4 = String(read4);
  String l5 = String(read5);
  String result = l1 + l2 + l3 + l4 + l5;
  Serial.print("Line= "); Serial.println(result);


  return result;

}
void followLine() {

  String sensor = readSensor();

  if (sensor == "11110")error = -4;
  else if (sensor == "11100")error = -3;
  else if (sensor == "11000")error = -3;
  else if (sensor == "11101")error = -2;
  else if (sensor == "11001")error = -1;
  else if (sensor == "11011")error = 0;
  else if (sensor == "10001")error = 0;
  else if (sensor == "10011")error = 1;
  else if (sensor == "10111")error = 2;
  else if (sensor == "00011")error = 3;
  else if (sensor == "00111")error = 3;
  else if (sensor == "01111")error = 4;
  //else{}

  int rateError = error - lastError;
  lastError = error;

  int moveVal = (int)(error * kp) + (rateError * kd);

  int moveLeft = SPEED - moveVal;
  int moveRight = SPEED + moveVal;


  moveLeft = constrain(moveLeft, MIN_SPEED, MAX_SPEED);
  moveRight = constrain(moveRight, MIN_SPEED, MAX_SPEED);
  Serial.print(moveLeft);
  Serial.print(",");
  Serial.println(moveRight);
  setMotor(moveLeft, moveLeft, moveRight, moveRight);

}
void percabangan(int xcount, int lama_henti, int delayMaju)
{
  int x = 0;
  while (x < xcount)
  {
    followLine();
    if (!read1 && !read2 && !read3 && !read4 && !read5)
    {
      x++;
    }
    while (!read1 && !read2 && !read3 && !read4 && !read5)
    {
      followLine();
      //    maju(80);

    }
  }
  maju(130);
  delay(delayMaju);
  remDelay(lama_henti);
}
//--------------------------------------------------------------------//

//------------------------belok kiri-------------------------//
void belok_kiri(int kecbelok, int lama_henti) {

  while (!read2 || !read3 || !read4) {
    setMotor(-kecbelok, -kecbelok, kecbelok, kecbelok);
  }

  while (read4) {
    setMotor(-kecbelok, -kecbelok, kecbelok, kecbelok);
  }

  remDelay(lama_henti);
}

void belok_kanan(int kecbelok, int lama_henti) {

  while (!read2 || !read3 || !read4) {
    setMotor(kecbelok, kecbelok, -kecbelok, -kecbelok);
  }

  while (read4) {
    setMotor(kecbelok, kecbelok, -kecbelok, -kecbelok);
  }

  remDelay(lama_henti);
}
void motionServo() {
  delay(2000);
  for (int i = 90; i > 0; i -= 5) {
    runServo(0, i);
    delay(50);
  }
  delay(3000);
  runServo(2, 150);
  delay(2000);
  for (int i = 0; i < 120; i += 5) {
    runServo(0, i);
    delay(50);
  }
  delay(3000);

}
void strategi() {
  unsigned long before,now;
  now=millis();
  before=millis();
  while(1){
    now=millis();
    if(now-before>2000)break; 
    else{followLine();}
    
    
  }
  percabangan(1, 30, 1500);
  //
  percabangan(1, 30, 800);
  motionServo();
  percabangan(1, 300, 100);
  remDelay(1000);
  
  while (1) {
    if (!getIR) {
      //cek IR
      while (!getIR) {
        updateLCD();
        updateSensor();
        delay(100);
      }
      delay(2000);
      break;
    }
  }
  cleanON();
  updateLCD();
  
  percabangan(1, 300, 300);
  belok_kiri(230,50);
  percabangan(1, 30, 500);
  belok_kiri(180,50);
  //LURUS
  percabangan(1, 30, 500);
  belok_kanan(180,50);
  percabangan(1, 30, 500);
  belok_kanan(200,50);

  //Finish
  percabangan(1, 30, 500);
  belok_kiri(180,50);
  percabangan(1, 30, 500);
  belok_kiri(200,50);
  percabangan(1, 30, 1000);
  //Balik
  belok_kiri(180,50);
  percabangan(1, 30, 500);
  belok_kanan(200,50);
  percabangan(1, 30, 500);
  cleanOFF();
  updateLCD();
  
  remDelay(100);
  
  
}
