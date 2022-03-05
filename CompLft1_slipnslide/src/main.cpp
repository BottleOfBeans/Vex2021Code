
/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// RightBack            motor         5               
// LeftBack             motor         20              
// Grabby               motor         10              
// LeftFront            motor         1               
// LeftLift             motor         11              
// LiftGrabby           motor         15              
// Inertial7            inertial      18              
// RightFront           motor         6               
// Convy                motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

 void turn(double angle, double inc)
{
  double times = 0;
    double error = 500;
    double kP = 0.4;
    double kI = 0;
    double kD = 3;
    
    double integral;
    double derivative;
    double prevError;
    double power;
    double speed;
    double prevangle = 3000;
    
    while (error > 1 or error < -1){
      
      error = angle - Inertial7.rotation(degrees);
      
      integral = integral + (error/10);
      if (integral > 500){
        integral = 500;
      }
      derivative = error - prevError;
      prevError = error;
      power = (error * kP) + (integral * kI) + (derivative + kD) + inc;
      
      LeftFront.spin(fwd, power, pct);
      RightFront.spin(reverse, power, pct);
      LeftBack.spin(fwd, power, pct);
      RightBack.spin(reverse, power, pct);
      
      wait(0.001, seconds);
    }
    LeftFront.stop(brake);
    RightFront.stop(brake);
    LeftBack.stop(brake);
    RightBack.stop(brake);
    wait(0.01,seconds);
    times++;
  }

int CheckDirection(double val){

  if(val > 0){
    return 1;
  }
  else{
  return -1;
  }


}

