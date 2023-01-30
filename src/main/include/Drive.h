#pragma once
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
  Drive(int a, int b, int c, int d, int e) : //Constructor, Initializer List: basically means that m_frontLeft is = to a.
    m_frontLeft(a),
    m_rearLeft(b),
    m_frontRight(c),
    m_rearRight(d),
    m_controller(e) { //Contructor body, end of initializer list
    startTime = m_timer.GetFPGATimestamp();
    m_left.SetInverted(true);
    m_driveptr = &m_drivetrain; //Yay! We now have something to point to.
    m_controlptr = &m_controller;
  }; //end of initializer list
  
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
  WPI_TalonSRX m_frontLeft;
  WPI_TalonSRX m_rearLeft;
  MotorControllerGroup m_left{m_frontLeft, m_rearLeft};

  //Right Motors
  WPI_TalonSRX m_frontRight;
  WPI_TalonSRX m_rearRight;
  MotorControllerGroup m_right{m_frontRight, m_rearRight};

  //Create a differential drive using the two previously defined motor groups.
  DifferentialDrive m_drivetrain{m_left, m_right};
  DifferentialDrive *m_driveptr;
  
  XboxController m_controller;
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