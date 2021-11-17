/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       VEX                                                       */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
// ---- START VEXCODE CONFIGURED DEVICftES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]ft
// Controller1          controller                    
// Drivetrain           drivetrain    12, 11, 16, 13, 14
// Lift                 motor         4               
// LeftIntake           motor         3               
// RightIntake          motor         8               
// Tray                 motor         18              
// TrayPot              pot           A               
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

auto vel = vex::velocityUnits::pct;
auto forw = vex::directionType::fwd;

int printSensorValues()
{
  while(true)
  {
    Brain.Screen.printAt(50, 50, "Lift: %f",TrayPot.value(rotationUnits::deg));
    Brain.Screen.printAt(50, 150, "Tray: %f", Tray.rotation(rotationUnits::rev));
    Brain.Screen.printAt(50, 200, "Gyro: %f",TurnGyroSmart.rotation());
    Brain.Screen.printAt(50, 100, "Line Sensor %d", lineSensor.value(analogUnits::pct));

   // Brain.Screen.printAt(50, 150, "Right: %f",RightPot.value(rotationUnits::deg));
    task::sleep(50);        
  }
  return 0;
}


double targetLift = 0;
bool liftAtTarget = false;
bool liftPIDEnabled = false;
double powPercentLift = 1;
int liftPIDTask()
{
  double kp = 3, ki = 0.0, kd = 0;
  double P = 0, I = 0, D = 0;
  double error, lastError = 0;
  double motorSpeed = 0; 
  double prevTarget = targetLift;
    remote.rumble(" cfffffffdsa-.-.-");

  while(true)
  {
    if(targetLift != prevTarget)
    {
      liftAtTarget = false;
      I = 0;
    }
    prevTarget = targetLift;
    error = TrayPot.value(rotationUnits::deg) - targetLift;
//Brain.Screen.printAt( 50, 50, "%f",error);    
    P = kp * error;
    D = kd*(error - lastError);
    I += ki * (error);
    lastError = error;
    motorSpeed = P + I +D;
    motorSpeed *= powPercentLift;
    if(liftPIDEnabled)
    {
      if(fabs(motorSpeed) < 1)
      {
        Lift.stop(brakeType::hold);
      //  RightLift.stop(brakeType::hold);      
        liftAtTarget = true;
      }else{
        Lift.spin(directionType::fwd, -motorSpeed, velocityUnits::pct);
        //RightLift.spin(directionType::fwd, motorSpeed, velocityUnits::pct);
      }
    }
    task::sleep(10);
  }
  return 0;
}

void turnTo(double angle)
{
  double kp = .4, kd = .0, ki = 0;
  double P=0, I=0, D = 0;
  double lastError = angle - TurnGyroSmart.rotation(rotationUnits::deg);
  int sign = 1;
  while(true)
  {
    double modangle = TurnGyroSmart.rotation(rotationUnits::deg);
    //if(angle > 180 && modangle < 180) modangle = 360+modangle;
    
    double error = angle - modangle;  
    P = error * kp;
    I += error * ki;
    D = (error - lastError) * kd;  
    lastError = error;

    LeftFront.spin(directionType::fwd, P + I + D, percentUnits::pct);
    RightFront.spin(directionType::rev, P + I + D, percentUnits::pct);
    RightBack.spin(directionType::rev, P + I + D, percentUnits::pct);
    LeftBack.spin(directionType::fwd, P + I + D, percentUnits::pct);  
    if(abs(P + I + D) < 1 && abs(D) < 1 && abs(P) < 1)      
    {
      LeftFront.stop(brakeType::brake);
            RightFront.stop(brakeType::brake);
                  LeftBack.stop(brakeType::brake);
                        RightFront.stop(brakeType::brake);
    LeftFront.spin(directionType::rev, 0, percentUnits::pct);
    RightFront.spin(directionType::fwd, 0, percentUnits::pct);
    RightBack.spin(directionType::fwd, 0, percentUnits::pct);
    LeftBack.spin(directionType::rev, 0, percentUnits::pct);
    return;        
    }
  }

}

bool stackingMacroOverride = true;
bool stackingStart = true;

