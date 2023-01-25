// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include <frc/TimedRobot.h>
#include <frc/XboxController.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
#include <frc/motorcontrol/Spark.h>
#include "ctre/Phoenix.h"



/*
 * Using the DifferentialDrive class.
 * Runs the motors with split arcade steering and an Xbox controller.
 */
class Robot : public frc::TimedRobot {
 //Defining all motors with their adjacent CAN Buses
  WPI_TalonSRX m_BackleftMotor{12};
  WPI_TalonSRX m_BackrightMotor{1};
  WPI_TalonSRX m_FrontleftMotor{13};     
  WPI_TalonSRX m_FrontrightMotor{2};
// ^ Calling the TalonConrollers using the Web 
//(https://maven.ctr-electronics.com/release/com/ctre/phoenix/Phoenix5-frc2023-latest.json)
   
    frc::MotorControllerGroup m_left{m_BackleftMotor, m_FrontleftMotor};
    frc::MotorControllerGroup m_right{m_BackrightMotor, m_FrontrightMotor};
    frc::DifferentialDrive m_drive{m_left, m_right};
    frc::XboxController m_driverController{0};
// Here we use MotorControllerGroup to group the 2 motors into 1 side of the Drive

 public:
  void RobotInit() override {
    // We need to invert one side of the drivetrain so that positive voltages
    // result in both sides moving forward. Depending on how your robot's
    // gearbox is constructed, you might have to invert the left side instead.
  
    m_right.SetInverted(true);
  }

  void TeleopPeriodic() override {

    m_drive.ArcadeDrive(m_driverController.GetLeftY(),
                             -m_driverController.GetRightX());
  }
};

#ifndef RUNNING_FRC_TESTS
int main() {
  return frc::StartRobot<Robot>();
}
#endif
