#include "vex.h"

using namespace vex;
using signature = vision::signature;
using code = vision::code;


brain  Brain;

motor lm1 = motor(PORT11, ratio6_1, true);
motor lm2 = motor(PORT12, ratio6_1, false);
motor lm3 = motor(PORT13, ratio6_1, true);

motor rm1 = motor(PORT18, ratio6_1, false);
motor rm2 = motor(PORT19, ratio6_1, true);
motor rm3 = motor(PORT20, ratio6_1, false);

motor intake = motor(PORT4, ratio6_1, true);
motor outtake = motor(PORT2, ratio6_1, true);

pneumatics outtakePneumatic = pneumatics(Brain.ThreeWirePort.H);
pneumatics matchloadPneumatic = pneumatics(Brain.ThreeWirePort.G);
pneumatics wingPneumatic = pneumatics(Brain.ThreeWirePort.F);

void vexcodeInit( void ) {
  // nothing to initialize
}