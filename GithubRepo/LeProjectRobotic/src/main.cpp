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

void moveWheel(int Rightamount, int Leftamount) {
    RightFront.spinFor(forward,Rightamount,degrees);
    RightBack.spinFor(forward,Rightamount,degrees);
    LeftFront.spinFor(forward,Leftamount,degrees);
    LeftBack.spinFor(forward,Leftamount,degrees);
     
  }

void moveLift(int liftAmount, int ZeroIsFwd) {
    if (ZeroIsFwd == 0){
      Lift.spinFor(forward,liftAmount,degrees);
    }else{
      Lift.spinFor(reverse,liftAmount,degrees);
    }
  }
  


void TurnLeft() {
    RightFront.spin(forward);
    RightBack.spin(forward);
    LeftFront.spin(reverse);
    LeftBack.spin(reverse);
     
     
  }
void TurnRight() {
    RightFront.spin(reverse);
    RightBack.spin(reverse);
    LeftFront.spin(forward);
    LeftBack.spin(forward);
     
     
  }
  void EverythingStop(){
    RightFront.stop();
    RightBack.stop();
    LeftFront.stop();
    LeftBack.stop();
  }
  void StopLift(){
    Lift.stop();
  }

void turn(int amount){
  if (amount>0){
    while(amount>Inertial.rotation(degrees)){
      TurnRight();
    }
    EverythingStop();
  } else {
    while(amount<Inertial.rotation(degrees)){
      TurnLeft(); }
    EverythingStop();
  }
    
}


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();


  moveWheel(360, 360);
  turn(90);
  moveLift(0,180);
  wait(1000,seconds);
  moveLift(1,180);
  
}
