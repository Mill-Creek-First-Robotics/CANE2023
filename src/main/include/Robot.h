// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once
#include "Arm.h"
#include "Drive.h"
#include "Constants.h"
#include <string>
#include <fmt/core.h>
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
  string const kAutoNameCustom = "My Auto";
  string m_autoSelected;
  //Drivetrain
  Drive m_drive{FRONT_LEFT_MOTOR,BACK_LEFT_MOTOR,FRONT_RIGHT_MOTOR,BACK_RIGHT_MOTOR,CONTROLLER};//Only place constants should be used for now.
  //Arm & Grabber
  Arm m_arm{m_drive.getController(), m_drive.getDrive()};
};