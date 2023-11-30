#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;

//constructors

brain  Brain;

controller Controller1 = controller(primary);

/*
  PORTS:
  RF 3 , RM 10 reverse, RB 5,
  LF 2, LM 6 reverse, LB 4
  CATA 1, Inertial 7, Intake 18.
*/

motor FL = motor(PORT2, ratio18_1, false);
motor FR = motor(PORT3, ratio18_1, false);
motor ML = motor(PORT6, ratio18_1, true);
motor MR = motor(PORT10, ratio18_1, true);
motor BL = motor(PORT4, ratio18_1, false);
motor BR = motor(PORT5, ratio18_1, false);

motor Intake = motor(PORT18, ratio18_1, false);
motor Catapult = motor(PORT1, ratio18_1, false);
inertial Inertial = inertial(PORT7);




/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}