int stackingMacro(bool lots = true)
{
  stackingStart = true;
  LeftIntake.spin(directionType::fwd, -20, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -20, percentUnits::pct); 
  while(lineSensor.value(analogUnits::pct) > 65)
    task::sleep(20);
  task::sleep(400);
  LeftIntake.spin(directionType::fwd, -0, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -0, percentUnits::pct);            
  task::sleep(100);
  Tray.setVelocity(100, percentUnits::pct);
  Tray.rotateTo(-1.05, rotationUnits::rev, true);
  Tray.setVelocity(45, percentUnits::pct); 
  if(lots)
   Tray.rotateTo(-3.95, rotationUnits::rev, true)  ;
  else
       Tray.rotateTo(-3.4, rotationUnits::rev, true)  ;
  remote.rumble("-.--");
  task::sleep(400);
  LeftIntake.spin(directionType::fwd, -40, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -40, percentUnits::pct);
  task::sleep(250);
  Drivetrain.driveFor(directionType::fwd, -10, distanceUnits::in);
  
  Tray.stop();
  stackingStart = false;
  return 0;
}

int stackingMacroAuton()
{
  stackingStart = true;
  LeftIntake.spin(directionType::fwd, -50, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -50, percentUnits::pct); 
  
  task::sleep(1200);
  LeftIntake.spin(directionType::fwd, -0, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -0, percentUnits::pct);            
  //task::sleep(100);
  Tray.setVelocity(50, percentUnits::pct);
  
   Tray.rotateTo(-3.2, rotationUnits::rev, true)  ;

//  remote.rumble("-.--");
  task::sleep(150);
  LeftIntake.spin(directionType::fwd, -40, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -40, percentUnits::pct);
  task::sleep(150);
  Drivetrain.setDriveVelocity(100, percentUnits::pct);
  Drivetrain.driveFor(directionType::fwd, -10, distanceUnits::in);
  
  Tray.stop();
  stackingStart = false;
  return 0;
}


bool trayInUse = false;
double trayTarget = 0;
int trayControl()
{
  trayInUse = true;
  Tray.rotateTo(2., rotationUnits::rev);
  Tray.rotateTo(2.22, rotationUnits::rev);
  trayInUse = false;  
  return 0;
}



