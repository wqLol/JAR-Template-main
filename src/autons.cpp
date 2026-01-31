#include "vex.h"

/**
 * Resets the constants for auton movement.
 * Modify these to change the default behavior of functions like
 * drive_distance(). For explanations of the difference between
 * drive, heading, turning, and swinging, as well as the PID and
 * exit conditions, check the docs.
 */

void default_constants(){
  // Each constant set is in the form of (maxVoltage, kP, kI, kD, startI).
  chassis.set_drive_constants(10, 1.5, 0, 10, 0);
  chassis.set_heading_constants(6, .4, 0, 1, 0);
  chassis.set_turn_constants(12, .4, .03, 3, 15);
  chassis.set_swing_constants(12, .3, .001, 2, 15);

  // Each exit condition set is in the form of (settle_error, settle_time, timeout).
  chassis.set_drive_exit_conditions(1.5, 300, 5000);
  chassis.set_turn_exit_conditions(1, 300, 3000);
  chassis.set_swing_exit_conditions(1, 300, 3000);
}

/**
 * Sets constants to be more effective for odom movements.
 * For functions like drive_to_point(), it's often better to have
 * a slower max_voltage and greater settle_error than you would otherwise.
 */

void odom_constants(){
  default_constants();
  chassis.heading_max_voltage = 10;
  chassis.drive_max_voltage = 8;
  chassis.drive_settle_error = 3;
  chassis.boomerang_lead = .5;
  chassis.drive_min_voltage = 0;
}

/**
 * The expected behavior is to return to the start position.
 */

void drive_test(){
  chassis.drive_distance(6);
  chassis.drive_distance(12);
  chassis.drive_distance(18);
  chassis.drive_distance(-36);
}

/**
 * The expected behavior is to return to the start angle, after making a complete turn.
 */

void turn_test(){
  chassis.turn_to_angle(5);
  chassis.turn_to_angle(30);
  chassis.turn_to_angle(90);
  chassis.turn_to_angle(225);
  chassis.turn_to_angle(0);
}

/**
 * Should swing in a fun S shape.
 */

void swing_test(){
  chassis.left_swing_to_angle(90);
  chassis.right_swing_to_angle(0);
}

/**
 * A little of this, a little of that; it should end roughly where it started.
 */

void full_test(){
  chassis.drive_distance(24);
  chassis.turn_to_angle(-45);
  chassis.drive_distance(-36);
  chassis.right_swing_to_angle(-90);
  chassis.drive_distance(24);
  chassis.turn_to_angle(0);
}

/**
 * Doesn't drive the robot, but just prints coordinates to the Brain screen 
 * so you can check if they are accurate to life. Push the robot around and
 * see if the coordinates increase like you'd expect.
 */

void odom_test(){
  chassis.set_coordinates(0, 0, 0);
  while(1){
    Brain.Screen.clearScreen();
    Brain.Screen.printAt(5,20, "X: %f", chassis.get_X_position());
    Brain.Screen.printAt(5,40, "Y: %f", chassis.get_Y_position());
    Brain.Screen.printAt(5,60, "Heading: %f", chassis.get_absolute_heading());
    Brain.Screen.printAt(5,80, "ForwardTracker: %f", chassis.get_ForwardTracker_position());
    Brain.Screen.printAt(5,100, "SidewaysTracker: %f", chassis.get_SidewaysTracker_position());
    task::sleep(20);
  }
}

/**
 * Should end in the same place it began, but the second movement
 * will be curved while the first is straight.
 */

void tank_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.turn_to_point(24, 24);
  chassis.drive_to_point(24,24);
  chassis.drive_to_point(0,0);
  chassis.turn_to_angle(0);
}

/**
 * Drives in a square while making a full turn in the process. Should
 * end where it started.
 */

void holonomic_odom_test(){
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  chassis.holonomic_drive_to_pose(0, 18, 90);
  chassis.holonomic_drive_to_pose(18, 0, 180);
  chassis.holonomic_drive_to_pose(0, 18, 270);
  chassis.holonomic_drive_to_pose(0, 0, 0);
}

// void cool_auton() {
//   odom_constants();
  
