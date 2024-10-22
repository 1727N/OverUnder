#include "vex.h"
#include <iostream>
#include <string>

using namespace vex;
competition Competition;

/*---------------------------------------------------------------------------*/
/*                             VEXcode Config                                */
/*                                                                           */
/*  Before you do anything else, start by configuring your motors and        */
/*  sensors using the V5 port icon in the top right of the screen. Doing     */
/*  so will update robot-config.cpp and robot-config.h automatically, so     */
/*  you don't have to. Ensure that your motors are reversed properly. For    */
/*  the drive, spinning all motors forward should drive the robot forward.   */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*                             JAR-Template Config                           */
/*                                                                           */
/*  Where all the magic happens. Follow the instructions below to input      */
/*  all the physical constants and values for your robot. You should         */
/*  already have configured your robot manually with the sidebar configurer. */
/*---------------------------------------------------------------------------*/
enum difficulty
{
  Easy = 0,
  Normal = 1,
  Hard = 2,
  Insane = 3,
  Crazy = 4,
  Impossible = 5


};

Drive chassis(

//Specify your drive setup below. There are seven options:
//ZERO_TRACKER_NO_ODOM, ZERO_TRACKER_ODOM, TANK_ONE_ENCODER, TANK_ONE_ROTATION, TANK_TWO_ENCODER, TANK_TWO_ROTATION, HOLONOMIC_TWO_ENCODER, and HOLONOMIC_TWO_ROTATION
//For example, if you are not using odometry, put ZERO_TRACKER_NO_ODOM below:
ZERO_TRACKER_NO_ODOM,

//Add the names of your Drive motors into the motor groups below, separated by commas, i.e. motor_group(Motor1,Motor2,Motor3).
//You will input whatever motor names you chose when you configured your robot using the sidebar configurer, they don't have to be "Motor1" and "Motor2".

//Left Motors:
motor_group(FL, ML, BL),

//Right Motors:
motor_group(FR, MR, BR),

//Specify the PORT NUMBER of your inertial sensor, in PORT format (i.e. "PORT1", not simply "1"):
PORT7,

//Input your wheel diameter. (4" omnis are actually closer to 4.125"):
3.25,

//External ratio, must be in decimal, in the format of input teeth/output teeth.
//If your motor has an 84-tooth gear and your wheel has a 60-tooth gear, this value will be 1.4.
//If the motor drives the wheel directly, this value is 1:
0.6,

//Gyro scale, this is what your gyro reads when you spin the robot 360 degrees.
//For most cases 360 will do fine here, but this scale factor can be very helpful when precision is necessary.
360,

/*---------------------------------------------------------------------------*/
/*                                  PAUSE!                                   */
/*                                                                           */
/*  The rest of the drive constructor is for robots using POSITION TRACKING. */
/*  If you are not using position tracking, leave the rest of the values as  */
/*  they are.                                                                */
/*---------------------------------------------------------------------------*/

//If you are using ZERO_TRACKER_ODOM, you ONLY need to adjust the FORWARD TRACKER CENTER DISTANCE.

//FOR HOLONOMIC DRIVES ONLY: Input your drive motors by position. This is only necessary for holonomic drives, otherwise this section can be left alone.
//LF:      //RF:    
PORT12,     -PORT2,

//LB:      //RB: 
PORT3,     -PORT4,

//If you are using position tracking, this is the Forward Tracker port (the tracker which runs parallel to the direction of the chassis).
//If this is a rotation sensor, enter it in "PORT1" format, inputting the port below.
//If this is an encoder, enter the port as an integer. Triport A will be a "1", Triport B will be a "2", etc.
20,

//Input the Forward Tracker diameter (reverse it to make the direction switch):
2.75,

//Input Forward Tracker center distance (a positive distance corresponds to a tracker on the right side of the robot, negative is left.)
//For a zero tracker tank drive with odom, put the positive distance from the center of the robot to the right side of the drive.
//This distance is in inches:
-2,

//Input the Sideways Tracker Port, following the same steps as the Forward Tracker Port:
21,

//Sideways tracker diameter (reverse to make the direction switch):
-2.75,

//Sideways tracker center distance (positive distance is behind the center of the robot, negative is in front):
5.5

);

int current_auton_selection = 2;
bool auto_started = false;
bool shooting = false;