int remoteControl()
{
  trayInUse = true;
  //task macro(stackingMacro);
  //task trayTask(trayControl);
  while(true)
  {
    if(true)//abs(remote.Axis2.value()) > 5 || abs(remote.Axis3.value()) > 5)
    {
      stackingMacroOverride = false;
      
      LeftFront.spin(fwd, remote.Axis3.value(), percentUnits::pct);
      LeftBack.spin(fwd, remote.Axis3.value(), percentUnits::pct);    
      RightBack.spin(fwd, remote.Axis2.value(), percentUnits::pct);
      RightFront.spin(fwd, remote.Axis2.value(), percentUnits::pct);    
    }else if (!stackingMacroOverride) {
    
      LeftFront.stop();
      LeftBack.stop();    
      RightBack.stop();
      RightFront.stop();        
    }

    if(remote.ButtonL1.pressing())
    {
      liftPIDEnabled = false;
      Lift.spin(forw, 75, vel);
      //RightLift.spin(forw, 100, vel);      
    }else if(remote.ButtonL2.pressing())
    {
      liftPIDEnabled = false;
      trayInUse = true;
      Lift.spin(forw, -75, vel);
      task::sleep(320);
      Tray.rotateTo(0, rotationUnits::rev, false);
      //RightLift.spin(forw, -100, vel);       
    }else if(remote.ButtonX.pressing())
    {
      LeftIntake.spin(directionType::fwd, -20, percentUnits::pct);
      RightIntake.spin(directionType::fwd, -20, percentUnits::pct); 
      while(lineSensor.value(analogUnits::pct) > 65)
        task::sleep(20);
      task::sleep(400);
      LeftIntake.spin(directionType::fwd, -0, percentUnits::pct);
      RightIntake.spin(directionType::fwd, -0, percentUnits::pct);
      liftPIDEnabled = true;
      Tray.setVelocity(100, percentUnits::pct);
      Tray.rotateTo(-1.9, rotationUnits::rev, false);   
      task::sleep(150);
      liftPIDEnabled = true;
      targetLift = 63.48; 
    }else if(remote.ButtonA.pressing())
    {
      LeftIntake.spin(directionType::fwd, -20, percentUnits::pct);
      RightIntake.spin(directionType::fwd, -20, percentUnits::pct); 
      while(lineSensor.value(analogUnits::pct) > 65)
        task::sleep(20);
      task::sleep(400);
      LeftIntake.spin(directionType::fwd, -0, percentUnits::pct);
      RightIntake.spin(directionType::fwd, -0, percentUnits::pct);
      Tray.setVelocity(100, percentUnits::pct);
      Tray.rotateTo(-1.9, rotationUnits::rev, false);   
      task::sleep(150);
      liftPIDEnabled = true;
      targetLift = 40.2; 
    
    }else if(remote.ButtonY.pressing())
    {
        liftPIDEnabled = true;
      Tray.setVelocity(100, percentUnits::pct);
      Tray.rotateTo(-1.9, rotationUnits::rev, false);   
      task::sleep(150);
      liftPIDEnabled = true;
      targetLift = 60.48; 
    }
    else if(!liftPIDEnabled){
      Lift.stop(brakeType::hold);
      //RightLift.stop(brakeType::hold);      
    }

    if(remote.ButtonR2.pressing())
    {
      stackingMacroOverride = false;
      LeftIntake.spin(forw, 100, vel);
      RightIntake.spin(forw, 100, vel);      
    }else if(remote.ButtonR1.pressing())
    {
      stackingMacroOverride = false;    
      LeftIntake.spin(forw, -50, vel);
      RightIntake.spin(forw, -50, vel);       
    }else if(!stackingMacroOverride) {
      LeftIntake.stop(brakeType::hold);
      RightIntake.stop(brakeType::hold);      
    }
    if(remote.ButtonUp.pressing())
    {
      stackingMacroOverride = false;
      trayInUse = false;     
      Tray.spin(fwd, -100, percentUnits::pct);
      //TrayRight.spin(fwd, 40, percentUnits::pct);
      
      
    }else if(remote.ButtonDown.pressing())
    {
      stackingMacroOverride = false;
      trayInUse = false;      
      Tray.spin(fwd, 100, percentUnits::pct);
      //TrayRight.spin(fwd, -40, percentUnits::pct);      
    }else if(remote.ButtonLeft.pressing()){ 
      //trayTask = task(trayControl);
    }else if(!trayInUse && !stackingMacroOverride){// if(!trayPIDEnabled) {
      Tray.stop(brakeType::hold);
      
      //TrayRight.stop(brakeType::hold);      
    }//else if(trayPIDEnabled && targetTray == 220 && trayAtTarget)
    //{
     // targetTray = 202;
    //}
    if(remote.ButtonRight.pressing())
    {
      stackingMacro();
          //  macro = task(stackingMacro);
     //     macro.resume();
      stackingStart = true;
     // task::sleep(10);
     //macro.resume();
    }else {
      //macro.stop();
    // macro.suspend();
      stackingStart = false;
    }


    task::sleep(50);
  }
}


int sgn(double val)
{
  if(val > 0) return 1;
  return -1;
}

void drive(int direction, double inches, double heading, double completeTime = 5000, double maxSpeed = 100) // direction: 0 forward, -1 backward, 2 strafe left, -2 strafe right
{
  double target = inches / (3.1415 * 4);
  //target /= 0.707106781;
  target *= 360*2;
  LeftFront.resetRotation();
  double kp = .37, ki = 0, kd = .3;
  
  double P = 0, I = 0, D = 0;
  double error, lastError = 0;
  double motorSpeed = 0;
  
  Brain.Timer.clear();
  while(true)//(Brain.Timer.time(timeUnits::msec) < completeTime)
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
      motorSpeed = sgn(motorSpeed) * maxSpeed;
    }
    if(fabs(error) < .2 && fabs(lastError) < .2)
      motorSpeed = 0;
    //Brain.Screen.printAt(50, 10, "%f", error);
    //Brain.Screen.printAt(150, 10, "%f", angle);
        
    double anglePower = 0;
    if(fabs(motorSpeed) > 1)
    {
       anglePower = 0;//(heading - angle);
    }

    LeftFront.spin(directionType::fwd, motorSpeed , percentUnits::pct);
     LeftBack.spin(directionType::fwd, motorSpeed , percentUnits::pct);   
    RightFront.spin(directionType::fwd, motorSpeed+anglePower, percentUnits::pct);
  RightBack.spin(directionType::fwd, motorSpeed+anglePower, percentUnits::pct);
    
    if(fabs(motorSpeed) < 1)
      break;
    task::sleep(20);
  }
  LeftBack.stop(brakeType::hold);
  LeftFront.stop(brakeType::hold);
  RightFront.stop(brakeType::hold);
  RightBack.stop(brakeType::hold);  

}