//   chassis.drive_max_voltage = 8;
//   chassis.turn_max_voltage = 7;

//   chassis.set_coordinates(0, 0, 0);

//   chassis.drive_to_point(0, 47.352);
//   matchloadPneumatic.open();


//   wait(200, msec);
//   chassis.turn_to_angle(-90);
//   intake.spin(forward, 11, volt);




  
//   chassis.drive_distance(13);

//   wait(2, sec);

//   chassis.drive_distance(-30);

//   outtakePneumatic.open();

//   outtake.spin(forward, 11, volt);
//   // chassis.drive_distance(-24);



// }

// void cool_auton() {
//   lm1.spin(forward, 11, volt);
//   wait(500, msec);
//   lm1.stop();
//   lm2.spin(forward, 11, volt);
//   wait(500, msec);
//   lm2.stop();
//   lm3.spin(forward, 11, volt);
//   wait(500, msec);
//   rm1.spin(forward, 11, volt);
//   wait(500, msec);
//   rm2.spin(forward, 11, volt);
//   wait(500, msec);
//   rm3.spin(forward, 11, volt);
//   wait(500, msec);

// }
void auton_skills() {
    // (18, 1) 
  odom_constants();
  chassis.drive_max_voltage = 9;
  chassis.turn_max_voltage = 6;
  outtakePneumatic.open();
  wingPneumatic.open();

  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(19.00); 
    
  // (18, 32) 
  chassis.turn_to_angle(-90.00); 
  chassis.drive_distance(34.50); 
    
  // (5, 32) 
  chassis.turn_to_angle(-180.00); 
  matchloadPneumatic.open(); 
  intake.spin(forward, 11, volt); 
  wait(1, sec); 
  chassis.drive_distance(15.00); 
  chassis.DriveL.spin(forward, 5, volt);
  chassis.DriveR.spin(forward, 5, volt);
    wait(50, msec);
  chassis.DriveL.stop();
  chassis.DriveR.stop();
  for (int i = 0;i < 3;i++) {
    chassis.DriveL.spin(reverse, 5, volt);
    chassis.DriveR.spin(reverse, 5, volt);
    wait(50, msec);
    intake.spin(reverse, 11, volt);
    outtake.spin(forward, 11, volt);
    wait(50, msec);
    outtake.stop();
    intake.spin(forward, 11, volt);

    chassis.DriveL.spin(forward, 5, volt);
    chassis.DriveR.spin(forward, 5
      , volt);

    wait(400, msec);
  }
  intake.spin(reverse, 11, volt);
  wait(200, msec);
  intake.spin(forward, 11, volt);
  wait(0.4, sec);

  // (13, 32) 
  intake.spin(forward, 11, volt);
  chassis.turn_to_angle(-180.00); 
  chassis.drive_distance(-8.00); 
  matchloadPneumatic.close(); 
  chassis.drive_distance(2);
  wait(0.5, sec); 
  // (30, 44) 
  chassis.turn_to_angle(-35.22); 
  chassis.drive_distance(26.2); 
    
  // (103, 44) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(73.00); 
    
  // (103, 32) 
  chassis.turn_to_angle(90.00); 
  chassis.drive_distance(11); 
    
  // (95, 32) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(-8.00);
  chassis.drive_distance(0.3); 
  intake.spin(forward, 11, volt); 
  outtake.spin(forward, 11, volt); 
  matchloadPneumatic.open(); 
  wait(1, sec);
  intake.spin(reverse, 11, volt);
  outtake.spin(reverse, 11, volt);
  wait(0.2, sec);
  intake.spin(forward, 11, volt); 
  outtake.spin(forward, 11, volt); 
  wait(1, sec); 
  outtake.stop();
    
  // (121, 32) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(27.00);
  for (int i = 0;i < 3;i++) {
    chassis.DriveL.spin(reverse, 5, volt);
    chassis.DriveR.spin(reverse, 5, volt);
    wait(50, msec);
    intake.spin(reverse, 11, volt);
    outtake.spin(forward, 11, volt);
    wait(50, msec);
    outtake.stop();
    intake.spin(forward, 11, volt);

    chassis.DriveL.spin(forward, 5, volt);
    chassis.DriveR.spin(forward, 5, volt);

  wait(400, msec);
  }


  wait(0.2, sec);
    
  // (95, 32) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(-27.00); 
  matchloadPneumatic.close(); 
  intake.spin(forward, 11, volt);
  outtake.spin(forward, 11, volt);
  wait(1, sec); 
  intake.spin(reverse, 11, volt);
  outtake.spin(reverse, 11, volt);
  wait(0.2, sec); 
  intake.spin(forward, 11, volt);
  outtake.spin(forward, 11, volt);
  wait(1, sec); 
  outtake.stop();
    
  // (103, 32) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(8.00); 
    
  // (103, -62) 
  chassis.turn_to_angle(90.00); 
  chassis.drive_distance(98.00); 
    
  // (121, -62) 
  chassis.turn_to_angle(0.00); 
  matchloadPneumatic.open(); 
  intake.spin(forward, 11, volt);
  wait(1, sec); 
  chassis.drive_distance(17.00);
  chassis.DriveL.spin(forward, 5, volt);
  chassis.DriveR.spin(forward, 5, volt);

  outtake.spin(forward, 11, volt);
  wait(400, msec);
  for (int i = 0;i < 3;i++) {
    chassis.DriveL.spin(reverse, 5, volt);
    chassis.DriveR.spin(reverse, 5, volt);
    wait(50, msec);
    intake.spin(reverse, 11, volt);
    wait(50, msec);
    intake.spin(forward, 11, volt);

    chassis.DriveL.spin(forward, 5, volt);
    chassis.DriveR.spin(forward, 5, volt);

  wait(400, msec);
  }


  wait(0.2, sec);
    
    
  // (113, -62) 
  chassis.turn_to_angle(0.00); 
  chassis.drive_distance(-8.00); 
  matchloadPneumatic.close(); 
  wait(1, sec); 
  
    
  // (96, -74) 
  chassis.turn_to_angle(144.78); 
  chassis.drive_distance(25.81); 
    
  // (23, -74) 
  chassis.turn_to_angle(180.00); 
  chassis.drive_distance(73.00); 
    
  // (23, -62) 
  chassis.turn_to_angle(270.00); 
  chassis.drive_distance(12.00); 
    
  // (31, -62) 
    
  // (5, -62) 
  chassis.turn_to_angle(180.00); 
  matchloadPneumatic.open();
  wait(0.5, sec); 
  chassis.drive_distance(18.00);
  outtake.spin(forward, 11, volt);
  
  for (int i = 0;i < 3;i++) {
    chassis.DriveL.spin(reverse, 5, volt);
    chassis.DriveR.spin(reverse, 5, volt);
    wait(50, msec);
    intake.spin(reverse, 11, volt);
    wait(50, msec);
    intake.spin(forward, 11, volt);

    chassis.DriveL.spin(forward, 5, volt);
    chassis.DriveR.spin(forward, 5, volt);

  wait(400, msec);
  }


  wait(0.2, sec);
    
  
  // (31, -62) 
  chassis.turn_to_angle(180.00); 
  chassis.drive_distance(-8.00); 
  matchloadPneumatic.close(); 
  wait(0.2, sec);
    
  // (23, -15) 
  chassis.turn_to_angle(270.00); 
  chassis.drive_distance(17.00); 
    
  // (-7, -15) 
  chassis.turn_to_angle(180.00); 
  chassis.drive_distance(10.00);
  
  chassis.turn_to_angle(-81.25383774);
  chassis.drive_distance(13.15294644);
  matchloadPneumatic.open();
  wait(0.4, sec);
  chassis.drive_distance(28);
  matchloadPneumatic.close();


  // // (31, -62) 
  // chassis.turn_to_angle(180.00); 
  // chassis.drive_distance(-26.00); 
  // matchloadPneumatic.close(); 
  // outtake.spin(forward, 11, volt); 
  // wait(3, sec); 
    
  // // (23, -62) 
  // chassis.turn_to_angle(180.00); 
  // chassis.drive_distance(8.00); 
    
  // // (23, -15) 
  // chassis.turn_to_angle(270.00); 
  // chassis.drive_distance(47.00); 
    
  // // (-7, -15) 
  // chassis.turn_to_angle(180.00); 
  // chassis.drive_distance(30.00); 

//   odom_constants();

// chassis.drive_max_voltage = 8;  

// chassis.turn_max_voltage = 4;
// intake.spin(reverse, 11, volt);
// // → (0, 52)
// chassis.drive_distance(18.000);

// chassis.turn_to_angle(-90);
// chassis.drive_distance(31.000);
// // → (5, 64)
// chassis.turn_to_angle(-180.000);
// matchloadPneumatic.open();
// wait(1, sec);
// chassis.drive_distance(11.000);

// // → (13, 64)
// chassis.turn_to_angle(-180.000);
// chassis.drive_distance(-8.000);
// matchloadPneumatic.close();
// wait(1, sec);

// // → (30, 76)
// chassis.turn_to_angle(-35.218);
// chassis.drive_distance(20.809);

// // → (103, 76)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(73.000);

// // → (103, 64)
// chassis.turn_to_angle(-90.000);
// chassis.drive_distance(12.000);

// // → (95, 64)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(-8.000);

// // → (121, 64)
// chassis.turn_to_angle(0.000);
// matchloadPneumatic.open();
// wait(1, sec);
// chassis.drive_distance(26.000);

// // → (95, 64)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(-26.000);
// matchloadPneumatic.close();
// wait(1, sec);

// // → (103, 64)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(8.000);

// // → (103, -30)
// chassis.turn_to_angle(90.000);
// chassis.drive_distance(94.000);

// // → (121, -30)
// chassis.turn_to_angle(0.000);
// matchloadPneumatic.open();
// wait(1, sec);
// chassis.drive_distance(18.000);

// // → (113, -30)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(-8.000);
// matchloadPneumatic.close();
// wait(1, sec);

// // → (96, -42)
// chassis.turn_to_angle(35.218);
// chassis.drive_distance(-20.809);

// // → (23, -42)
// chassis.turn_to_angle(0.000);
// chassis.drive_distance(-73.000);

// // → (23, -30)
// chassis.turn_to_angle(90.000);
// chassis.drive_distance(-12.000);

// // → (31, -30)
// chassis.turn_to_angle(180.000);
// chassis.drive_distance(-8.000);

// // → (5, -30)
// chassis.turn_to_angle(180.000);
// matchloadPneumatic.open();
// wait(1, sec);
// chassis.drive_distance(26.000);

// // → (31, -30)
// chassis.turn_to_angle(180.000);
// chassis.drive_distance(-26.000);
// matchloadPneumatic.close();
// wait(1, sec);

// // → (23, -30)
// chassis.turn_to_angle(180.000);
// chassis.drive_distance(8.000);

// // → (23, 17)
// chassis.turn_to_angle(270.000);
// chassis.drive_distance(47.000);

// // → (-7, 17)
// chassis.turn_to_angle(180.000);
// chassis.drive_distance(30.000);

}
void cool_auton() {
  odom_constants();
  chassis.set_coordinates(0, 0, 0);
  // chassis.turn_to_point(-73, 17);
  chassis.drive_max_voltage = 7;  
  chassis.turn_max_voltage = 5;  
  wingPneumatic.open();
// (18, 2)
  chassis.turn_to_angle(0);
  chassis.drive_distance(17);
// (29, -1)
chassis.turn_to_angle(-15.255187);
  intake.spin(forward, 11, volt);
  chassis.drive_distance(27.5);
// (49.5, -1.5)
  chassis.turn_to_angle(-135);
  chassis.drive_distance(-9.75);
  outtake.spin(forward, 11, volt);
  wait(0.75, sec);
// (16, 32)
  outtake.stop();
  chassis.turn_to_angle(-135);
  chassis.drive_distance(49.25);
// (5, 32)
  chassis.turn_to_angle(-180);
  matchloadPneumatic.open();
  outtakePneumatic.open();
  wait(150, msec);
  chassis.drive_distance(11);
  for (int i = 0;i < 1;i++) {
    chassis.DriveL.spin(reverse, 5, volt);
    chassis.DriveR.spin(reverse, 5, volt);
    wait(50, msec);
    intake.spin(reverse, 11, volt);
    outtake.spin(forward, 11, volt);
    wait(50, msec);
    outtake.stop();
    intake.spin(forward, 11, volt);

    chassis.DriveL.spin(forward, 5, volt);
    chassis.DriveR.spin(forward, 5
      , volt);

    wait(400, msec);
  }
// (31, 32)
  // chassis.turn_to_angle(-180);
  chassis.turn_to_angle(-180);
  chassis.drive_distance(-26);
  outtake.spin(forward, 11, volt);
  matchloadPneumatic.close();
  wait(1, sec);
// // (23, 32)
//   // chassis.turn_to_angle(-180);
//   chassis.drive_distance(8);
// // (35, 21)
//   chassis.turn_to_angle(-137.49);
//   chassis.drive_distance(-15.779);
// // (53, 21)

//   chassis.turn_to_angle(-180);
//   chassis.drive_distance(-6);
//   wingPneumatic.close();
//   chassis.drive_max_voltage = 11;  
//   chassis.drive_distance(-11);


  // wait(1, sec);
  // chassis.drive_distance(30);
  
  // wait(200, msec);
  // intake.spin(forward, 11, volt);
  // chassis.turn_to_angle(-20);





  // chassis.drive_max_voltage = 10;  

  // chassis.drive_distance(15);


  // chassis.turn_to_angle(-130);

  // chassis.drive_max_voltage = 5;
  // chassis.drive_distance(-10);

  // outtake.spin(forward, 11, volt);
  // chassis.drive_max_voltage = 10;

  // wait(2, sec);
  // outtake.stop();
  // // chassis.drive_distance(48);
  // chassis.drive_max_voltage = 7;
  // chassis.turn_to_point(-52, 18);
  // chassis.drive_to_point(-52, 18);
  
  // chassis.turn_to_angle(180); 


  // matchloadPneumatic.open();
  // wait(1, sec);

  // chassis.drive_distance(20);

  // wait(1, sec);

  // chassis.drive_distance(-20);
  // outtakePneumatic.open();
  // outtake.spin(forward, 11, volt);

  // chassis.drive_distance(-20);
  // chassis.set_coordinates(0, 0, 0);
  // // // chassis.mov(30, 0, -20);
  // // chassis.drive_to_point(0, 28);

  // // chassis.drive_max_voltage = 5;  
  // // // chassis.turn_to_angle(-20);

  // // chassis.drive_to_point(-3, 44);
  // chassis.drive_max_voltage = 7;
  // chassis.drive_distance(30);
  // chassis.turn_to_angle(-20);

  // intake.spin(forward, 11, volt);
  // chassis.drive_max_voltage = 5;
  // chassis.turn_max_voltage = 5;
  // chassis.drive_distance(15);
  // chassis.turn_to_angle(-130);
  // chassis.drive_distance(-10);
  // outtake.spin(forward, 8, volt);

  // chassis.drive_max_voltage = 10;
  // wait(500, msec);
  // // outtake.stop();
  // chassis.drive_distance(48);
  // chassis.turn_to_angle(-180);
  // outtake.stop();

  // matchloadPneumatic.open();
  // chassis.drive_max_voltage = 7;
  // chassis.drive_distance(18);

  // wait(2, sec);
  
  // chassis.drive_distance(-25);
  // outtakePneumatic.close();
  // outtake.spin(forward, 11, volt);
  // chassis.drive_max_voltage = 101;
}
  // odom_constants();

  // chassis.drive_max_voltage = 8;
  // chassis.turn_max_voltage = 5;

  // chassis.set_coordinates(0, 0, 0);
  // chassis.drive_to_point(0, 29.673);

  // wait(200, msec);
  // intake.spin(forward, 11, volt);
  // chassis.drive_max_voltage = 4;

  // chassis.drive_to_point(3.766, 50.008);
  // outtake.spin(forward, 11, volt);

  // wait(500, msec);
  // intake.stop();


