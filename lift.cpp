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
  pros::Motor* liftClaw = nullptr;
  pros::ADIButton* liftLim = nullptr;

  int liftState;
  float liftPos;


  RobotLift() : rcLift(RCM) {}
};

static RobotLift l1;

void LiftInit(pros::Controller rcName, int ml, int mr, int bumper, int mClaw){
  l1.liftL = new pros::Motor (ml);
  l1.liftR = new pros::Motor (mr);
  l1.liftClaw = new pros::Motor (mClaw);
  l1.rcLift = rcName;
  l1.liftLim = new pros::ADIButton (bumper);
}

void lift(int x){
  l1.liftL->move(x);
  l1.liftR->move(x);
}
void liftClaw(int x){
  l1.liftClaw->move(x);
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


void runLift(){
	 
  if(rcGDV(l1.rcLift, R1)){
    lift(127);
    }
  else if(rcGDV(l1.rcLift, R2)){
    lift(-127);
    }
  else{
    liftBrake();
    } 
  else{
    liftTare();
  }
}

void runClaw(){
	
  if (rcGDV(l1.rcLift, L1)){
    l1.liftClaw->move(127);
  }
	
  else if (rcGDV(l1.rcLift, L2)){
    l1.liftClaw->move(-127);
  }

  else{
    l1.liftClaw->move_velocity(0);
    l1.liftClaw->set_brake_mode(MOTOR_BRAKE_HOLD);
  }
}
	

#endif
