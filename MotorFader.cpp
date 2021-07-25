#include "MotorFader.h"

MotorFader::MotorFader(int motor_pin_a, int motor_pin_b, int enable_pin, int potentiometer_pin, int faderMin, int faderMax, int tolerance){
  this->motor_pin_a = motor_pin_a;
  this->motor_pin_b = motor_pin_b;
  this->enable_pin = enable_pin;
  this->potentiometer_pin = potentiometer_pin;
  this->faderMin = faderMin;
  this->faderMax = faderMax;
  this->tolerance = tolerance;
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

int MotorFader::GetPos(){
  return analogRead(potentiometer_pin);
}

int MotorFader::GetTarget(int target){
  return map(target, 0, 100, faderMin, faderMax);
}

void MotorFader::SetFaderSpeed(int val){
  analogWrite(enable_pin, faderSpeed[val]);
}

void MotorFader::ToPos(int target){
  int currentPos = GetPos();
  int targetPos = map(target, 0, 100, faderMin, faderMax);
  int targetMin = GetFaderMinTarget(targetPos);
  int targetMax = GetFaderMaxTarget(targetPos);
  if (target == 100){
    targetMin = faderMax;
    targetMax = faderMax + 2 * tolerance;
  }else if (target == 0){
    targetMin = faderMin - 2 * tolerance;
    targetMax = faderMin;
  }

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
    currentPos = GetPos();
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