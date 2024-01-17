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

motor FL = motor(PORT2, ratio6_1, true);
motor FR = motor(PORT3, ratio6_1, false);
motor ML = motor(PORT6, ratio6_1, true);
motor MR = motor(PORT10, ratio6_1, false);
motor BL = motor(PORT4, ratio6_1, true);
motor BR = motor(PORT5, ratio6_1, false);

motor Intake = motor(PORT11, ratio18_1, false);
motor Catapult = motor(PORT1, ratio18_1, false);
inertial Inertial = inertial(PORT7);

// digital_out Wings = digital_out(Brain.ThreeWirePort.H);
digital_out LWing = digital_out(Brain.ThreeWirePort.A);
digital_out RWing = digital_out(Brain.ThreeWirePort.H);



/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void vexcodeInit( void ) {
  // nothing to initialize
}