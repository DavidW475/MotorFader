#ifndef MOTORFADER_H
#define MOTORFADER_H
#include <Arduino.h>

/**
 * Implementation of a motorfader for Arduino
 *
 * A class to controll a motorfader with a Arduino
 *
 */
class MotorFader {
  private:
    int motor_pin_a;
    int motor_pin_b;
    int enable_pin;
    int potentiometer_pin;
    int faderMin;
    int faderMax;
    int tolerance;
    int faderSpeed[3];
    int faderSpeedDist[2];
    void SetFaderSpeed(int val);
  public:
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
    MotorFader(int motor_pin_a, int motor_pin_b, int enable_pin, int potentiometer_pin, int faderMin, int faderMax, int tolerance, int faderSpeed1, int faderSpeed2, int faderSpeed3, int faderSpeedDist1, int faderSpeedDist2);

    /**
     * @return the minimum value of the potentiometer (faderMin)
    **/
    int GetFaderMin();

    /**
     * @return the maximum value of the potentiometer (faderMax)
    **/
    int GetFaderMax();

    /**
     * @return the tolerance the fader is trying to aim (tolerance)
    **/
    int GetFaderTolerance();

    /**
     * @param target the target of the potentiometer (must be between faderMin and faderMax)
     * @return the minimum potentiometer value of the target (target-tolerance)
    **/
    int GetFaderMinTarget(int target);
    
    /**
     * @param target the target of the potentiometer (must be between faderMin and faderMax)
     * @return the maximum potentiometer value of the target (target+tolerance)
    **/
    int GetFaderMaxTarget(int target);

    /**
     * @return the current potentiometer value
    **/
    int GetPotentiometerValue();

    /**
     * @return the current pos in percantage between faderMin and faderMax
    **/
    int GetPos();

    /**
     * @return the target in percantage
    **/
    int GetTarget(int target);

    /**
     * moves the fader to a target position
     * @param target the target the fader moves to (values between 0 and 100)
    **/
    void ToPos(int target);

    /**
     * fader moves up
    **/
    void MotorUp();

    /**
     * fader moves down
    **/
    void MotorDown();

    /**
     * fader stops
    **/
    void MotorStop();
};
#endif