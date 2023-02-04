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
  /* --=[ DEFAULT VARIABLES ]=-- */
  SendableChooser<string> m_chooser;
  string const kAutoNameDefault = "Default";
  string const kAutoNameCustom = "My Auto";
  string m_autoSelected;
  /* --=[###################]=-- */

  /* --=[ DRIVETRAIN ]=-- */
  // type name = new type(args); means dynamic allocation. Object is deleted when we explicitly say so, useful to avoid scope errors.
  // new keyword also *always* returns a pointer.
  //Left Motors
  WPI_TalonSRX *m_frontLeft = new WPI_TalonSRX(MotorControllerSRX::FRONT_LEFT_MOTOR);
  WPI_TalonSRX *m_backLeft = new WPI_TalonSRX(MotorControllerSRX::BACK_LEFT_MOTOR);
  MotorControllerGroup *m_left = new MotorControllerGroup(*m_frontLeft, *m_backLeft);

  //Right Motors
  WPI_TalonSRX *m_frontRight = new WPI_TalonSRX(MotorControllerSRX::FRONT_RIGHT_MOTOR);
  WPI_TalonSRX *m_backRight = new WPI_TalonSRX(MotorControllerSRX::BACK_RIGHT_MOTOR);
  MotorControllerGroup *m_right = new MotorControllerGroup(*m_frontRight, *m_backRight);

  //Create a differential drive using the two previously defined motor groups.
  DifferentialDrive *m_drivetrain = new DifferentialDrive(*m_left, *m_right);
  
  //Drivetrain Controller.
  XboxController *m_controller = new XboxController(Controller::DRIVE_XBOX_CONTROLLER);
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
  Drive *m_drive = new Drive
    (
      this->m_drivetrain,
      this->m_controller
    );
  /* --=[############]=-- */

  /* --=[ ARM & GRABBER ]=-- */
  //int deviceNumber
  WPI_TalonSRX *armJoint = new WPI_TalonSRX(MotorControllerSRX::ARM_JOINT_MOTOR_CONTROLLER);
  WPI_TalonSRX *armExtension = new WPI_TalonSRX(MotorControllerSRX::ARM_EXTENSION_MOTOR_CONTROLLER);
  //Define the Compressor and Pneumatic Piston that controls grabber
  //{int compressor, module type}
  Compressor *pcmCompressor = new Compressor(COMPRESSOR, PneumaticsModuleType::CTREPCM);
  //{Module type, int channel}
  Solenoid *grabberPiston = new Solenoid(PneumaticsModuleType::CTREPCM, ChannelSolenoid::ARM_SOLENOID);
  // XboxController *armController = new XboxController(Controller::ARM_XBOX_CONTROLLER); //if we have seperate controllers
  Arm *m_arm = new Arm
    (
      this->m_controller,  //armController
      this->m_drivetrain,
      this->grabberPiston,
      this->armJoint,
      this->armExtension
    );
  /* --=[###############]=-- */
};