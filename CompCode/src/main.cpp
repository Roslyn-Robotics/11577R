/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
motor LeftDriveSmart = motor(PORT6, ratio18_1, false);
motor RightDriveSmart = motor(PORT5, ratio18_1, true);
drivetrain Drivetrain = drivetrain(LeftDriveSmart, RightDriveSmart, 299.24, 295, 130, mm, 1);
controller Controller1 = controller(primary);
motor Left = motor(PORT10, ratio36_1, false);
motor Right = motor(PORT1, ratio36_1, true);
motor Bottom = motor(PORT9, ratio36_1, false);
motor ClawL = motor(PORT11, ratio18_1, false);
motor ClawR = motor(PORT20, ratio18_1, true);
motor rise = motor(PORT15, ratio36_1, false);
// VEXcode generated functions
// define variables used for controlling motors based on controller inputs
bool Controller1R1R2ControlMotorsStopped = true;
bool Controller1L1L2ControlMotorsStopped = true;
bool Controller1XBControlMotorsStopped = true;
bool DrivetrainLNeedsToBeStopped_Controller1 = true;
bool DrivetrainRNeedsToBeStopped_Controller1 = true;
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
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  Drivetrain.driveFor(reverse, 400, mm);
  wait(1,seconds);
  Drivetrain.driveFor(forward, 600, mm);
  //Left.spin(forward, 100, pct);
  //Right.spin(forward,100, pct);
  //Bottom.spin(forward,100, pct);
  //wait(0.5,seconds);
  //Left.stop();
  //Right.stop();
  //Bottom.stop();
  //ClawL.spin(reverse, 50, pct);
  //ClawR.spin(reverse, 50, pct);
  //wait(1,seconds);
  //ClawL.stop();
  //ClawR.stop();                        
  //Drivetrain.turnFor(-170, degrees);
  //wait(1,seconds);
  //Drivetrain.driveFor(forward, 200, mm);
  //wait(1,seconds);
  //ClawL.spin(forward, 50, pct);
  //ClawR.spin(forward, 50, pct);
  //wait(1,seconds);
  //ClawL.stop();
  //ClawR.stop();
  //wait(1,seconds);
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  // User control code here, inside the loop
  
  
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    // calculate the drivetrain motor velocities from the controller joystick axies
    // left = Axis3
    // right = Axis2
    int drivetrainLeftSideSpeed = Controller1.Axis3.position();
    int drivetrainRightSideSpeed = Controller1.Axis2.position();
    // check if the value is inside of the deadband range
    if (drivetrainLeftSideSpeed < 5 && drivetrainLeftSideSpeed > -5) {
      // check if the left motor has already been stopped
      if (DrivetrainLNeedsToBeStopped_Controller1) {
        // stop the left drive motor
        LeftDriveSmart.stop();
        // tell the code that the left motor has been stopped
        DrivetrainLNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the left motor next time the input is in the deadband range
      DrivetrainLNeedsToBeStopped_Controller1 = true;
    }
    // check if the value is inside of the deadband range
    if (drivetrainRightSideSpeed < 5 && drivetrainRightSideSpeed > -5) {
      // check if the right motor has already been stopped
      if (DrivetrainRNeedsToBeStopped_Controller1) {
        // stop the right drive motor
        RightDriveSmart.stop();
        // tell the code that the right motor has been stopped
        DrivetrainRNeedsToBeStopped_Controller1 = false;
      }
    } else {
      // reset the toggle so that the deadband code knows to stop the right motor next time the input is in the deadband range
      DrivetrainRNeedsToBeStopped_Controller1 = true;
    }
    // only tell the left drive motor to spin if the values are not in the deadband range
    if (DrivetrainLNeedsToBeStopped_Controller1) {
      LeftDriveSmart.setVelocity(drivetrainLeftSideSpeed, percent);
      LeftDriveSmart.spin(forward);
    }
    // only tell the right drive motor to spin if the values are not in the deadband range
    if (DrivetrainRNeedsToBeStopped_Controller1) {
      RightDriveSmart.setVelocity(drivetrainRightSideSpeed, percent);
      RightDriveSmart.spin(forward);
    }
    // check the Up/Down Buttons status to control Left
    if (Controller1.ButtonL1.pressing()) {
      Left.spin(forward, 100, pct);
      Right.spin(forward,100, pct);
      Bottom.spin(forward,100, pct);
      // Left.setBrake(hold);
      // Right.setBrake(hold);
      // Bottom.setBrake(hold);
      Controller1L1L2ControlMotorsStopped = false;
    } else if (Controller1.ButtonL2.pressing()) {
      Left.spin(reverse,15, pct);
      Right.spin(reverse,15, pct);
      Bottom.spin(reverse,15, pct);
      // Left.setBrake(hold);
      // Right.setBrake(hold);
      // Bottom.setBrake(hold);
      Controller1L1L2ControlMotorsStopped = false;
    } else if (!Controller1L1L2ControlMotorsStopped){
      Left.stop();
      Right.stop();
      Bottom.stop();
         Left.setBrake(hold);
      Right.setBrake(hold);
      Bottom.setBrake(hold);
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1L1L2ControlMotorsStopped = true;
    }

    if (Controller1.ButtonR1.pressing()) {
      ClawL.spin(forward, 80, pct);
      ClawR.spin(forward,80, pct);
      ClawL.setBrake(hold);
      ClawR.setBrake(hold);
      Controller1R1R2ControlMotorsStopped = false;
    } else if (Controller1.ButtonR2.pressing()) {
      ClawL.spin(reverse,80, pct);
      ClawR.spin(reverse, 80, pct);
      ClawL.setBrake(hold);
      ClawR.setBrake(hold);
      Controller1R1R2ControlMotorsStopped = false;
    } else if (!Controller1R1R2ControlMotorsStopped){
      ClawL.stop();
      ClawR.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1R1R2ControlMotorsStopped = true;
    }

    if (Controller1.ButtonX.pressing()) {
      rise.spin(forward, 20, pct);
      rise.setBrake(hold);
      Controller1XBControlMotorsStopped = false;
    } else if (Controller1.ButtonB.pressing()) {
      rise.spin(reverse,20, pct);
      rise.setBrake(hold);
      Controller1XBControlMotorsStopped = false;
    } else if (!Controller1XBControlMotorsStopped){
      rise.stop();
      // set the toggle so that we don't constantly tell the motor to stop when the buttons are released
      Controller1XBControlMotorsStopped = true;
    }
    // wait before repeating the process
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