// }

// void cool_auton(){
//   // sideways.resetRotation();
//   // chassis.DriveR.resetPosition();
//   // chassis.DriveL.resetPosition();
  
//   // chassis.DriveR.spin(reverse, 4, volt);
//   // chassis.DriveL.spin(reverse, 4, volt);

//   // wait(1.9, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();

//   // chassis.DriveR.spin(reverse, 5, volt);
//   // chassis.DriveL.spin(forward, 5, volt);

//   // wait(0.2, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();

//   // chassis.DriveR.spin(reverse, 3, volt);
//   // chassis.DriveL.spin(reverse, 3, volt);

//   // wait(0.5, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();

//   // outtake.spin(forward, 11, volt);
//   // wait(1, sec);
//   // outtake.stop();

//   // matchloadPneumatic.open();

//   // chassis.DriveR.spin(forward, 4, volt);
//   // chassis.DriveL.spin(forward, 4, volt);

//   // wait(2.15, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();


//   // chassis.DriveR.spin(forward, 4, volt);
//   // chassis.DriveL.spin(reverse, 4, volt);

//   // wait(0.35, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();

//   // intake.spin(forward, 11, volt);
//   // chassis.DriveR.spin(forward, 4, volt);
//   // chassis.DriveL.spin(forward, 4, volt);

