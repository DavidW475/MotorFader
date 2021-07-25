#include "MotorFader.h"

MotorFader::MotorFader(int motor_pin_a, int motor_pin_b, int enable_pin, int potentiometer_pin, int faderMin, int faderMax, int tolerance, int faderSpeed1, int faderSpeed2, int faderSpeed3, int faderSpeedDist1, int faderSpeedDist2){
  this->motor_pin_a = motor_pin_a;
  this->motor_pin_b = motor_pin_b;
  this->enable_pin = enable_pin;
  this->potentiometer_pin = potentiometer_pin;
  this->faderMin = faderMin;
  this->faderMax = faderMax;
  this->tolerance = tolerance;
  this->faderSpeed[0] = faderSpeed1;
  this->faderSpeed[1] = faderSpeed2;
  this->faderSpeed[2] = faderSpeed3;
  this->faderSpeedDist[0] = faderSpeed1;
  this->faderSpeedDist[1] = faderSpeed2;
}

int MotorFader::GetFaderMin(){
  return faderMin;
}

int MotorFader::GetFaderMax(){
  return faderMax;
}

int MotorFader::GetFaderTolerance(){
  return tolerance;
}

int MotorFader::GetFaderMinTarget(int target){
  return target - tolerance;
}

int MotorFader::GetFaderMaxTarget(int target){
  return target + tolerance;
}

int MotorFader::GetPotentiometerValue(){
  return analogRead(potentiometer_pin);
}

int MotorFader::GetPos(){
  int pos = map(analogRead(potentiometer_pin), faderMin, faderMax, 0, 100);
  if (pos > 100) return 100;
  if (pos < 0) return 0;
  return pos;
}

int MotorFader::GetTarget(int target){
  return map(target, 0, 100, faderMin, faderMax);
}

void MotorFader::SetFaderSpeed(int val){
  analogWrite(enable_pin, faderSpeed[val]);
}

void MotorFader::ToPos(int target){
  int currentPos = GetPotentiometerValue();
  int targetPos = map(target, 0, 100, faderMin, faderMax);
  int targetMin = GetFaderMinTarget(targetPos);
  int targetMax = GetFaderMaxTarget(targetPos);

  SetFaderSpeed(2);
  int i = 0;

  while ((currentPos < targetMin || currentPos > targetMax) || i < 100){
    if (currentPos < targetMin){
      if (targetMin - currentPos > faderSpeedDist[0]){
        SetFaderSpeed(0);
      }else if (targetMin - currentPos > faderSpeedDist[1]){
        SetFaderSpeed(1);
      }else{
        SetFaderSpeed(2);
      }
      MotorUp();
      i=0;
    } else if (currentPos > targetMax){
      if (currentPos - targetMax > faderSpeedDist[0]){
        SetFaderSpeed(0);
      }else if (currentPos - targetMax > faderSpeedDist[1]){
        SetFaderSpeed(1);
      }else{
        SetFaderSpeed(2);
      }
      MotorDown();
      i=0;
    }else{
      i++;
    }
    currentPos = GetPotentiometerValue();
  }
  MotorStop();
}

void MotorFader::MotorUp(){
  digitalWrite(motor_pin_a, HIGH);
  digitalWrite(motor_pin_b, LOW);
}

void MotorFader::MotorDown(){
  digitalWrite(motor_pin_a, LOW);
  digitalWrite(motor_pin_b, HIGH);
}

void MotorFader::MotorStop(){
  digitalWrite(motor_pin_a, LOW);
  digitalWrite(motor_pin_b, LOW);
  analogWrite(enable_pin, 0);
}