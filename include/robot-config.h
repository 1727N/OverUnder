using namespace vex;

extern brain Brain;

extern controller Controller1;

extern motor FL;
extern motor FR;
extern motor ML;
extern motor MR;
extern motor BL;
extern motor BR;

extern motor Intake;
extern motor Catapult;
extern inertial Inertial;

extern digital_out LWing;
extern digital_out RWing;
// VEXcode devices

/**
 * Used to initialize code/tasks/devices added using tools in VEXcode Pro.
 * 
 * This should be called at the start of your int main function.
 */
void  vexcodeInit( void );