/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:                                                                 */
/*    Created:      Thu Sep 26 2019                                           */
/*    Description:  Competition Template                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*
 * Rename this file as `main.cpp` and remove the `#if 0` below and the
 * `#endif` at the end of this file.
 */

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"
#include "robot-config.h"
#include "vpi/vpi.h"
#include "PIDTunerUI.h"

using namespace vex;
using namespace vpi;

// A global instance of competition
competition Competition;

// define your global instances of motors and other devices here
#define ROBOT_GEAR_SETTING vex::ratio6_1
#define ROBOT_GEAR_RATIO 36.0 / 60.0
#define ROBOT_LEFT_MOTOR_1 PORT1
#define ROBOT_LEFT_MOTOR_1_REV true
#define ROBOT_LEFT_MOTOR_2 PORT19
#define ROBOT_LEFT_MOTOR_2_REV false
#define ROBOT_LEFT_MOTOR_3 PORT10
#define ROBOT_LEFT_MOTOR_3_REV true
#define ROBOT_RIGHT_MOTOR_1 PORT3
#define ROBOT_RIGHT_MOTOR_1_REV true
#define ROBOT_RIGHT_MOTOR_2 PORT20
#define ROBOT_RIGHT_MOTOR_2_REV false
#define ROBOT_RIGHT_MOTOR_3 PORT11
#define ROBOT_RIGHT_MOTOR_3_REV false

#define ROBOT_GPS_PORT PORT8
#define ROBOT_GPS_MOUNT_OFFSET_X 1.25
#define ROBOT_GPS_MOUNT_OFFSET_Y 1.00
#define ROBOT_GPS_MOUNT_OFFSET_HEADING -90

#define ROBOT_INERTIAL_PORT PORT5

// You may want to use the PhysicalDriveTuner to help determine these 2 values
#define ROBOT_WHEEL_TRACK 17_in
#define ROBOT_WHEEL_DIAMETER 3.25_in

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
}

void testForward() {
  vex::motor ml1 = motor(ROBOT_LEFT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_1_REV);
  vex::motor ml2 = motor(ROBOT_LEFT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_2_REV);
  vex::motor ml3 = motor(ROBOT_LEFT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_3_REV);
  vex::motor mr1 = motor(ROBOT_RIGHT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_1_REV);
  vex::motor mr2 = motor(ROBOT_RIGHT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_2_REV);
  vex::motor mr3 = motor(ROBOT_RIGHT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_3_REV);
  vex::motor_group mg_left{ml1, ml2 ,ml3};
  vex::motor_group mg_right{mr1, mr2, mr3};
  DifferentialDriveChassisPID m_chassis(mg_left, mg_right, 
                                        ROBOT_WHEEL_TRACK, ROBOT_WHEEL_DIAMETER, 
                                        PID_d, PID_a, PID_t,
                                        ROBOT_GEAR_SETTING, ROBOT_GEAR_RATIO, vex::brakeType::coast);
  m_chassis.DriveDistance(8_ft, 2_ftps, true);
} 

void testBackward() {
  vex::motor ml1 = motor(ROBOT_LEFT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_1_REV);
  vex::motor ml2 = motor(ROBOT_LEFT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_2_REV);
  vex::motor ml3 = motor(ROBOT_LEFT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_3_REV);
  vex::motor mr1 = motor(ROBOT_RIGHT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_1_REV);
  vex::motor mr2 = motor(ROBOT_RIGHT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_2_REV);
  vex::motor mr3 = motor(ROBOT_RIGHT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_3_REV);
  vex::motor_group mg_left{ml1, ml2 ,ml3};
  vex::motor_group mg_right{mr1, mr2, mr3};
  DifferentialDriveChassisPID m_chassis(mg_left, mg_right, 
                                        ROBOT_WHEEL_TRACK, ROBOT_WHEEL_DIAMETER, 
                                        PID_d, PID_a, PID_t,
                                        ROBOT_GEAR_SETTING, ROBOT_GEAR_RATIO, vex::brakeType::coast);
  m_chassis.DriveDistance(-8_ft, 2_ftps, true);
} 

void testTurn() {
  vex::motor ml1 = motor(ROBOT_LEFT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_1_REV);
  vex::motor ml2 = motor(ROBOT_LEFT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_2_REV);
  vex::motor ml3 = motor(ROBOT_LEFT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_LEFT_MOTOR_3_REV);
  vex::motor mr1 = motor(ROBOT_RIGHT_MOTOR_1, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_1_REV);
  vex::motor mr2 = motor(ROBOT_RIGHT_MOTOR_2, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_2_REV);
  vex::motor mr3 = motor(ROBOT_RIGHT_MOTOR_3, ROBOT_GEAR_SETTING, ROBOT_RIGHT_MOTOR_3_REV);
  vex::motor_group mg_left{ml1, ml2 ,ml3};
  vex::motor_group mg_right{mr1, mr2, mr3};
  DifferentialDriveChassisPID m_chassis(mg_left, mg_right, 
                                        ROBOT_WHEEL_TRACK, ROBOT_WHEEL_DIAMETER, 
                                        PID_d, PID_a, PID_t,
                                        ROBOT_GEAR_SETTING, ROBOT_GEAR_RATIO, vex::brakeType::coast);
  m_chassis.TurnAngle(720_deg, 360_dps, true);
}

