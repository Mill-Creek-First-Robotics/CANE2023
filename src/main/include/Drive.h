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
    return m_controlptr;
  }
  DifferentialDrive *getDrive() {
    return m_driveptr;
  }
 private:
  //This is where the core/essential variables are defined. Used normally here, used as pointers everywhere else.
  //Left Motors
  WPI_TalonSRX m_frontLeft{FRONT_LEFT_MOTOR};
  WPI_TalonSRX m_backLeft{BACK_LEFT_MOTOR};
  MotorControllerGroup m_left{m_frontLeft, m_backLeft};

  //Right Motors
  WPI_TalonSRX m_frontRight{FRONT_RIGHT_MOTOR};
  WPI_TalonSRX m_backRight{BACK_RIGHT_MOTOR};
  MotorControllerGroup m_right{m_frontRight, m_backRight};

  //Create a differential drive using the two previously defined motor groups.
  DifferentialDrive m_drivetrain{m_left, m_right};
  DifferentialDrive *m_driveptr;
  
  XboxController m_controller{CONTROLLER};
  XboxController *m_controlptr;
  
  /** Button Bindings Overview:
  *  Left Joystick y-axis = move robot forward/back
  *  Right Joystick x-axis = rotate robot left/right
  *  'A' button = toggle the grabber pneumatics extended/retracted
  *  //
  *  //
  *  //
  */
  Timer m_timer;
  units::second_t startTime;
};