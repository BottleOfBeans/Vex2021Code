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

void Turn_Right(int degs){
  Inertial.setRotation(0, degrees);
  double kP = 1.1;
  
  while(true) {
    double Angle = Inertial.angle(deg);
    double Power;
    if(degs > 0)
    {
      Power = (degs - Angle) * kP;
    }
    else if (degs < 0)
    {
      Power = (degs + Angle) * kP;
    }

    while(abs(degs) > fabs(Angle) - 5)
    {
      LeftBack.spin(vex::directionType::rev, Power, pct);
      RightBack.spin(fwd, Power, pct);
      
    }
    LeftBack.stop();
    RightBack.stop();
    
  }
}



int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  Inertial.calibrate();
  Inertial.setRotation(0, degrees);

  this_thread::sleep_for(1000);
  moveForward(360);
  Turn_Right(90);
  
}
