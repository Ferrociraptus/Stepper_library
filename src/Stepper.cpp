#include "STEPPER.h"
#include <Arduino.h>

//Constructor:
Stepper::Stepper(byte stpPin, byte dirPin, byte enaPin = NONE){
  this->stpPin = stpPin;
  this->dirPin = dirPin;
  this->enaPin = enaPin;

  if (enaPin != NONE){
    pinMode(enaPin, OUTPUT);
    digitalWrite(enaPin, LOW);
  }
  pinMode(dirPin, OUTPUT);
  digitalWrite(dirPin, LOW);

  pinMode(stpPin, OUTPUT);
  digitalWrite(stpPin, LOW);
}
//End of Constructor;


//Set settings:

  //Settings of rotation for stepper motor:
  void setmmPerTurn(float mmPerTurn){
    this->mmPerTurn = mmPerTurn;
  }

  void setAcceleration(int acceleration){
    this->acceleration = acceleration;
  }

  void setStepDivision(byte division){
    this->stepDivision = division;
  }

  void setAnglePerStep(float angle){
    this->anglePerStep = angle;
  }

  void setStartSpeed(float speed){
    this->startSpeed = speed;
  }

  void setMaxSpeed(float speed){
    this->maxSpeed = speed;
  }
  //End of settings of rotation for stepper motor;

  //Settings of operation mode:
  void setMotorMode(String Mode, String enaLvl = "LOW"){
    Mode = Mode.toUpperCase();
    if (Mode = "ON"){
      if (reverseMod = false) digitalWrite(enaPin, HIGH);
      if (reverseMod = true) digitalWrite(enaPin, LOW);
    }
    else{
      if (reverseMod = false) digitalWrite(enaPin, LOW);
      if (reverseMod = true) digitalWrite(enaPin, HIGH);
    }
  }

  void reverse(){
    this->reverseMod = !reverseMod;
  }

  void setImpulseTime(byte impulseTime){
    this->impulseTime = impulseTime;
  }
  //End of Settings of operation mode;



  //Settings of position set:
  void setPosition(float position = 0){
    this->position = position;
  }

  void setEndBorder(float endBorderPosition){
      this->endBorder = endBorderPosition;
  }

  void setBeginBorder(float beginBorderPosition);{
    this->beginBorder = beginBorderPosition;
  }
  //End settings of position set;

//End of set-settings;



//Metods for work with stepper motor:

  //Position metods:
  void  position(float Position){
    this->position = changePosition(Position - position);
  }

  float changePosition(float changePos){
    this->stepsPerMM = (360.0 / anglePerStep) * stepDivision) / mmPerTurn;
    this->position = poition + changePos;

    if (changePos < 0){
        if (reverseMod = false) digitalWrite(dirPin, HIGH);
        if (reverseMod = true) digitalWrite(dirPin, LOW);

        changePos = -changePos;
        if (beginBorder != NONE && position < beginBorder){
          changePos = changePos - (position - beginBorder);
          this->position = beginBorder;
        }
    }
    else{
        if (reverseMod = false) digitalWrite(dirPin, LOW);
        if (reverseMod = true) digitalWrite(dirPin, HIGH);

        if (endBorder != NONE && position > endBorder){
          changePos = changePos - (position - endBorder);
          this->position = endBorder;
        }
    }

      float accelerationWay = ((maxSpeed * maxSpeed) - (startSpeed * startSpeed)) / (2 * acceleration)
      if (accelerationWay * 2 > changePos) accelerationWay = changePos / 2;

      float accelerationWayBuffer = accelerationWay;
      int stepTime = 0;
      float speed = startSpeed;

      while (accelerationWayBuffer >= 0){
          if(speed < maxSpeed){
            speed = speed + (acceleration * stepTime);
            if(speed > maxSpeed) speed = maxSpeed;
          }
          stepTime = ()(1000000 / speed) / stepsPerMM) - impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = changePos - (2 * accelerationWay);

      while (accelerationWayBuffer >= 0){
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = accelerationWay;

      while (accelerationWayBuffer >= 0){
          if(speed > startSpeed){
            speed = speed - (acceleration * stepTime);
            if(speed < startSpeed) speed = startSpeed;
          }
          stepTime = ()(1000000 / speed) / stepsPerMM) - impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      return position;
  }

  void  changePosition(float changePos){
    this->stepsPerMM = (360.0 / anglePerStep) * stepDivision) / mmPerTurn;
    this->position = poition + changePos;

    if (changePos < 0){
        if (reverseMod = false) digitalWrite(dirPin, HIGH);
        if (reverseMod = true) digitalWrite(dirPin, LOW);

        changePos = -changePos;
        if (beginBorder != NONE && position < beginBorder){
          changePos = changePos - (position - beginBorder);
          this->position = beginBorder;
        }
    }
    else{
        if (reverseMod = false) digitalWrite(dirPin, LOW);
        if (reverseMod = true) digitalWrite(dirPin, HIGH);

        if (endBorder != NONE && position > endBorder){
          changePos = changePos - (position - endBorder);
          this->position = endBorder;
        }
    }

      float accelerationWay = ((maxSpeed * maxSpeed) - (startSpeed * startSpeed)) / (2 * acceleration)
      if (accelerationWay * 2 > changePos) accelerationWay = changePos / 2;

      float accelerationWayBuffer = accelerationWay;
      int stepTime = 0;
      float speed = startSpeed;

      while (accelerationWayBuffer >= 0){
          if(speed < maxSpeed){
            speed = speed + (acceleration * stepTime);
            if(speed > maxSpeed) speed = maxSpeed;
          }
          stepTime = ()(1000000 / speed) / stepsPerMM) - impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = changePos - (2 * accelerationWay);

      while (accelerationWayBuffer >= 0){
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = accelerationWay;

      while (accelerationWayBuffer >= 0){
          if(speed > startSpeed){
            speed = speed - (acceleration * stepTime);
            if(speed < startSpeed) speed = startSpeed;
          }
          stepTime = ()(1000000 / speed) / stepsPerMM) - impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * stepTime);
          digitalWrite(stpPin, HIGH);
          delayMicroseconds(impulseTime);
          digitalWrite(stpPin, LOW);
          delayMicroseconds(stepTime);
      }
  }

  //End of position metods;