double difficultyVoltage(int difficulty)
{
  switch(difficulty)
  {
    case Easy:
      return 8;
    case Normal:
      return 9;
    case Hard:
      return 10;
    case Insane:
      return 10.5;
    case Crazy:
      return 11;
    case Impossible:
      return 12;
    default:
      return 7.5;
  }
}

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();
  andre_constants();
  // while(auto_started == false){            //Changing the names below will only change their names on the
  //   Brain.Screen.clearScreen();            //brain screen for auton selection.
  //   switch(current_auton_selection){       //Tap the brain screen to cycle through autons.
  //     case 0:
  //       Brain.Screen.printAt(50, 50, "Drive Test");
  //       break;
  //     case 1:
  //       Brain.Screen.printAt(50, 50, "Drive Test");
  //       break;
  //     case 2:
  //       Brain.Screen.printAt(50, 50, "Turn Test");
  //       break;
  //     case 3:
  //       Brain.Screen.printAt(50, 50, "Swing Test");
  //       break;
  //     case 4:
  //       Brain.Screen.printAt(50, 50, "Full Test");
  //       break;
  //     case 5:
  //       Brain.Screen.printAt(50, 50, "Odom Test");
  //       break;
  //     case 6:
  //       Brain.Screen.printAt(50, 50, "Tank Odom Test");
  //       break;
  //     case 7:
  //       Brain.Screen.printAt(50, 50, "Holonomic Odom Test");
  //       break;
  //   }
  //   if(Brain.Screen.pressing()){
  //     while(Brain.Screen.pressing()) {}
  //     current_auton_selection ++;
  //   } else if (current_auton_selection == 8){
  //     current_auton_selection = 0;
  //   }
    task::sleep(10);
  // }
  
}

void debug_turn_to_angle(float angle)
{
  Brain.resetTimer();
  chassis.turn_to_angle(angle);
  std::cout << "KP " << chassis.turn_kp << std::endl << std::endl;
  std::cout << "KI " << chassis.turn_ki << std::endl << std::endl;
  std::cout << "KD " << chassis.turn_kd << std::endl << std::endl;
}

void debug_drive_distance(float distance)
{
  Brain.resetTimer();
  chassis.drive_distance(distance);
  std::cout << "KP " << chassis.drive_kp << std::endl << std::endl;
  std::cout << "KI " << chassis.drive_ki << std::endl << std::endl;
  std::cout << "KD " << chassis.drive_kd << std::endl << std::endl;
}

void outtake(int waittime)
{
  Intake.spin(reverse, 12, volt);
  wait(waittime, msec);
  Intake.stop();
}

void outtake()
{
  outtake(500);
  // chassis.drive_distance(3);
  // chassis.drive_distance(-3);
}



void spinCatapultFor(timeUnits unit, std::string difficulty)
{

}

void wingControl(bool val)
{
  LWing.set(val);
  RWing.set(val);
}

void far_side()
{ 
  chassis.drive_timeout = 1000;
  chassis.turn_timeout = 800;
  Intake.spin(fwd, 6, volt);
  // wingControl(true);
  RWing.set(true);
  wait(100, msec);
  Intake.spin(fwd, 1, volt);
  chassis.drive_distance(10, 0, 8, 8);
  chassis.right_swing_to_angle(330);
  // chassis.right_swing_to_angle(330, 6, chassis.swing_settle_error, chassis.swing_settle_time, chassis.swing_timeout, chassis.swing_kp, chassis.swing_ki, chassis.swing_kd, chassis.swing_starti);
  // chassis.turn_to_angle(330);
  chassis.drive_distance(10, 330, 8, 8);
  // wingControl(false);
  RWing.set(false);
  chassis.drive_distance(10, 330, 8, 8);
  outtake();
  chassis.drive_distance(-9, 330, 8, 8);

  //back in
  // chassis.turn_to_angle(150);
  // chassis.drive_distance(-5, 150, 6, 6);
  // chassis.drive_distance(5, 150, 8, 8);
  chassis.drive_timeout = 2000;

  chassis.turn_to_angle(247);
  Intake.spin(forward);
  chassis.drive_distance(45, 247, 6, 6);
  //grab first ball
  // wait(1, sec);
  // chassis.turn_to_angle(270);
  
  // chassis.drive_distance(10, 240, 8, 8);
  Intake.spin(fwd, 1, volt);
  // chassis.right_swing_to_angle(350);
  chassis.turn_to_angle(25);
  // chassis.drive_distance(15, 10, 8, 8);
  outtake(1000);
  // chassis.drive_distance(-5, 10, 8, 8);

  //grab middle ball
  chassis.turn_to_angle(293);
  Intake.spin(forward);
  chassis.drive_distance(20, 293, 8, 8);
  Intake.spin(forward, 6, volt);

  // chassis.right_swing_to_angle(45);
  chassis.turn_to_angle(43);

  wingControl(true);
  outtake();
  chassis.drive_distance(28, 43, 12, 8);
  chassis.drive_distance(-10, 43, 12, 12);
  wingControl(false);
  Catapult.spinFor(reverse, 0.3, rev, false);
  // chassis.drive_distance(5);
  // chassis.turn_to_angle(-90);
  // chassis.drive_distance(5);
  // chassis.turn_to_angle(0);
  // chassis.drive_distance(48);
  // outtake();
}