void turnRight(double degrees)
{
  double rots = 11.5 * (degrees/360.0);
  //rots /= 2;
  rots /= (4);
  LeftBack.startRotateFor(directionType::fwd, rots, rotationUnits::rev, 40, velocityUnits::pct);
  LeftFront.startRotateFor(directionType::fwd, rots, rotationUnits::rev, 40, velocityUnits::pct);  
  RightBack.startRotateFor(directionType::fwd, -rots, rotationUnits::rev, 40, velocityUnits::pct);  
  RightFront.rotateFor(directionType::fwd, -rots, rotationUnits::rev, 40, velocityUnits::pct);    
}

void turnLeft(double degrees)
{
  double rots = 11.5 * (degrees/360.0);
//  rots /= 2;
 rots /= (4);//*3.1415);
  LeftBack.startRotateFor(directionType::fwd, -rots, rotationUnits::rev, 40, velocityUnits::pct);
  RightFront.startRotateFor(directionType::fwd, rots, rotationUnits::rev,40, velocityUnits::pct);  
  LeftBack.startRotateFor(directionType::fwd, -rots, rotationUnits::rev, 40, velocityUnits::pct);
  RightBack.rotateFor(directionType::fwd, rots, rotationUnits::rev, 40, velocityUnits::pct);  

}
// .61

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
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

void flipOut()
{
 // drive(1, 3, 0, 0, 100); 
 // Drivetrain.0setDriveVelocity(100, percentUnits::pct); 
//  Drivetrain.driveFor(directionType::fwd, 3, distanceUnits::in);
//  Lift.stop(brakeType::brake);
  
  //Tray.rotateTo(0, rotationUnits::rev, true);  
  //liftPIDEnabled = true;
 LeftIntake.spin(directionType::rev, 100, percentUnits::pct);
 RightIntake.spin(directionType::rev, 100, percentUnits::pct); 
 task::sleep(500);
 LeftIntake.spin(directionType::rev, 0, percentUnits::pct);
 RightIntake.spin(directionType::rev, 0, percentUnits::pct);
 task::sleep(300);  
}

void matchAuton2()
{
    Lift.stop(brakeType::hold);
  drive(1, 6, 0, 0, 40);
  Tray.setVelocity(100, percentUnits::pct);
  Tray.rotateTo(3.6, rotationUnits::rev, true);  
  drive(1, -3, 0, 0, 40);  
  //turnTo(0);
  Tray.rotateTo(0, rotationUnits::rev, true);  
  //turnTo(0);
  Tray.rotateTo(0, rotationUnits::rev, true);  
  //flipOut();
  LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
  RightIntake.spin(directionType::fwd, 100, percentUnits::pct);
 // drive(1, -2, 0, 0, 40);
  drive(1, 32, 0, 0, 60);
  task::sleep(300);
  turnTo(360-147); //142
  drive(1, 21,0 ,0, 50);
  turnTo(360-(140-50));
  drive(1, 4, 0, 0, 40);
  LeftIntake.spin(directionType::fwd, -100, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -100, percentUnits::pct);    
  task::sleep(500);
  LeftIntake.spin(directionType::fwd, -10, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -10, percentUnits::pct); 
   Tray.setVelocity(75, percentUnits::pct); 
  Tray.rotateTo(7.45, rotationUnits::rev)  ;

  LeftIntake.spin(directionType::fwd, -100, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -100, percentUnits::pct);
  //Tray.rotateTo(7.3, rotationUnits::rev);
  Drivetrain.driveFor(directionType::fwd, -10, distanceUnits::in);
  LeftIntake.spin(directionType::fwd, -0, percentUnits::pct);
  RightIntake.spin(directionType::fwd, -0, percentUnits::pct);

}

