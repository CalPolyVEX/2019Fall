/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Clawbot Competition Template                              */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Drivetrain           drivetrain    1, 2            
// ArmMotor1            motor         8               
// ArmMotor2            motor         4               
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"


using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
bool ClawOpened = false;

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  ArmMotors.resetPosition();
  ClawMotor.resetPosition();
  ArmMotors.setVelocity(20, percent);
  ClawMotor.setVelocity(20, percent);
  Drivetrain.setDriveVelocity(100, percent);
}

void autonomous(void) {
  Drivetrain.setTimeout(3, seconds);
  Drivetrain.driveFor(reverse, 24, inches);
}

void usercontrol(void) {
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    if( Controller1.ButtonX.pressing()) {
     dig1.open();
     vex::task::sleep(250);
    }
    if(Controller1.ButtonB.pressing()) {
      dig1.close();
      vex::task::sleep(250);
    }
    if(Controller1.ButtonL1.pressing() && ArmMotors.position(degrees)<=460){
      ArmMotors.spin(forward);
    } else if(Controller1.ButtonL2.pressing() && ArmMotors.position(degrees)>=0){
      ArmMotors.spin(reverse);
    } else{
      ArmMotors.stop();
    }

    if(Controller1.ButtonR1.pressing() && ClawMotor.position(degrees)<=120){
      ClawMotor.spin(forward);
    } else if(Controller1.ButtonR2.pressing() && ClawMotor.position(degrees)>=0){
      ClawMotor.spin(reverse);
    } else{
      ClawMotor.stop();
    }

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}