// void farBack_side()
// { 
//   chassis.drive_timeout = 1000;
//   chassis.turn_timeout = 800;
//   Intake.spin(fwd, 6, volt);
//   // wingControl(true);
//   RWing.set(true);
//   wait(100, msec);
//   Intake.spin(fwd, 1, volt);
//   chassis.drive_distance(10, 0, 8, 8);
//   chassis.right_swing_to_angle(330);
//   // chassis.right_swing_to_angle(330, 6, chassis.swing_settle_error, chassis.swing_settle_time, chassis.swing_timeout, chassis.swing_kp, chassis.swing_ki, chassis.swing_kd, chassis.swing_starti);
//   // chassis.turn_to_angle(330);
//   chassis.drive_distance(10, 330, 8, 8);
//   // wingControl(false);
//   RWing.set(false);
//   chassis.drive_distance(5, 330, 8, 8);
//   outtake();
//   chassis.drive_distance(-5, 330, 8, 8);

//   //back in
//   chassis.turn_to_angle(150);
//   chassis.drive_distance(-5, 150, 6, 6);
//   chassis.drive_distance(5, 150, 8, 8);
//   chassis.drive_timeout = 2000;

//   chassis.turn_to_angle(247);
//   Intake.spin(forward);
//   chassis.drive_distance(45, 247, 6, 6);
//   //grab first ball
//   // wait(1, sec);
//   // chassis.turn_to_angle(270);
  
//   // chassis.drive_distance(10, 240, 8, 8);
//   Intake.spin(fwd, 1, volt);
//   // chassis.right_swing_to_angle(350);
//   chassis.turn_to_angle(25);
//   // chassis.drive_distance(15, 10, 8, 8);
//   outtake(1000);
//   // chassis.drive_distance(-5, 10, 8, 8);

//   //grab middle ball
//   chassis.turn_to_angle(293);
//   Intake.spin(forward);
//   chassis.drive_distance(20, 293, 8, 8);
//   Intake.spin(forward, 6, volt);

//   // chassis.right_swing_to_angle(45);
//   chassis.turn_to_angle(43);

//   wingControl(true);
//   outtake();
//   chassis.drive_distance(28, 43, 8, 8);
 

//   // chassis.drive_distance(5);
//   // chassis.turn_to_angle(-90);
//   // chassis.drive_distance(5);
//   // chassis.turn_to_angle(0);
//   // chassis.drive_distance(48);
//   // outtake();
// }

void near_side()
{
  //Push load into goal
  Intake.spin(fwd, 1, volt);
  chassis.drive_distance(26, 0, 8, 8);
  chassis.turn_to_angle(45);
  chassis.drive_distance(6, 45, 8, 8);
  outtake();

  chassis.drive_distance(-8, 45, 8, 8);
  chassis.turn_to_angle(225);
  chassis.drive_distance(-12, 225, 8, 8);
  chassis.drive_distance(12, 225, 8, 8);

  //Take out wp ball
  chassis.right_swing_to_angle(180);
  // chassis.drive_distance(7, 180, 8, 8);
  // chassis.turn_to_angle(0);
  RWing.set(true);
  // wait(300, msec);
  // chassis.drive_distance(12, 185, 8, 8);
  // chassis.drive_distance(-26, 0, 8,8);
  chassis.right_swing_to_angle(135);
  RWing.set(false);
  // wait(100, msec);
  

  //Swing to gay
  // chassis.drive_distance(2, 135, 8, 8);
  chassis.turn_to_angle(180);
  chassis.drive_distance(13, 180, 8, 8);
  chassis.turn_to_angle(135);
  chassis.drive_distance(29.2, 135, 8, 8);


  // LWing.set(true);
  // chassis.left_swing_to_angle(150);
  // chassis.turn_to_angle(0);
  // chassis.drive_distance(-12, 0, 8, 8);
  // chassis.turn_to_angle(315);
  // chassis.drive_distance(-24, 315, 8, 8);
  // chassis.drive_distance(-28, -45, 8,8);  
}

