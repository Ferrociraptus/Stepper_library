#ifndef STEPPER_H
#define STEPPER_H

#include <Arduino.h>

class Stepper{
public:
  //Constructor:
  Stepper(byte stpPin, byte dirPin);
  Stepper(byte stpPin, byte dirPin, byte enaPin);
  //End of Constructor;


  //Set settings:

  //Settings of rotation for stepper motor:
  void setmmPerTurn(float mmPerTurn);
  void setAcceleration(int acceleration);
  void setStepDivision(byte division);
  void setAnglePerStep(float angle);
  void setStartSpeed(float speed);
  void setMaxSpeed(float speed);
  //End of settings of rotation for stepper motor;

  //Settings of operation mode:
  void setMotorMode(String Mode, String enaLvl = "LOW");
  void reverse();
  void setImpulseTime(byte impulseTime);
  //End of Settings of operation mode;

  //Settings of position set:
  void setPosition(float position);
  void setEndBorder(float endBorderPosition);
  void setBeginBorder(float beginBorderPosition);
  //End settings of position set;

  //End of set-settings;


  //Metods for work with stepper motor:

  //Position metods:
  void  position(float Position);
  float changePosition(float changePos);
  //End of position metods;

  //Information metods:
  String showPosition(boolean ifshowPos = true, boolean ifshowBorders = true);
  String showInformation(String nameOfStepperController, boolean ifshowAnglePerStep = true, boolean ifshowDivision = true);
  //End of information metods;

  //End of metods for work with stepper motor;

private:
  float anglePerStep = 1.8;
  float stepsPerMM = 0.0;
  float acceleration = 100.0; //mm/s^2
  float maxSpeed = 60.0;// mm/s
  float startSpeed = 5.0;// mm/s
  byte impulseTime = 3;
  byte stepDivision = 1;
  //boolean motorMode = true;
  boolean reverseMod = false;
  float mmPerTurn = 10;

  float position = 0;
  float beginBorder = -3000000.0;
  float endBorder = +3000000.0;

  byte stpPin;
  byte dirPin;
  byte enaPin;

}



#endif STEPPER_H
