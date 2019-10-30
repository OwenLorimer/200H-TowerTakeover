// Not commented bc not gonna bother if won't be used.
// Situation: finish the fucking lift.


#ifndef _LIFT_
#define _LIFT_

#ifndef _PROS_MAIN_H_
#include "main.h"
#endif

#ifndef _RCLIB_
#include "rcLib.cpp"
#endif

struct RobotLift{
  pros::Controller rcLift;
  pros::Motor* liftL = nullptr;
  pros::Motor* liftR = nullptr;
  pros::ADIButton* liftLim = nullptr;

  int liftState;
  float liftPos;


  RobotLift() : rcLift(RCM) {}
};

static RobotLift l1;

void LiftInit(pros::Controller rcName, int ml, int mr, int bumper){
  l1.liftL = new pros::Motor (ml);
  l1.liftR = new pros::Motor (mr);
  l1.rcLift = rcName;
  l1.liftLim = new pros::ADIButton (bumper);
}

void lift(int x){
  l1.liftL->move(x);
  l1.liftR->move(x);
}

void liftTare(){
	l1.liftL->tare_position();
	l1.liftR->tare_position();
}


void liftBrake(){
	l1.liftL->move_velocity(0);
	l1.liftR->move_velocity(0);
	l1.liftL->set_brake_mode(MOTOR_BRAKE_HOLD);
	l1.liftR->set_brake_mode(MOTOR_BRAKE_HOLD);
}

void liftReset(){
  l1.rcLift.rumble(". .");
  while(l1.liftState != 1){
	  lift(-20);
    pros::delay(25);
  }
}

void runLift(int isRetracted, float liftPos){

  if(liftPos < 1440 && l1.liftState != 1){
    if(rcGDV(l1.rcLift, R1)){
      lift(127);
    }
    else if(rcGDV(l1.rcLift, R2)){
      lift(-127);
    }
    else{
      liftBrake();
    }
  }
  else if(liftPos > 1440 && l1.liftState != 1){
    liftReset();
  }
  else if(liftPos < 1440 && l1.liftState == 1){
    liftTare();
    if(rcGDV(l1.rcLift, R1)){
      lift(127);
    }
  }
  else{
    liftTare();
  }
}

void rcLiftInput(){
  l1.liftState = l1.liftLim->get_value();
  float liftPos = fabs(((l1.liftL->get_position() + l1.liftR->get_position())/2));

  runLift(l1.liftState, liftPos);
}

#endif
