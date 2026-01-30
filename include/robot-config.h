using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;

//Add your devices below, and don't forget to do the same in robot-config.cpp:

extern motor lm1;
extern motor lm2;
extern motor lm3;

extern motor rm1;
extern motor rm2;
extern motor rm3;

extern motor intake;
extern motor outtake;

extern pneumatics outtakePneumatic;
extern pneumatics matchloadPneumatic;
extern pneumatics wingPneumatic;


void  vexcodeInit( void );