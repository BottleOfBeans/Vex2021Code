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
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;

void moveWheel(int rightAmount, int leftAmount) {
    RightFront.spinFor(forward,Rightamount,degrees);
    RightBack.spinFor(forward,Rightamount,degrees);
    LeftFront.spinFor(forward,Leftamount,degrees);
    LeftBack.spinFor(forward,Leftamount,degrees);
     
  }
void turn(int amount){
  if (amount>90){
    RightFront
  }
}

int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  
  
  vexcodeInit();
  
}
