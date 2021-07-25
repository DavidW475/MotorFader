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
     * @param motor_pin_a
     * @param motor_pinb
     * @param enable_pin
     * @param potentiometer_pin
     * @param faderMin
     * @param faderMax
     * @param tolerance
     * @param faderSpeed1
     * @param faderSpeed2
     * @param faderSpeed3
     * @param faderSpeedDist1
     * @param faderSpeedDist2
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
     * drives the fader to a given position
     * @param target the position the fader should drive to (values between 0 and 100)
    **/
    void ToPos(int target);

    /**
     * the fader drives up
    **/
    void MotorUp();

    /**
     * the fader drives down
    **/
    void MotorDown();

    /**
     * the fader stops
    **/
    void MotorStop();
};
#endif