void drive(double inches,double completeTime = 500, double maxSpeed = 100) // direction: 0 forward, -1 backward, 2 strafe left, -2 strafe right
{
  double target = inches / (3.1415 * 4);

  target *= 360*2;
  LeftFront.resetRotation();
  RightBack.resetRotation();
  RightFront.resetRotation();
  LeftBack.resetRotation();
  double kp = .37, ki = 0, kd = .3;
  
  double P = 0, I = 0, D = 0;
  double error, lastError = 0;
  double motorSpeed = 0;
  
  Brain.Timer.clear();
  while(true)
  {
    
    error = -(LeftFront.rotation(rotationUnits::deg) + RightBack.rotation(rotationUnits::deg) + RightFront.rotation(deg) + LeftBack.rotation(deg))/4 + target;

    P = kp * error;
    if(fabs(error) < 50)
    {
      I += ki * error;

    }
    D = kd * (error - lastError);
    lastError = error;

    motorSpeed = P + I + D;
    if(fabs(motorSpeed) > maxSpeed)
    {
      motorSpeed = CheckDirection(motorSpeed) * maxSpeed;
    }
    if(fabs(error) < .2 && fabs(lastError) < .2){
      motorSpeed = 0;
    }
        
    double anglePower = 0;
    if(fabs(motorSpeed) > 1)
    {
      anglePower = 0;
    }
    
    LeftFront.spin(directionType::fwd, motorSpeed , percentUnits::pct);
    LeftBack.spin(directionType::fwd, motorSpeed , percentUnits::pct);   
    RightFront.spin(directionType::fwd, motorSpeed+anglePower, percentUnits::pct);
    RightBack.spin(directionType::fwd, motorSpeed+anglePower, percentUnits::pct);
    
    if(fabs(motorSpeed) < 1)
    {
      break;
    }
    task::sleep(20);
  }
  LeftBack.stop(brakeType::hold);
  LeftFront.stop(brakeType::hold);
  RightFront.stop(brakeType::hold);
  RightBack.stop(brakeType::hold);  

}
void drivestartout(double inches, double correction,double completeTime = 5000, double maxSpeed = 100) // direction: 0 forward, -1 backward, 2 strafe left, -2 strafe right
{
  double target = inches / (3.1415 * 4);

  target *= 360*2;
  LeftFront.resetRotation();
  double kp = .37, ki = 0, kd = .3;
  
  double P = 0, I = 0, D = 0;
  double error, lastError = 0;
  double motorSpeed = 0;
  
  Brain.Timer.clear();
  while(true)
  {
    
    error = -LeftFront.rotation(rotationUnits::deg) + target;

    P = kp * error;
    if(fabs(error) < 50)
    {
      I += ki * error;

    }
    D = kd * (error - lastError);
    lastError = error;

    motorSpeed = P + I + D;
    if(fabs(motorSpeed) > maxSpeed)
    {
      motorSpeed = CheckDirection(motorSpeed) * maxSpeed;
    }
    if(fabs(error) < .2 && fabs(lastError) < .2){
      motorSpeed = 0;
    }
        
    double anglePower = 0;
    if(fabs(motorSpeed) > 1)
    {
      anglePower = 0;
    }
    
    LeftFront.spin(directionType::fwd, motorSpeed , percentUnits::pct);
    LeftBack.spin(directionType::fwd, motorSpeed , percentUnits::pct);   
    RightFront.spin(directionType::fwd, motorSpeed+anglePower - correction, percentUnits::pct);
    RightBack.spin(directionType::fwd, motorSpeed+anglePower - correction, percentUnits::pct);
    if(error < 300){
      LiftGrabby.setVelocity(100,percent);
      LiftGrabby.spin(fwd);
    }
    if(fabs(motorSpeed) < 1)
    {
      LiftGrabby.stop(hold);
      break;
    }
    task::sleep(20);
    correction = 0;
  }
  LeftBack.stop(brakeType::hold);
  LeftFront.stop(brakeType::hold);
  RightFront.stop(brakeType::hold);
  RightBack.stop(brakeType::hold);  

}
void grabby(int updown)
{
  Grabby.setVelocity(100,pct);
  if(updown == 1){
    Grabby.spinToPosition(-590,degrees);
  }else if(updown == 2){
    Grabby.spinToPosition(-210,degrees);
  }else{
    Grabby.spinToPosition(0,degrees);
  }
}
void deployconvy(int dir, double t){
  if(dir == 1){
    Convy.spin(forward,100,pct);
  }else if(dir == 2){
    Convy.spin(reverse,100,pct);
  }
  wait(t,seconds);
  Convy.stop();
}
void up(){
  LiftGrabby.spinToPosition(0,degrees);
  LiftGrabby.stop(hold);
}
void down(){
  LiftGrabby.setVelocity(100,percent);
  LiftGrabby.spinToPosition(220,degrees);
  LiftGrabby.stop(hold);
}
void convyStart(){
  Convy.spin(forward,100,pct);
}
void convyStop(){
  Convy.stop();
}
void lift(double angle){
  double error = 500;
  double kP = 2;
  double kI = 0.1;
  double kD = 0.1;
  
  double integral;
  double derivative;
  double prevError;
  double power;
  
  while (error > 5 or error <-5){
    error = angle - LeftLift.position(degrees);
    integral = integral + (error)/10;
    if (integral > 2000){
      integral = 2000;
    }
    derivative = error - prevError;
    prevError = error;
    power = error;//(error * kP) + (integral * kI) + (derivative + kD);
    
    LeftLift.spin(fwd, power, pct);
  }
  LeftLift.stop(hold);
}
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
  //Initializing Robot Configuration. DO NOT REMOVE!
  Inertial7.calibrate();
  Inertial7.setRotation(0, degrees);
  this_thread::sleep_for(1000);
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
  drivestartout(24,0);
  drive(-5);
  turn(20,1);
  drive(-10);
  grabby(1);
  turn(-35,-4);
  drive(-9);
  grabby(2);
  drive(10);
  lift(200);
  deployconvy(1,1);
  deployconvy(2,0.3);
  deployconvy(1,1);
  deployconvy(2,0.3);
  deployconvy(1,1);
  deployconvy(2,0.3);
  grabby(1);
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
    int leftWheelSplit =  Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent);
    int rightWheelSplit = (Controller1.Axis3.position(percent)) - Controller1.Axis1.position(percent);
    
    if (Controller1.ButtonR1.pressing() == true){ //This is your Conveyor Belt
      Convy.spin(forward, 100, pct);
    }
    else if(Controller1.ButtonR2.pressing() == true){    
      Convy.spin(reverse, 100, pct); 
    }else{ //This is your Conveyor Belt on drugs
      Convy.stop();
    }

    if (Controller1.ButtonL1.pressing() == true){ //This is your Lift
      LeftLift.spin(forward, 100, pct);
    }
    else if(Controller1.ButtonL2.pressing() == true){    
      LeftLift.spin(reverse, 100, pct);
    
    }else{ //This is your Lift on drugs
      LeftLift.stop(hold);
    }

    if (Controller1.ButtonX.pressing() == true){ //This is your Grabby
      Grabby.spin(forward, 100, pct);
    }
    else if (Controller1.ButtonB.pressing() == true){    
      Grabby.spin(reverse, 100, pct); 
    }else{ //This is your Grabby on drugs
      Grabby.stop(hold);
    }
  
    //SplitDerivitiverive Move
    LeftFront.spin(forward, leftWheelSplit, pct); 
    RightFront.spin(forward, rightWheelSplit, pct);
    
    LeftBack.spin(forward, leftWheelSplit, pct);
    RightBack.spin(forward, rightWheelSplit, pct);

    if(Controller1.ButtonY.pressing()){
      LiftGrabby.spin(fwd,100,pct);
    } else if(Controller1.ButtonA.pressing()){
      LiftGrabby.spin(reverse,100,pct);
    }else{
      LiftGrabby.stop(hold);
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
