#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

// A global instance of brain used for printing to the V5 Brain screen
brain  Brain;

// VEXcode device constructors
controller Controller1 = controller(primary);
motor RightBack = motor(PORT1, ratio18_1, true);
motor LeftBack = motor(PORT5, ratio18_1, false);
motor Grabby = motor(PORT6, ratio18_1, false);
motor LeftFront = motor(PORT10, ratio18_1, false);
motor LeftLift = motor(PORT11, ratio18_1, false);
motor RightLift = motor(PORT15, ratio18_1, true);
inertial Inertial = inertial(PORT18);
motor RightFront = motor(PORT20, ratio18_1, true);
motor Convy = motor(PORT16, ratio18_1, true);

// VEXcode generated functions
// define variable for remote controller enable/disable
bool RemoteControlCodeEnabled = true;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}