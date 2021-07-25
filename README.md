# MotorFader
## Installation
Clone the Repository to your Arduino Library Folder(default Windows: C:\Users\\\<User>\Documents\Arduino\libraries)
```
git clone https://github.com/DavidW475/MotorFader.git
```
## Usage
### Variables
* motor_pin_a first motor pin on the Arduino
* motor_pinb second pin on the Arduino
* enable_pin enable pin on the Arduino
* potentiometer_pin potentiometer_pin on the Arduino
* faderMin the minimum value of the potentiometer
* faderMax the maximum value of the potentiometer
* tolerance the tolerance of the target point (potentiometer value)
* faderSpeed1 fastest fader speed (between 0 and 255)
* faderSpeed2 medium fader speed (between 0 and 255)
* faderSpeed3 low fader speed (between 0 and 255)
* faderSpeedDist1 the potentiometer distance to the target where the fader switches between faderSpeed1 and faderSpeed2
* faderSpeedDist2 the potentiometer distance to the target where the fader switches between faderSpeed2 and faderSpeed3