void fullFwd(int amtTime){
  FL.spin(fwd, 12, volt);
  ML.spin(fwd, 12, volt);
  BL.spin(fwd, 12, volt);
  FR.spin(fwd, 12, volt);
  MR.spin(fwd, 12, volt);
  BR.spin(fwd, 12, volt);

  wait(amtTime, sec);

  FL.stop();
  ML.stop();
  BL.stop();
  FR.stop();
  MR.stop();
  BR.stop();
}

void skills()
{
  Intake.spin(fwd, 1, volt);
  chassis.drive_distance(24, 0, 8, 8);
  chassis.turn_to_angle(45);
  chassis.drive_distance(5, 45, 8, 8);
  outtake();
  chassis.drive_distance(-5, 45, 6, 6);
  chassis.turn_to_angle(225);
  chassis.drive_distance(-8, 225, 6, 6);
  chassis.drive_distance(7, 225, 8, 8);

  chassis.left_swing_to_angle(270);
  chassis.drive_distance(5, 270, 6, 6);
  chassis.right_swing_to_angle(290);
  chassis.drive_distance(1, 290, 4, 4);
  // Catapult.spin(reverse, difficultyVoltage(Normal), volt);
  Catapult.spin(reverse, 8, volt);
  wait(30, sec);
  Catapult.stop();

  chassis.drive_distance(-24, 290, 8, 8);
  // chassis.turn_to_angle(135);
  // chassis.drive_distance(10, 135, 8, 8);
  
  chassis.turn_to_angle(45);
  

  //// take the long way home
  chassis.drive_distance(72,45,8,8);
  chassis.turn_to_angle(135);
  chassis.drive_distance(36, 135, 8, 8);
  chassis.turn_to_angle(225);
  chassis.drive_distance(16, 225, 8, 8);
  chassis.turn_to_angle(315);
  chassis.drive_distance(20, 315, 8, 8);
  chassis.turn_to_angle(135);
  wingControl(true);
  chassis.drive_distance(20, 135, 8, 8);

  //Drive through mid pole
  // chassis.drive_distance(36, 45, 8, 8);
  // chassis.turn_to_angle(135);
  // wingControl(true);
  // //chassis.drive_distance(160, 135, 12, 12);
  // fullFwd(4);
  // chassis.drive_distance(-10, 135, 12, 12);
  // fullFwd(4);
  // chassis.drive_distance(-20, 135, 12, 12);
}

void safeFar(){
  Intake.spin(fwd, 6, volt);
  // wingControl(true);
  RWing.set(true);
  wait(100, msec);
  Intake.spin(fwd, 1, volt);
  chassis.drive_distance(10, 0, 8, 8);
  chassis.right_swing_to_angle(330);
  // chassis.right_swing_to_angle(330, 6, chassis.swing_settle_error, chassis.swing_settle_time, chassis.swing_timeout, chassis.swing_kp, chassis.swing_ki, chassis.swing_kd, chassis.swing_starti);
  // chassis.turn_to_angle(330);
  outtake();
  chassis.drive_distance(10, 330, 8, 8);
  // wingControl(false);
  RWing.set(false);
  chassis.drive_distance(10, 330, 8, 8);
  outtake();
  chassis.drive_distance(-9, 330, 8, 8);

  chassis.turn_to_angle(150);
  chassis.drive_distance(-10, 150, 12, 6);
  chassis.drive_distance(10, 150, 8, 8);
}

void swing()
{
  chassis.right_swing_to_angle(45);
}

void autonWait(){
  Inertial.calibrate();
  while (Inertial.isCalibrating()){
    wait(50, msec);
  }
  wait(2, sec);
}

void safeSafeFar(){
  Intake.spin(fwd, 1, volt);
  chassis.drive_distance(50, 0, 10, 8);
  chassis.turn_to_angle(90);
  Intake.spin(reverse, 1, volt);
  chassis.drive_distance(15);
  chassis.drive_distance(-15);

}

void autonomous(void) { 
  //autonWait();

  wingControl(false);
  Catapult.spinFor(reverse, 1, rev, false);
  
  //chassis.drive_distance(160, 0, 12, 12);
  //chassis.drive_distance(-20, 0, 12, 12);

  //safeSafeFar();
  //near_side();
  far_side();
  Catapult.spinFor(reverse, 0.35, rev, false);

  //farBack_side();

  //safeFar();
  //skills();
}

