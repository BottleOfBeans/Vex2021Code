/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       joe                                                       */
/*    Created:      Sat Sep 18 2021                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// LeftFrontBack             motor         11              
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
void DriveTurn(int degs){
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
      LeftBack.spin(reverse, Power, pct);
      RightBack.spin(fwd, Power, pct);
      LeftFront.spin(reverse, Power, pct);
      RightFront.spin(fwd, Power, pct);
    }
    LeftBack.stop();
    RightBack.stop();
    LeftFront.stop();
    RightFront.stop();
  }
}

void DriveForward(double inches) {
  LeftFront.resetPosition();
  RightFront.resetPosition();

  double targetDeg = (inches*360)/(4*3.1415); //4 inch wheel??

  double leftVal = LeftFront.position(degrees);
  double rightVal = RightFront.position(degrees);

  double leftlastErr = targetDeg - leftVal;
  double rightlastErr = targetDeg - rightVal;

  double leftErr = 0;
  double rightErr = 0;

  double leftPower = 0;
  double rightPower = 0;

  double leftInt = leftErr;
  double rightInt = rightErr;

  double leftDeriv = leftlastErr - leftErr;
  double rightDeriv = rightlastErr - rightErr;

  double leftKp = 1;
  double leftKi = 1;
  double leftKd = 1;

  double rightKp = 1;
  double rightKi = 1;
  double rightKd = 1;

  int dT = 10;
  while (true) {
    leftVal = LeftFront.position(degrees);
    rightVal = RightFront.position(degrees);

    leftErr = targetDeg - leftVal;
    rightErr = targetDeg - rightVal;

    if (fabs(leftErr) < 5 && fabs(rightErr) < 5) {
      break;
    }

    leftInt += (leftErr/dT);
    rightInt +=  (rightErr/dT);

    leftDeriv = leftErr - leftlastErr;
    rightDeriv = rightErr - rightlastErr;

    leftPower = (leftErr * leftKp) + (leftInt * leftKi) - (leftDeriv * leftKd);
    rightPower = (rightErr * rightKp) + (rightInt * rightKi) - (rightDeriv * rightKd);

    LeftFront.spin(forward, leftPower, pct);
    LeftBack.spin(forward, leftPower, pct);
    RightFront.spin(forward, rightPower, pct);
    RightBack.spin(forward, rightPower, pct);

    leftlastErr = leftErr;
    rightlastErr = rightErr;
  }
  LeftFront.stop();
  RightFront.stop();
  LeftBack.stop();
  RightBack.stop();
}


void AutoCode(){
  //DriveForward() is in inches
  //DriveTurn is in Degrees
  DriveForward(4);
  DriveTurn(30);

}


int main() {
  // Initial`();
  Inertial.calibrate();
  Inertial.setRotation(0, degrees);
  this_thread::sleep_for(1000);

  //Code After Here  
  

}