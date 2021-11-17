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
// LeftBack             motor         5               
// Grabby               motor         6               
// RightBack            motor         1               
// RightFront           motor         20              
// Inertial             motor         7               
// LeftLift             motor         11              
// RightLift            motor         15              
// LeftFront            motor         10              
// Convy                motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

  void pre_auton(void){
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  float prevAngle;
  bool rightleft;
  bool speed;
  void turn (int angle){
    float angleA = angle + prevAngle;
    prevAngle = angleA;  
    float speed = Inertial.rotation(deg);
    while ((Inertial.rotation(deg) + 0.5 < angleA) or (Inertial.rotation(deg) - 0.5 > angleA)){
      if ( Inertial.rotation(deg) < angleA){
        while ( Inertial.rotation(deg) < angleA){
          speed = angleA - Inertial.rotation(deg) + 2;
          speedfp = speed;
          LeftFront.spin(fwd, speed, pct);
          RightFront.spin(reverse, speed, pct);
          LeftBack.spin(fwd, speed, pct);
          RightBack.spin(reverse, speed, pct);
          rightleft = true;
        }
      } else {
        while ( Inertial.rotation(deg) > angleA){
          speed = angleA - Inertial.rotation(deg) - 2;
          speedfp = speed;
          LeftFront.spin(fwd, speed /2, pct);
          RightFront.spin(reverse, speed/2, pct);
          LeftBack.spin(fwd, speed, pct);
          RightBack.spin(reverse, speed/2, pct);
          rightleft = false;
        }
      }
    }
  }  
    
    LeftFront.stop(brakeType::brake);
    RightFront.stop(brakeType::brake);
    LeftBack.stop(brakeType::brake);
    RightBack.stop(brakeType::brake);
  
  float errorA;
  float limitFS;

  float prevdistance;
  void drivef (float distanceB, float speedMultiplyer){
    float kP = 0.3;
    float distanceA = distanceB * 28.66;
    float distance = distanceA + prevdistance;
    prevdistance = distance;
    while(distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2) > 1){
      float error = distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2);
      float speed = error * kP * speedMultiplyer + 1;
      LeftFront.spin(fwd, speed, pct);
      RightFront.spin(fwd, speed, pct);
      LeftBack.spin(fwd, speed, pct);
      RightBack.spin(fwd, speed, pct);
    }
    LeftFront.stop();
    RightFront.stop();
    LeftBack.stop();
    RightBack.stop();
  }
    float prevAngle;
    bool rightleft;
    bool speed;
    bool speedfp;
    void drivefwg (float distanceB, float speedMultiplyer){ //what are your variables 
      float kP = 0.3;
      float distanceA = distanceB * 28.66;
      float distance = distanceA + prevdistance;
      prevdistance = distance;
      float angleA = prevAngle;
      while(distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2) > 1){
        float error = distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2);
        float speedP = error * kP * speedMultiplyer + 1;
        float speed = 0.0;
        if((Inertial.rotation(deg) + 0.5 < angleA) or (Inertial.rotation(deg) - 0.5 > angleA)){
      if ( Inertial.rotation(deg) < angleA){
          if(Inertial.rotation(deg) < angleA){
            speed = angleA - Inertial.rotation(deg) + 2;
            speedfp = speed;
            LeftFront.spin(fwd, speedP + speed, pct);
            RightFront.spin(fwd, speedP -speed, pct);
            LeftBack.spin(fwd, speed + speed, pct);
            RightBack.spin(fwd, speed - speed, pct);
            rightleft = true;
          }
      } else {
        if(Inertial.rotation(deg) > angleA){
            speed = angleA - Inertial.rotation(deg) - 2;
            speedfp = speed;
            LeftFront.spin(fwd, speedP + speed, pct);
            RightFront.spin(fwd, speedP -speed, pct);
            LeftBack.spin(fwd, speed + speed, pct);
            RightBack.spin(fwd, speed - speed, pct);
            rightleft = false;
          }
      }

      LeftFront.spin(fwd, speed, pct);
      RightFront.spin(fwd, speed, pct);
      LeftBack.spin(fwd, speed, pct);
      RightBack.spin(fwd, speed, pct);
    }
    LeftFront.stop();
    RightFront.stop();
    LeftBack.stop();
    RightBack.stop();
  }
  }


  void driveIntakes (float distanceB, float speedMultiplyer, float intakedistance){
    float kP = 0.3;
    float distanceA = distanceB * 28.66;
    float distance = distanceA + prevdistance;
    prevdistance = distance;
    while(distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2) > 1){
      float error = distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2);
      float speed = error * kP * speedMultiplyer + 1;
      LeftFront.spin(fwd, speed, pct);
      RightFront.spin(fwd, speed, pct);
      LeftBack.spin(fwd, speed, pct);
      RightBack.spin(fwd, speed, pct);
      if(Grabby.position(degrees) < intakedistance){
        Grabby.spin(forward, 100, pct);
      }
    }
    Grabby.stop();
    LeftFront.stop();
    RightFront.stop();
    LeftBack.stop();
    RightBack.stop();
  }
  void driver (float distanceB, float speedMultiplyer){
    float kP = 0.3;
    float distanceA = distanceB * -28.66;
    float distance = distanceA + prevdistance;
    prevdistance = distance;
    while(distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2) < -1){
      float error = distance - ((LeftFront.position(degrees) + RightBack.position(degrees)) /2);
      float speed = error * kP * speedMultiplyer + -1;
      LeftFront.spin(fwd, speed, pct);
      RightFront.spin(fwd, speed, pct);
      LeftBack.spin(fwd, speed, pct);
      RightBack.spin(fwd, speed, pct);
    }
    LeftFront.stop();
    RightFront.stop();
    LeftBack.stop();
    RightBack.stop();
  }


  void printC(){
    while(true){

    wait(0.5, seconds);
    //Controller1.Screen.print("speed: %f", speedfp);
    }
  }

}
  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...


/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void){
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
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

void usercontrol(void){
  // User control code here, inside the loop
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
}

//
// Main will set up the competition functions and callbacks.
//
int main(){
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
