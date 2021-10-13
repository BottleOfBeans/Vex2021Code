using namespace vex;

extern brain Brain;

// VEXcode devices
extern controller Controller1;
extern motor RightBack;
extern motor LeftBack;
extern motor Grabby;
extern motor LeftFront;
extern motor LeftLift;
extern motor RightLift;
extern inertial Inertial;
extern motor RightFront;
extern motor Convy;

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Text.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );