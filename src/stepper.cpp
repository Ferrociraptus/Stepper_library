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
  void Stepper::setMotorMode(String Mode = "ON", String enaLvl = "LOW"){
    Mode.toUpperCase();
    enaLvl.toUpperCase();
    if (Mode == "ON"){
      this->motorMod = true;
      if (enaLvl == "HIGH") digitalWrite(this->enaPin, HIGH);
      if (enaLvl == "LOW") digitalWrite(this->enaPin, LOW);
    }
    if (Mode == "OFF"){
      this->motorMod = false;
      if (enaLvl == "HIGH") digitalWrite(this->enaPin, LOW);
      if (enaLvl == "LOW") digitalWrite(this->enaPin, HIGH);
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

  void Stepper::setBeginBorder(float beginBorderPosition){
    this->beginBorder = beginBorderPosition;
  }
  //End settings of position set;

//End of set-settings;



//Metods for work with stepper motor:

  //Position metods:
  void  Stepper::moveToPosition(float Position){
    this->position = changePosition(Position - this->position);
  }

  float Stepper::changePosition(float changePos){
  if(this->motorMod == true){
    this->stepsPerMM = ((360.0 / this->anglePerStep) * this->stepDivision) / this->mmPerTurn;
    this->position = this->position + changePos;

    if (changePos < 0){
        if (this->reverseMod == false) digitalWrite(this->dirPin, HIGH);
        if (this->reverseMod == true) digitalWrite(this->dirPin, LOW);

        changePos = -changePos;
        if (this->beginBorder != -3000000.0 && this->position < this->beginBorder){
          changePos = changePos - (this->position - this->beginBorder);
          this->position = this->beginBorder;
        }
    }
    else{
        if (this->reverseMod == false) digitalWrite(this->dirPin, LOW);
        if (this->reverseMod == true) digitalWrite(this->dirPin, HIGH);

        if (this->endBorder != 3000000.0 && this->position > this->endBorder){
          changePos = changePos - (this->position - this->endBorder);
          this->position = this->endBorder;
        }
    }

      float accelerationWay = ((this->maxSpeed * this->maxSpeed) - (this->startSpeed * this->startSpeed)) / (2 * this->acceleration);
      if (accelerationWay * 2 >= changePos) accelerationWay = changePos / 2;

      float accelerationWayBuffer = accelerationWay;
      int stepTime = 0;
      float speed = this->startSpeed;
      int iterations = 0;

      while (accelerationWayBuffer >= 0){
        if (iterations == (stepsPerMM * 0.01)){
          if(speed < this->maxSpeed && speed != this->maxSpeed){
            speed = speed + ((this->acceleration * stepTime * iterations) / 1000000.0);
          if(speed > this->maxSpeed) speed = this->maxSpeed;
          }
            accelerationWayBuffer = accelerationWayBuffer - 0.01;
            stepTime = ((1000000 / speed) / this->stepsPerMM) - this->impulseTime;

            iterations = 0;
        }
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(stepTime);
          iterations ++;
      }

      accelerationWayBuffer = changePos - (2 * accelerationWay);
      iterations = 0;

      while (accelerationWayBuffer >= 0){
        if (iterations == (stepsPerMM * 0.01)){
          accelerationWayBuffer = accelerationWayBuffer - 0.01;
          iterations = 0;
          }
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(stepTime);
          iterations++;
      }

      accelerationWayBuffer = accelerationWay;
      iterations = 0;

      while (accelerationWayBuffer >= 0){
        if (iterations == (stepsPerMM * 0.01)){
          if(speed > this->startSpeed && speed != this->startSpeed){
            speed = speed - ((this->acceleration * stepTime * iterations) / 1000000.0);
          if(speed < this->startSpeed) speed = this->startSpeed;
          }
            accelerationWayBuffer = accelerationWayBuffer - 0.01;
            stepTime = ((1000000 / speed) / this->stepsPerMM) - this->impulseTime;

            iterations = 0;
        }
          digitalWrite(this->stpPin, HIGH);
          delayMicroseconds(this->impulseTime);
          digitalWrite(this->stpPin, LOW);
          delayMicroseconds(stepTime);
          iterations++;
      }

      return this->position;
  }
}

  //End of position metods;

  //Information metods:
  // String showPosition(boolean ifshowPos = true, boolean ifshowBorders = true){
  //   if(ifshowPos == 1){
  //     String answer = String("Position:\t") + String(position) + String("\n");
  //   }
  //
  //   if(ifshowBorders == 1){
  //       if (beginBorder != -3000000.0){
  //           answer = answer + String("BeginBorder:\t") + String(beginBorder) + String("\n");
  //   }
  //   else{
  //       answer = answer + String("BeginBorder:\t") + String("NONE") + String("\n");
  //   }
  //
  //   if(endBorder != 3000000.0){
  //     answer = answer + String("EndBorder:\t") + String(endBorder) + String("\n");
  //   }
  //   else{
  //     answer = answer + String("EndBorder:\t") + String("NONE") + String("\n");
  //   }
  // }
  // return answer;
  // }
  //
  // String showInformation(String nameOfStepperController, boolean ifshowAnglePerStep = true, boolean ifshowDivision = true){
  //     String answer = String("Name of stepper controller:\t") + nameOfStepperController + String("\n");
  //
  //     if(ifshowAnglePerStep == 1){
  //       answer = answer + String("Angle per step:\t") + String(anglePerStep) + String("\n");
  //     }
  //
  //     if(ifshowDivision == 1){
  //       answer = answer + String("Step division:\t") + String(stepDivision) + String("\n");
  //     }
  //
  //     return answer;
  // }
  //End of information metods;

  //End of metods for work with stepper motor;