Pose2d startingPosition;

void setStartingPosition() {
  vex::gps gpsSensor(ROBOT_GPS_PORT, ROBOT_GPS_MOUNT_OFFSET_X, ROBOT_GPS_MOUNT_OFFSET_Y, distanceUnits::in, ROBOT_GPS_MOUNT_OFFSET_HEADING);
  startingPosition = Pose2d(gpsSensor.xPosition(distanceUnits::in) * inch, 
                            gpsSensor.yPosition(distanceUnits::in) * inch,
                            gpsSensor.heading() * degree);
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
  // Set up callbacks for autonomous and driver control periods.
  Competition.bStopAllTasksBetweenModes = false;

  // Run the pre-autonomous function.
  pre_auton();

  // Initialize the display
  initButtons();

  controller c;
  int i = 0;

  // Register the call-back so that when the user presses the `Up`
  // button on the controller, the robot will drive forward what it
  // thinks should be 8 feet.  The user can then dial in the Wheel
  // Diameter parameter from the physical dimension (e.g. 3.25 inches
  // or 4.0 inch diameter) to what makes the robot move the desired
  // distance in reality.
  c.ButtonUp.released(testForward);
  c.ButtonDown.released(testBackward);

  // Register the call-back so that when the user presses the `Right`
  // button on the controller, the robot will turn what it thinks should
  // be 720 degrees. The user can then dial in the Wheel Track parameter
  // physical dimension to what makes the robot turn the desired
  // amount in reality.
  c.ButtonRight.released(testTurn);

  // Advanced users may connect an inertial sensor or GPS to the robot. Configure
  // that device here, and uncomment the line below. In the while loop,
  // uncomment out the code that sends the inertial sensor's reading to
  // the Controller, so the user isn't eye-balling how close to 720 degrees
  // the robot has turned or 8 feet the robot has moved.
  /*
  vex::inertial inertialSensor(ROBOT_INERTIAL_PORT);
  inertialSensor.calibrate();
  while(inertialSensor.isCalibrating()) {
    wait(20, msec);
  }
  */
  /*
  // Physical offset of sensor on the actual robot to the robot's center of rotation
  vex::gps gpsSensor(ROBOT_GPS_PORT, ROBOT_GPS_MOUNT_OFFSET_X, ROBOT_GPS_MOUNT_OFFSET_Y, distanceUnits::in, ROBOT_GPS_MOUNT_OFFSET_HEADING);
  gpsSensor.calibrate();
  while(gpsSensor.isCalibrating()) {
    wait(20, msec);
  }
  // Press the `A` button to set the starting point of the robot
  c.ButtonA.released(setStartingPosition);
  */
  while (1) {
    // This is the main execution loop for the user control program.
    // Each time through the loop your program should update motor + servo
    // values based on feedback from the joysticks.

    // ........................................................................
    // Insert user code here. This is where you use the joystick values to
    // update your motors, etc.
    // ........................................................................
    double a1 = (double)c.Axis1.position(vex::percentUnits::pct) / 100.0;
    double a2 = (double)c.Axis2.position(vex::percentUnits::pct) / 100.0;
    double a3 = (double)c.Axis3.position(vex::percentUnits::pct) / 100.0;

    // We can't write to the Controller's LED very frequently, this should update
    // roughly once every second (e.g. 50 * 20 msec)
    if(i++ > 50) {
      // Display to the controller so we don't overwrite the tuning options on the Brain
      /* Uncomment this if you have an inertial sensor
      double h = inertialSensor.angle();
      c.Screen.clearScreen();
      c.Screen.setCursor(1,1);
      c.Screen.print("Heading: %.1f", h);
      c.Screen.newLine();
      */
      /* Uncomment this if you have a GPS sensor
      c.Screen.clearScreen();
      c.Screen.setCursor(1,1);
      c.Screen.print("GPS: %d, %d, %d ", (int)gpsSensor.xPosition(distanceUnits::in),
                                    (int)gpsSensor.yPosition(distanceUnits::in),
                                    (int)gpsSensor.heading());
      c.Screen.newLine();
      Point2d p(gpsSensor.xPosition(distanceUnits::in) * inch, gpsSensor.yPosition(distanceUnits::in) * inch);
      c.Screen.print("D: %.1f ", startingPosition.DistanceTo(p).convert(inch));
      c.Screen.newLine();
      */
      i = 0;
    }
    wait(20, msec); // Sleep the task for a short amount of time to
                    // prevent wasted resources.
  }
 
}
