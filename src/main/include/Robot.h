// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once
#include "Arm.h"
#include "Drive.h"
#include "Constants.h"

#include <string>
#include <memory>

#include <fmt/core.h>
#include <frc/Encoder.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/smartdashboard/SendableChooser.h>

using namespace std;
using namespace frc;

class Robot : public TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void TestInit() override;
  void TestPeriodic() override;
  void SimulationInit() override;
  void SimulationPeriodic() override;

 private:
  /* --=[ DEFAULT VARIABLES ]=-- */
  SendableChooser<string> m_chooser;
  string const kAutoNameDefault = "Default";
  string const kAutoNameCustom = "My Auto";
  string m_autoSelected = kAutoNameCustom;
  /* --=[###################]=-- */
  shared_ptr<XboxController> m_controller = make_shared<XboxController>(Constants::Controller::DRIVE_XBOX_CONTROLLER);
  /* Here are the current Button Bindixngs:
   * A = Toggle grabber (pneumatic piston)
   * B = Move to arm positions based on # of presses. Max three.
   * X = Toggle Arm extended/retracted
   * Left Joystick Y-Axis = Move robot forwards/backwards
   * Right Joystick X-Axis = Rotate robot left/right
   */
  unique_ptr<Arm> m_arm = make_unique<Arm>(m_controller);
  unique_ptr<Drive> m_drive = make_unique<Drive>(m_controller);
};