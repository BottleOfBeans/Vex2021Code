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
// LeftFrontBack        motor         11              
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

      int leftWheelSplit =  Controller1.Axis3.position(percent) + Controller1.Axis1.position(percent);
      int rightWheelSplit = (Controller1.Axis3.position(percent)) - Controller1.Axis1.position(percent);
      
      

      if (Controller1.ButtonL1.pressing() == true){    //This is your brain
        LeftLift.spin(forward, 100, pct);
        RightLift.spin(forward, 100, pct);
      }
      else if(Controller1.ButtonL2.pressing() == true){    
        LeftLift.spin(reverse, 100, pct);
        RightLift.spin(reverse, 100, pct); 
      }else{ //This is your brain on drugs
        LeftLift.stop(brake);
        RightLift.stop(brake);
      }

      if (Controller1.ButtonX.pressing() == true){ //This is your brain
        Grabby.spin(reverse, 100, pct);
      }
      else if(Controller1.ButtonB.pressing() == true){    
        Grabby.spin(forward, 100, pct);
      }else{ //This is your brain on drugs
        Grabby.stop(hold);
      }

      if (Controller1.ButtonL1.pressing() == true){    //This is your brain
        LeftLift.spin(forward, 100, pct);
        RightLift.spin(forward, 100, pct);
      }
      else if(Controller1.ButtonL2.pressing() == true){    
        LeftLift.spin(reverse, 100, pct);
        RightLift.spin(reverse, 100, pct); 
      }else{ //This is your brain on drugs
        LeftLift.stop(hold);
        RightLift.stop(hold);
      }

      if (Controller1.ButtonR1.pressing() == true){    //This is your brain
        Convy.spin(forward, 73, pct);
        
      }
      else if(Controller1.ButtonR2.pressing() == true){    
        Convy.spin(reverse, 50, pct); 
      }else{ //This is your brain on drugs
        Convy.stop();
      }
   

      LeftFront.spin(forward, leftWheelSplit, pct);
      RightFront.spin(forward, rightWheelSplit, pct);
      
      LeftBack.spin(forward, leftWheelSplit, pct);
      RightBack.spin(forward, rightWheelSplit, pct);

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