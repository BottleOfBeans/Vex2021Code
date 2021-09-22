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
// Controller1          controller                    
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
using namespace vex;
void DriverCode(){
    while(true){
        
        int lM = Controller1.Axis3.position(percent) + Controller1.Axis4.position(percent);
        int rM = Controller1.Axis3.position(percent) - Controller1.Axis4.position(percent);

        if ( (lM)>100)lM = 100;
        if ( (lM)<-100)lM = -100;
        
        if ( (rM)>100)rM = 100;
        if ( (rM)<-100)rM = -100;
        
        LeftBack.spin(fwd, lM,  pct);
        RightBack.spin(fwd, rM,  pct);
        LeftFront.spin(fwd, lM,  pct);
        RightFront.spin(fwd, rM,  pct);
    
      }
    }
void AutoCode(){
  
}




int main() {
  // Initial`();
  Inertial.calibrate();
  Inertial.setRotation(0, degrees);
  this_thread::sleep_for(1000);

  //Code After Here  
  DoThis();

}
