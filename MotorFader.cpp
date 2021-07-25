#include "MotorFader.h"

/**
 * @param motor_pin_a first motor pin on the Arduino
 * @param motor_pinb second pin on the Arduino
 * @param enable_pin enable pin on the Arduino
 * @param potentiometer_pin potentiometer_pin on the Arduino
 * @param faderMin the minimum value of the potentiometer
 * @param faderMax the maximum value of the potentiometer
 * @param tolerance the tolerance of the target point (potentiometer value)
 * @param faderSpeed1 fastest fader speed (between 0 and 255)
 * @param faderSpeed2 medium fader speed (between 0 and 255)
 * @param faderSpeed3 low fader speed (between 0 and 255)
 * @param faderSpeedDist1 the potentiometer distance to the target where the fader switches between faderSpeed1 and faderSpeed2
 * @param faderSpeedDist2 the potentiometer distance to the target where the fader switches between faderSpeed2 and faderSpeed3
**/

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

/**
 * @return the minimum value of the potentiometer (faderMin)
**/
int MotorFader::GetFaderMin(){
  return faderMin;
}

/**
 * @return the maximum value of the potentiometer (faderMax)
**/
int MotorFader::GetFaderMax(){
  return faderMax;
}

/**
 * @return the tolerance the fader is trying to aim (tolerance)
**/
int MotorFader::GetFaderTolerance(){
  return tolerance;
}

/**
 * @param target the target of the potentiometer (must be between faderMin and faderMax)
 * @return the minimum potentiometer value of the target (target-tolerance)
**/
int MotorFader::GetFaderMinTarget(int target){
  if (target < faderMin) return faderMin;
  if (target > faderMax) return faderMax;
  return target - tolerance;
}

/**
 * @param target the target of the potentiometer (must be between faderMin and faderMax)
 * @return the maximum potentiometer value of the target (target+tolerance)
**/
int MotorFader::GetFaderMaxTarget(int target){
  if (target < faderMin) return faderMin;
  if (target > faderMax) return faderMax;
  return target + tolerance;
}

/**
 * @return the current potentiometer value
**/
int MotorFader::GetPotentiometerValue(){
  return analogRead(potentiometer_pin);
}

/**
 * @return the current pos in percantage between faderMin and faderMax
**/
int MotorFader::GetPos(){
  int pos = map(analogRead(potentiometer_pin), faderMin, faderMax, 0, 100);
  if (pos > 100) return 100;
  if (pos < 0) return 0;
  return pos;
}

/**
 * @return the target in percantage
**/
int MotorFader::GetTarget(int target){
  return map(target, 0, 100, faderMin, faderMax);
}

/**
 * @param val the new fader speed (between 255 and 0)
**/
void MotorFader::SetFaderSpeed(int val){
  analogWrite(enable_pin, faderSpeed[val]);
}

/**
 * moves the fader to a target position
 * @param target the target the fader moves to (values between 0 and 100)
**/
void MotorFader::ToPos(int target){
  if (target > 100 || target < 0) return;
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

/**
 * fader moves up
**/
void MotorFader::MotorUp(){
  digitalWrite(motor_pin_a, HIGH);
  digitalWrite(motor_pin_b, LOW);
}

/**
 * fader moves down
**/
void MotorFader::MotorDown(){
  digitalWrite(motor_pin_a, LOW);
  digitalWrite(motor_pin_b, HIGH);
}

/**
 * fader stops
**/
void MotorFader::MotorStop(){
  digitalWrite(motor_pin_a, LOW);
  digitalWrite(motor_pin_b, LOW);
  analogWrite(enable_pin, 0);
}