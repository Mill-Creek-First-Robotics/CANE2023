#pragma once

#include "Constants.h"
#include "Bindings.hpp"

#include <memory>
#include <stdexcept>
#include <frc/SPI.h>
#include <frc/SerialPort.h>
#include "AHRS.h"
#include "ctre/Phoenix.h"

#include <frc/Timer.h>
#include <units/time.h>
#include <units/dimensionless.h>
#include <units/acceleration.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

using namespace frc;
using namespace std;

enum class DriveMode {
  NORMAL,
  PRECISION
};

class Drive {
 public:
  Drive();
  void TuxDrive(); //Actual driving
  void Autonomous();
  void UpdateSelection();
  void UpdateBindings();
 private:
  SendableChooser<string> chooser;
  string const styleDefault = "Default";
  /* --=#[ DRIVERS ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~ */
  string const drivers[4] = {
    "Bobby",
    "Calen",
    "Orren",
    "Landon"
  };
  string currentDriver = styleDefault; //selected
  /* --=#[ END ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */

  DriveMode mode = DriveMode::NORMAL;
  Bindings bindings;

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