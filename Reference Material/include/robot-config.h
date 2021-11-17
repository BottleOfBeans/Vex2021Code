using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller remote;
extern smartdrive Drivetrain;
extern motor LeftFront;
extern motor LeftBack;
extern motor RightFront;
extern motor RightBack;
extern motor Lift;
extern motor LeftIntake;
extern motor RightIntake;
extern motor Tray;
extern pot TrayPot;
extern inertial TurnGyroSmart;
extern line lineSensor;
/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );