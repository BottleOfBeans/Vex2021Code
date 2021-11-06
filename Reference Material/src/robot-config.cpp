#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller remote = controller(primary);
motor LeftFront = motor(PORT4, ratio18_1, false);
motor LeftBack = motor(PORT11, ratio18_1, false);
motor_group LeftDriveSmart = motor_group(LeftBack, LeftFront);

motor RightFront = motor(PORT8, ratio18_1, true); 
motor RightBack = motor(PORT19, ratio18_1, true); 
motor_group RightDriveSmart = motor_group(RightFront, RightBack);

inertial TurnGyroSmart = inertial(PORT12);
smartdrive Drivetrain= smartdrive(LeftDriveSmart, RightDriveSmart, TurnGyroSmart,319.19, 320, 165, mm, 1);
motor Lift = motor(PORT16, ratio18_1, true);
motor LeftIntake = motor(PORT14, ratio18_1, false);
motor RightIntake = motor(PORT21, ratio18_1, true);
motor Tray = motor(PORT3, ratio18_1, true);
pot TrayPot = pot(Brain.ThreeWirePort.A);
line lineSensor = line(Brain.ThreeWirePort.B);
// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  Brain.Screen.print("Device initialization...");
  Brain.Screen.setCursor(2, 1);
  // calibrate the drivetrain gyro
  wait(200, msec);
  TurnGyroSmart.calibrate();
  Brain.Screen.print("Calibrating Gyro for Drivetrain");
  // wait for the gyro calibration process to finish
  while (TurnGyroSmart.isCalibrating()) {
    wait(25, msec);
  }
  task::sleep(2000);
  // reset the screen now that the calibration is complete
  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1,1);
  wait(50, msec);
  Brain.Screen.clearScreen();
}