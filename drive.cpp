/*----------------------------------------------------------------------------*/
/*                       Name: Mecanum Drive Control                          */
/*                           Created: August 2019                             */
/*                          Author: Chris Katsaros                            */
/*                          For use by: Team 200H                             */
/*                            Revisions made by:                              */
/*                                                                            */
/*    About: An extremely simple file for the abstraction of a standard 4     */
/*           motor V5 mechanum drive. Gyroscope code still needs to be added  */
/*           to implement field-oriented control. For others who might want   */
/*           to use this file,if you make any revisions or improvements,      */
/*           please test and redistribute for others to use. Make sure to add */
/*           your name to the 'Revisions made by:' field.                     */
/*----------------------------------------------------------------------------*/
// Macro guards
#ifndef _DRIVE_
#define _DRIVE_

#ifndef _PROS_MAIN_H_
#include "main.h"
#endif

#ifndef _RCLIB_
#include "rcLib.cpp"
#endif

//#include <memory> seems to be uneeded now

// Struct for holding drive information
struct RobotDrive{
  pros::Controller rcDrive;
  pros::Motor* fl = nullptr;
  pros::Motor* bl = nullptr;
  pros::Motor* fr = nullptr;
  pros::Motor* br = nullptr;

  // Init pros::Controller with ID master on new RobotDrive
  RobotDrive() : rcDrive(RCM) {}
};

static RobotDrive d1;
// Function to run drive motors
void runMecanumDrive(int leftx, int lefty, int rightx){
  // Calculate motor power.
  int frontLeft  = lefty + rightx + leftx;
  int backLeft   = lefty + rightx - leftx;
  int frontRight = lefty - rightx - leftx;
  int backRight  = lefty - rightx + leftx;

  // Normalize motor power (completely took this from jpearman, thank ya kindly jpearman).
  int max = abs(frontLeft);

  if(abs(backLeft) > max){
    max = abs(backLeft);
  }
  if(abs(backRight) > max){
    max = abs(backRight);
  }
  if(abs(frontRight) > max){
    max = abs(frontRight);
  }
  if(max>127){
    frontLeft  = 127 * frontLeft / max;
    backLeft   = 127 * backLeft  / max;
    backRight  = 127 * backRight  / max;
    frontRight = 127 * frontRight / max;
  }

  // Set power to motors.
  d1.fl->move(frontLeft);
  d1.bl->move(backLeft);
  d1.fr->move(frontRight);
  d1.br->move(backRight);


}


// Function to get user input from controller joysticks, called in opcontrol
void rcDriveInput(){
  // Get joystick input values.
  int lx = rcGAV(d1.rcDrive, ALX, true);
  int ly = rcGAV(d1.rcDrive, ALY, false);
  int rx = rcGAV(d1.rcDrive, ARX, false);

  runMecanumDrive(lx, ly, rx);
}


// Function to initialize a mecanum drive, called in opcontrol
void MecanumDriveInit(pros::Controller rcName, int mfl, int mbl, int mfr, int mbr){
  d1.rcDrive = rcName;
  d1.fl = new pros::Motor(mfl);
  d1.bl = new pros::Motor(mbl);
  d1.fr = new pros::Motor(mfr);
  d1.br = new pros::Motor(mbr);
}
#endif