void matchAuton()
{
  Lift.stop(brakeType::brake);
  flipOut();
  //liftPIDEnabled = true;
  //targetLift = 0.0;
  //return;
  LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
  RightIntake.spin(directionType::fwd, 100, percentUnits::pct);
  drive(1, 20, 0, 0, 40);
  
//  Drivetrain.driveFor(39, distanceUnits::in, 40, velocityUnits::pct);
  //Drivetrain.turnToHeading(90, rotationUnits::deg);
  turnTo(90);
  //return; 
 //Drivetrain.turnFor(90, rotationUnits::deg, 10, velocityUnits::pct);
  drive(1, 30, 0, 0, 100);
 // Drivetrain.driveFor(60, distanceUnits::in, 60, velocityUnits::pct);
//Drivetrain.turnFor(210, rotationUnits::deg, 10, velocityUnits::pct);
  //return;
  turnTo(140);
 
  drive(1, 25, 0, 0, 100);
 // Drivetrain.driveFor(24, distanceUnits::in, 60, velocityUnits::pct);
       LeftIntake.spin(forw, -50, vel);
      RightIntake.spin(forw, -50, vel);
      task::sleep(250);
     // LeftIntake.spin(forw, 20, vel);
     // RightIntake.spin(forw, 20, vel);   
     stackingStart = true;
     stackingMacro();
}


void onePoint()
{
  Drivetrain.driveFor(directionType::fwd, -10, distanceUnits::in);
  Drivetrain.driveFor(directionType::fwd, 10, distanceUnits::in); 
  Tray.setVelocity(100, percentUnits::pct);
  Tray.rotateTo(3, rotationUnits::rev, true);  
  drive(1, -3, 0, 0, 40);  
  //turnTo(0);
  flipOut();
  Tray.rotateTo(0, rotationUnits::rev, true);  
  //turnTo(0);
  Tray.rotateTo(0, rotationUnits::rev, true);  
 
}

void frontAuton()
{
 drive(1, 7, 0, 0,50);
  drive(1, -3, 0,0,50);
     flipOut();
    // turnTo(0); 
  //return;
  Lift.spin(directionType::fwd, -20, percentUnits::pct);
 // Lift.stop(brakeType::brake);

  LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
   RightIntake.spin(directionType::fwd, 100, percentUnits::pct); 
  drive(1, 9, 0, 5000, 40);
  turnTo(-90);
  drive(1, 12, 0, 0, 40);
  turnTo(-140);
  drive(1, 5, 0,0, 50);
  //onePoint();
  stackingMacro(false); 
}

void wallAuton()
{
Lift.spin(directionType::fwd, -20, percentUnits::pct); 
 LeftIntake.spin(directionType::fwd, -50, percentUnits::pct);
   RightIntake.spin(directionType::fwd, -50, percentUnits::pct);
   task::sleep(600);
  //Tray.rotateTo(-1.5, rotationUnits::rev, true);
    //task::sleep(1000); 
    //Tray.rotateTo(0, rotationUnits::deg, true);
//task::sleep(1000);
 LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
   RightIntake.spin(directionType::fwd, 100, percentUnits::pct); 

  turnTo(30);
  drive(1,11,0,0,50);
  drive(1,-9,0,0,50);  
  turnTo(-30);
  drive(1,10,0,0,50);  
  drive(1,-8,0,0,50); 
  turnTo(-90); 
    drive(1,8,0,0,50);
  stackingMacroAuton();
  Tray.rotateTo(0, rotationUnits::rev, false);
  LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
   RightIntake.spin(directionType::fwd, 100, percentUnits::pct); 
  turnTo(-10);
  drive(1,24,0,0,50);
  turnTo(45);

}

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ..........................................................................
  task print(printSensorValues);
  //task tray(trayPIDTask);
  task lift(liftPIDTask);
  //onePoint();
 
   Lift.spin(directionType::fwd, -20, percentUnits::pct); 
 LeftIntake.spin(directionType::fwd, -50, percentUnits::pct);
   RightIntake.spin(directionType::fwd, -50, percentUnits::pct);
   task::sleep(1000);
  //Tray.rotateTo(-1.5, rotationUnits::rev, true);
    //task::sleep(1000); 
    //Tray.rotateTo(0, rotationUnits::deg, true);
