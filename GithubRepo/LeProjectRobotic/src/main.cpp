/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Student                                          */
/*    Created:      Sat Sep 18 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftBack             motor         11              
// LeftFront            motor         4               
// RightBack            motor         20              
// RightFront           motor         10              
// Inertial             inertial      7               
// Lift                 motor_group   1, 2            
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;


void moveForward(int degreers){
    //Left_Motor_.resetRotation();
    LeftBack.resetRotation();
    RightBack.resetRotation();
    while (LeftBack.position(degrees)<360){
      LeftBack.spin(fwd);
      RightBack.spin(fwd);
    }

    LeftBack.stop();
    RightBack.stop();
    

    
}

void Turn_Right(int degreess){
    LeftBack.resetRotation();
    LeftFront.resetRotation();
    RightBack.resetRotation();
    RightFront.resetRotation(); 

    while (Inertial.rotation(degrees) <degreess ){
        RightBack.spin(reverse, 50, pct);
        LeftBack.spin(forward, 50, pct);
    }
        RightBack.stop();
        RightFront.stop();
        LeftBack.stop();
        LeftFront.stop();
}
int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial.calibrate();
  this_thread::sleep_for(1000);
  moveForward(360);
  Turn_Right(90);
  
}
