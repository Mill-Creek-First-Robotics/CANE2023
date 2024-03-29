#pragma once

#include "Constants.h"

#include <memory>
#include <stdexcept>
#include <frc/SPI.h>
#include <frc/SerialPort.h>
#include "AHRS.h"
#include "ctre/Phoenix.h"

#include <frc/Timer.h>
#include <units/time.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>

using namespace frc;
using namespace std;

enum class DriveMode {
  NORMAL,
  SLOW
};

class Drive {
 public:
 
  Drive(shared_ptr<XboxController>& controller); //Constructor
  void TuxDrive(); //Actual driving
  void Autonomous();
  void TimerReset();

 private:

  DriveMode mode = DriveMode::NORMAL;
  // XboxController m_controller{Constants::Controller::DRIVE_XBOX_CONTROLLER}; //Controller};
  shared_ptr<XboxController> m_controller;
  WPI_TalonSRX m_frontLeft{Constants::MotorControllers::FRONT_LEFT};
  WPI_TalonSRX m_backLeft{Constants::MotorControllers::BACK_LEFT};
  MotorControllerGroup m_left{m_frontLeft, m_backLeft};

  WPI_TalonSRX m_frontRight{Constants::MotorControllers::FRONT_RIGHT};
  WPI_TalonSRX m_backRight{Constants::MotorControllers::BACK_RIGHT};
  MotorControllerGroup m_right{m_frontRight, m_backRight};

  DifferentialDrive m_drive{m_left,m_right};

 
  //AHRS m_gyro{SPI::Port::kMXP};

  Timer m_timer;
};