#include "stepper.h"
//#include "arduino.h"

//Constructor:
Stepper::Stepper(byte stpPin, byte dirPin, byte enaPin){
  this->stpPin = stpPin;
  this->dirPin = dirPin;
  this->enaPin = enaPin;


  pinMode(this->enaPin, OUTPUT);
  digitalWrite(this->enaPin, LOW);

  pinMode(this->dirPin, OUTPUT);
  digitalWrite(this->dirPin, LOW);

  pinMode(this->stpPin, OUTPUT);
  digitalWrite(this->stpPin, LOW);
}

Stepper::Stepper(byte stpPin, byte dirPin){
  this->stpPin = stpPin;
  this->dirPin = dirPin;

  pinMode(this->dirPin, OUTPUT);
  digitalWrite(this->dirPin, LOW);

  pinMode(this->stpPin, OUTPUT);
  digitalWrite(this->stpPin, LOW);
}
//End of Constructor;


//Set settings:

  //Settings of rotation for stepper motor:
  void Stepper::setmmPerTurn(float mmPerTurn){
    this->mmPerTurn = mmPerTurn;
  }

  void Stepper::setAcceleration(int acceleration){
    this->acceleration = acceleration;
  }

  void Stepper::setStepDivision(byte division){
    this->stepDivision = division;
  }

  void Stepper::setAnglePerStep(float angle){
    this->anglePerStep = angle;
  }

  void Stepper::setStartSpeed(float speed){
    this->startSpeed = speed;
  }

  void Stepper::setMaxSpeed(float speed){
    this->maxSpeed = speed;
  }
  //End of settings of rotation for stepper motor;

  //Settings of operation mode:
  void Stepper::setMotorMode(String Mode, String enaLvl = "LOW"){
    Mode = Mode.toUpperCase();
    if (Mode = "ON"){
      if (reverseMod = false) digitalWrite(this->enaPin, HIGH);
      if (reverseMod = true) digitalWrite(this->enaPin, LOW);
    }
    else{
      if (reverseMod = false) digitalWrite(this->enaPin, LOW);
      if (reverseMod = true) digitalWrite(this->enaPin, HIGH);
    }
  }

  void Stepper::reverse(){
    this->reverseMod = !this->reverseMod;
  }

  void Stepper::setImpulseTime(byte impulseTime){
    this->impulseTime = impulseTime;
  }
  //End of Settings of operation mode;



  //Settings of position set:
  void Stepper::setPosition(float position = 0){
    this->position = position;
  }

  void Stepper::setEndBorder(float endBorderPosition){
      this->endBorder = endBorderPosition;
  }

  void Stepper::setBeginBorder(float beginBorderPosition);{
    this->beginBorder = beginBorderPosition;
  }
  //End settings of position set;

//End of set-settings;



//Metods for work with stepper motor:

  //Position metods:
  void  Stepper::position(float Position){
    this->position = changePosition(Position - this->position);
  }

  float Stepper::changePosition(float changePos){
    this->stepsPerMM = (360.0 / this->anglePerStep) * this->stepDivision) / this->mmPerTurn;
    this->position = this->position + changePos;

    if (changePos < 0){
        if (this->reverseMod = false) digitalWrite(this->dirPin, HIGH);
        if (this->reverseMod = true) digitalWrite(this->dirPin, LOW);

        changePos = -changePos;
        if (this->beginBorder != -3000000.0 && this->position < this->beginBorder){
          changePos = changePos - (this->position - this->beginBorder);
          this->position = this->beginBorder;
        }
    }
    else{
        if (this->reverseMod = false) digitalWrite(this->dirPin, LOW);
        if (this->reverseMod = true) digitalWrite(this->dirPin, HIGH);

        if (this->endBorder != 3000000.0 && this->position > this->endBorder){
          changePos = changePos - (this->position - this->endBorder);
          this->position = this->endBorder;
        }
    }

      float accelerationWay = ((this->maxSpeed * this->maxSpeed) - (this->startSpeed * this->startSpeed)) / (2 * this->acceleration)
      if (accelerationWay * 2 > changePos) accelerationWay = changePos / 2;

      float accelerationWayBuffer = accelerationWay;
      int stepTime = 0;
      float speed = this->startSpeed;

      while (accelerationWayBuffer >= 0){
          if(speed < this->maxSpeed){
            speed = speed + (this->acceleration * stepTime);
            if(speed > this->maxSpeed) speed = maxSpeed;
          }
          stepTime = ((1000000 / speed) / this->stepsPerMM) - this->impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * this->stepTime);
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = changePos - (2 * accelerationWay);

      while (accelerationWayBuffer >= 0){
          accelerationWayBuffer = accelerationWayBuffer - (speed * this->stepTime);
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(stepTime);
      }

      accelerationWayBuffer = accelerationWay;

      while (accelerationWayBuffer >= 0){
          if(speed > this->startSpeed){
            speed = speed - (this->acceleration * stepTime);
            if(speed < this->startSpeed) speed = this->startSpeed;
          }
          stepTime = ()(1000000 / speed) / this->stepsPerMM) - this->impulseTime;
          accelerationWayBuffer = accelerationWayBuffer - (speed * this->stepTime);
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(this->stepTime);
      }

      return this->position;
  }

  //End of position metods;
