#pragma once

#include "Constants.h"

#include <memory>

#include "ctre/Phoenix.h"
#include <frc/Timer.h>
#include <units/time.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
//#include <frc/SpeedControllerGroup.h>
using namespace frc;
using namespace std;

class Drive {
 public:

  Drive(shared_ptr<XboxController>& controller); //Constructor
  void TuxDrive(); //Actual driving
  void Autonomous();

 private:
  
  shared_ptr<XboxController> m_controller;
  unique_ptr<WPI_TalonSRX> m_frontLeft = make_unique<WPI_TalonSRX>(Constants::MotorControllers::FRONT_LEFT);
  unique_ptr<WPI_TalonSRX> m_backLeft = make_unique<WPI_TalonSRX>(Constants::MotorControllers::BACK_LEFT);
  unique_ptr<MotorControllerGroup> m_left = make_unique<MotorControllerGroup>(*m_frontLeft, *m_backLeft);

  unique_ptr<WPI_TalonSRX> m_frontRight = make_unique<WPI_TalonSRX>(Constants::MotorControllers::FRONT_RIGHT);
  unique_ptr<WPI_TalonSRX> m_backRight = make_unique<WPI_TalonSRX>(Constants::MotorControllers::BACK_RIGHT);
  unique_ptr<MotorControllerGroup> m_right = make_unique<MotorControllerGroup>(*m_frontRight, *m_backRight);

  unique_ptr<DifferentialDrive> m_drive = make_unique<DifferentialDrive>(*m_left,*m_right);

  Timer m_timer;
};