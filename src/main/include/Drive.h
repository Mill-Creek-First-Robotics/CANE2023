#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Timer.h>
#include <units/time.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
//#include <frc/SpeedControllerGroup.h>
using namespace frc;

class Drive {
 public:
  Drive(); //Constructor
  void TuxDrive(); //Actual driving
  void Autonomous();
  void TimerReset();
  XboxController *getController() {
    return this->m_controller;
  }
  DifferentialDrive *getDrive() {
    return this->m_drivetrain;
  }
 private:
  //This is where the core/essential variables are defined. Used normally here, used as pointers everywhere else.
  //Left Motors
  // type name = new type(args); means dynamic allocation. Object is deleted when we explicitly say so, useful to avoid scope errors.
  WPI_TalonSRX *m_frontLeft = new WPI_TalonSRX(MotorControllerSRX::FRONT_LEFT_MOTOR);
  WPI_TalonSRX *m_backLeft = new WPI_TalonSRX(MotorControllerSRX::BACK_LEFT_MOTOR);
  MotorControllerGroup *m_left = new MotorControllerGroup(*m_frontLeft, *m_backLeft);

  //Right Motors
  WPI_TalonSRX *m_frontRight = new WPI_TalonSRX(MotorControllerSRX::FRONT_RIGHT_MOTOR);
  WPI_TalonSRX *m_backRight = new WPI_TalonSRX(MotorControllerSRX::BACK_RIGHT_MOTOR);
  MotorControllerGroup *m_right = new MotorControllerGroup(*m_frontRight, *m_backRight);

  //Create a differential drive using the two previously defined motor groups.
  DifferentialDrive *m_drivetrain = new DifferentialDrive(*m_left, *m_right);
  //DifferentialDrive *m_driveptr;
  
  XboxController *m_controller = new XboxController(Controller::XBOX_CONTROLLER);
  //XboxController *m_controlptr;
  
  /** Button Bindings Overview:
  *  Left Joystick y-axis = move robot forward/back
  *  Right Joystick x-axis = rotate robot left/right
  *  'A' button = toggle the grabber pneumatics extended/retracted
  *  //
  *  //
  *  //
  */
 
  // Timer *m_timer; //I have no clue if this can be a pointer or not.
  // units::second_t *startTime;
};