//   // wait(1, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();
//   // outtakePneumatic.open();

//   // chassis.DriveR.spin(reverse, 4, volt);
//   // chassis.DriveL.spin(reverse, 4, volt);

//   // wait(1.5, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();
  
//   // chassis.DriveR.spin(reverse, 3, volt);
//   // chassis.DriveL.spin(reverse, 4.5, volt);

//   // wait(0.5, sec);

//   // chassis.DriveR.stop();
//   // chassis.DriveL.stop();
//   // intake.spin(reverse, 11, volt);
//   // wait(0.3, sec);
//   // intake.spin(forward, 11, volt);
//   // outtake.spin(forward, 11, volt);


//   odom_constants();

//   chassis.drive_max_voltage = 7;  
//   chassis.turn_max_voltage = 5;  


//   chassis.drive_distance(30);
  
//   wait(200, msec);
//   intake.spin(forward, 11, volt);
//   chassis.turn_to_angle(-20);





//   chassis.drive_max_voltage = 5;  

//   chassis.drive_distance(15);


//   chassis.turn_to_angle(-130);
//   chassis.drive_distance(-13);

//   outtake.spin(forward, 8, volt);


//   wait(2, sec);
//   outtake.stop();
//   chassis.drive_distance(47);

//   chassis.turn_to_angle(180); 


