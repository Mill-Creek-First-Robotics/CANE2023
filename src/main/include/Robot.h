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
  SendableChooser<string> m_chooser;
  string const kAutoNameDefault = "Default";
  string const kAutoNameSimple = "Simple auto balance";
  string const kAutoNameSimpleForward = "Simple Forward";
  string m_autoSelected = kAutoNameSimple;
  Arm m_arm{};
  Drive m_drive{};
};