void drive_tuning(float tuning_factor)
{
  if (Controller1.ButtonX.PRESSED){
      chassis.drive_kp += tuning_factor;
      std::cout << "KP "<< chassis.drive_kp << std::endl << std::endl;
  }
  if (Controller1.ButtonA.PRESSED){
    chassis.drive_kp -= tuning_factor;
    std::cout << "KP "<<chassis.drive_kp << std::endl << std::endl;
  }
  if (Controller1.ButtonY.PRESSED){
    chassis.drive_kd += tuning_factor;
    std::cout << "KD "<<chassis.drive_kd << std::endl << std::endl;
  }
  if (Controller1.ButtonB.PRESSED){
    chassis.drive_kd -= tuning_factor;
    std::cout << "KD "<<chassis.drive_kd << std::endl << std::endl;
  } 

  if(Controller1.ButtonL1.PRESSED){
    debug_drive_distance(24);
  }
  if(Controller1.ButtonL2.PRESSED) {
    debug_drive_distance(-24);
  }
  if(Controller1.ButtonR1.PRESSED) {
    debug_drive_distance(6);
  }
  if(Controller1.ButtonR2.PRESSED) {
    debug_drive_distance(-6);
  }
}

void turn_tuning(float tuning_factor)
{
  if (Controller1.ButtonX.PRESSED){
    chassis.turn_kp += tuning_factor;
    std::cout << "KP " << chassis.turn_kp << std::endl << std::endl;
  }
  if (Controller1.ButtonA.PRESSED){
    chassis.turn_kp -= tuning_factor;
    std::cout << "KP" << chassis.turn_kp << std::endl << std::endl;
  }
  if (Controller1.ButtonY.PRESSED){
    chassis.turn_kd += tuning_factor;
    std::cout << "KD" << chassis.turn_kd << std::endl << std::endl;
  }
  if (Controller1.ButtonB.PRESSED){
    chassis.turn_kd -= tuning_factor;
    std::cout << "KD" << chassis.turn_kd << std::endl << std::endl;
  }  
  
  if(Controller1.ButtonL1.PRESSED){
    debug_turn_to_angle(90);
  }
  if(Controller1.ButtonL2.PRESSED) {
    debug_turn_to_angle(0);
  }
  if(Controller1.ButtonR2.PRESSED) {
    debug_turn_to_angle(180);
  }
  if(Controller1.ButtonR1.PRESSED) {
    debug_turn_to_angle(-45);
  }
}



void catapultControl(double diff)
{
  double volts = difficultyVoltage(diff);
  if(Controller1.ButtonR1.PRESSED)
  {
    shooting = !shooting;
  }

  if(shooting){
      Catapult.spin(reverse, volts, volt);
  }
  else{     
    Catapult.stop();
  }
}

void intakeControl(){
  Intake.setBrake(coast);
  Intake.setVelocity(90, pct);

  if (Controller1.ButtonL1.pressing()){
    Intake.spin(fwd);
  }
  else if (Controller1.ButtonL2.pressing()){
    Intake.spin(reverse);
  }
  else {
    Intake.spin(fwd, 0.2, volt); 
  }
}

void wingControl(){
  if (Controller1.ButtonX.PRESSED){
    wingControl(true);
  }
  else if (Controller1.ButtonB.PRESSED){
    wingControl(false);
  }
}

void i_drive()
{
  chassis.control_arcade(1, 0.65);
  intakeControl();
  wingControl();
  //Easy, Normal, Hard, Insane, Crazy, Impossible
  catapultControl(9.5);
}

void pid_tuning()
{
  wait(5, sec);
  int mode = 0; //0 - turning;     1 - driving
  float t_factor = 1;

  while(1)
  {
    if(Controller1.ButtonLeft.PRESSED)
    {
      mode = 0;
      std::cout << "Tuning Turns" << std::endl;
    }
    else if(Controller1.ButtonRight.PRESSED)
    {
      mode = 1;
      std::cout << "Tuning Drive" << std::endl;
    }
    else if(Controller1.ButtonUp.PRESSED)
    {
      t_factor *= 10;
      std::cout<< "t_factor: " << t_factor<<std::endl;
    }
    else if(Controller1.ButtonDown.PRESSED)
    {
      t_factor *= 0.1;
      std::cout<< "t_factor: " << t_factor<<std::endl;
    }
    else
    {
      switch (mode)
      {
      case 1:
        drive_tuning(t_factor);
        break;
      case 0:
        turn_tuning(t_factor);
        break;
      }
    }
    wait(20, msec);
  }
}


void usercontrol(void) {
  // User control code here, inside the loop
  wingControl(false);
  while (1) {

    i_drive();
    // pid_tuning();
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
  // Competition.drivercontrol(pid_tuning);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    wait(100, msec);
  }
}