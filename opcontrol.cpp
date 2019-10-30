#include "main.h"
#include "drive.cpp"
#include "lift.cpp"

#define DFL_PRT 11
#define DBL_PRT 12
#define DFR_PRT 20
#define DBR_PRT 19
#define LL_PRT 5
#define LR_PRT 6
#define LC_PRT 7
#define LIFTLIM_PRT 1

//Controller ctrl1 uses master
pros::Controller ctrl1(pros::E_CONTROLLER_MASTER);
//Front Left drive motor is reversed
pros::Motor dFl(11, true);
pros::Motor dBl(12);
pros::Motor dFr(20);
//Back Right drive motor is reversed
pros::Motor dBr(19, true);
pros::Motor liftL(5);
pros::Motor liftClaw(7);
//Right side lift motor is reversed
pros::Motor liftR(6, true);
pros::ADIButton liftLim('A');
pros::ADIGyro gyro('B');


void opcontrol(){
	LiftInit(ctrl1, LL_PRT, LR_PRT, LIFTLIM_PRT);
	MecanumDriveInit(ctrl1, DFL_PRT, DBL_PRT, DFR_PRT, DBR_PRT);
	while (true){
		rcLiftInput();
		rcDriveInput();
	pros::delay(20);
	}
}