//   matchloadPneumatic.open();
//   chassis.drive_distance(20);

//   wait(1, sec);

//   chassis.drive_distance(20);
//   outtakePneumatic.open();
//   outtake.spin(forward, 11, volt);

//   // chassis.drive_distance(-20);
//   // chassis.set_coordinates(0, 0, 0);
//   // // // chassis.mov(30, 0, -20);
//   // // chassis.drive_to_point(0, 28);

//   // // chassis.drive_max_voltage = 5;  
//   // // // chassis.turn_to_angle(-20);

//   // // chassis.drive_to_point(-3, 44);
//   // chassis.drive_max_voltage = 7;
//   // chassis.drive_distance(30);
//   // chassis.turn_to_angle(-20);

//   // intake.spin(forward, 11, volt);
//   // chassis.drive_max_voltage = 5;
//   // chassis.turn_max_voltage = 5;
//   // chassis.drive_distance(15);
//   // chassis.turn_to_angle(-130);
//   // chassis.drive_distance(-10);
//   // outtake.spin(forward, 8, volt);

//   // chassis.drive_max_voltage = 10;
//   // wait(500, msec);
//   // // outtake.stop();
//   // chassis.drive_distance(48);
//   // chassis.turn_to_angle(-180);
//   // outtake.stop();

//   // matchloadPneumatic.open();
//   // chassis.drive_max_voltage = 7;
//   // chassis.drive_distance(18);

//   // wait(2, sec);
  
//   // chassis.drive_distance(-25);
//   // outtakePneumatic.close();
//   // outtake.spin(forward, 11, volt);
//   // chassis.drive_max_voltage = 101;
// }