//task::sleep(1000);
 LeftIntake.spin(directionType::fwd, 100, percentUnits::pct);
   RightIntake.spin(directionType::fwd, 100, percentUnits::pct); 

  turnTo(0);
  // return;
  drive(1, 18, 0, 0, 70); 
  turnTo(-20);
  drive(1,10,0,0,40);
  turnTo(0);
  drive(1,-21,0,0,50);
  turnTo(90);
  drive(1,7,0,0,50);
  stackingMacro();
  return;
  turnTo(-30);
  drive(1, -20, 0,0,100);
  turnTo(0);
  drive(1, 24, 0,0,50);
  Tray.setVelocity(60, percentUnits::pct);
  Tray.rotateTo(-1, rotationUnits::rev, false);
  drive(1, -24, 0,0,100);
  task::sleep(50);
  turnTo(90);
  drive(1,6,0,0,100);
  stackingMacroAuton();
  //matchAuton2();
  return;
  //return;
  flipOut();
  return;
  Tray.setVelocity(100, percentUnits::pct);
  Tray.rotateTo(2, rotationUnits::rev, true);
  liftPIDEnabled = true;
  targetLift = 66.1;
  while(!liftAtTarget) task::sleep(50);
 // while(true) task::sleep(500);
  //task::sleep(5000);
  //return 0;
 // task::sleep(5000);
 // remoteControl();
  
  //Drivetrain.driveFor(directionType::fwd, 30, distanceUnits::in);
  
  
  
  
  
  
  
  
  
  drive(1, 20, 0, 0, 50);
      LeftIntake.spin(forw, -50, vel);
      RightIntake.spin(forw, -50, vel);
      task::sleep(500);


  drive(1, -20, 0, 0, 50);
  targetLift = 1;
  while(!liftAtTarget) task::sleep(50);      
  Tray.rotateTo(0, rotationUnits::rev, true);
 // Drivetrain.turnFor(-50, rotationUnits::deg);
  turnLeft(50); 
  Lift.stop(brakeType::hold);    
//  return;   
 // while(true)
 // {
  //  task::sleep(200);
  //}
  //drive(1, 48, 0, 5000, 100);*/
  liftPIDEnabled = true;
  targetLift = 0;
  task::sleep(1000);
    Tray.rotateTo(0, rotationUnits::rev, true);

  //while(!liftAtTarget) task::sleep(50);
      LeftIntake.spin(forw, 100, vel);
      RightIntake.spin(forw, 100, vel);  
    drive(1, 24, 0, 0, 50);
    //Drivetrain.d(directionType::fwd, 96, distanceUnits::in);

  Drivetrain.turnToHeading(51, rotationUnits::deg, 10, velocityUnits::pct);
//  Drivetrain.turnFor(45, rotationUnits::deg);
  Drivetrain.driveFor(directionType::fwd, 36, distanceUnits::in);
  //turnRight(80);
      LeftIntake.spin(forw, 0, vel);
      RightIntake.spin(forw, -0, vel); 
      Tray.setVelocity(50, percentUnits::pct); 
  Tray.rotateTo(6, rotationUnits::rev);
      LeftIntake.spin(forw, -50, vel);
      RightIntake.spin(forw, -50, vel);  
      Drivetrain.driveFor(directionType::fwd, -20, distanceUnits::in);
 // drive(-1, 20, 0, 5000, 40);
  //targetTray = 222;
  while(true)
  {
    task::sleep(200);
  }

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
// 7
void usercontrol(void) {
  // User control code here, inside the loop
  //autonomous();
  task print(printSensorValues);
  //task tray(trayPIDTask);
  task lift(liftPIDTask);
  //remoteControl();
 // stackingMacro();
  pre_auton();
 // turnTo(-110);
  //turnTo(90);
 autonomous();
 //return;

 //while(true) task::sleep(10);
// turnTo(90);
//  remoteControl();
 return;
 // return;
  pre_auton();
 // autonomous();
 //turn1To(45);
  matchAuton2();
 // flipOut();
  //stackingMacro();
   //while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................

   // wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  //}
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
