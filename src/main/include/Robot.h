// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.
#pragma once
#include "Arm.h"
#include "Drive.h"
#include "Constants.h"

#include <string>
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
  string m_autoSelected;
  /* --=[###################]=-- */

  /* --=[ MISC SENSORS ]=-- */


  /* --=[ DRIVETRAIN ]=-- */
  // type name = new type(args); means dynamic allocation. Object is deleted when we explicitly say so, useful to avoid scope errors.
  // new keyword also *always* returns a pointer.
  //Left Motors
  WPI_TalonSRX *m_frontLeft = new WPI_TalonSRX(Constants::MotorControllers::FRONT_LEFT);
  WPI_TalonSRX *m_backLeft = new WPI_TalonSRX(Constants::MotorControllers::BACK_LEFT);
  MotorControllerGroup *m_left = new MotorControllerGroup(*m_frontLeft, *m_backLeft);

  //Right Motors
  WPI_TalonSRX *m_frontRight = new WPI_TalonSRX(Constants::MotorControllers::FRONT_RIGHT);
  WPI_TalonSRX *m_backRight = new WPI_TalonSRX(Constants::MotorControllers::BACK_RIGHT);
  MotorControllerGroup *m_right = new MotorControllerGroup(*m_frontRight, *m_backRight);

  //Create a differential drive using the two previously defined motor groups.
  DifferentialDrive *m_drivetrain = new DifferentialDrive(*m_left, *m_right);
  
  //Drivetrain Controller.
  XboxController *m_controller = new XboxController(Constants::Controller::DRIVE_XBOX_CONTROLLER);
  /* Here are the current Button Bindings:
   * A = Toggle grabber (pneumatic piston)
   * B = Move to arm positions based on # of presses. Max three.
   * X = Toggle Arm extended/retracted
   * Left Joystick Y-Axis = Move robot forwards/backwards
   * Right Joystick X-Axis = Rotate robot left/right
   */
  Drive *m_drive = new Drive (
    this->m_drivetrain,
    this->m_controller
  );
  /* --=[############]=-- */

  /* --=[ ARM & GRABBER ]=-- */
  //int deviceNumber
  WPI_TalonSRX *armJoint = new WPI_TalonSRX(Constants::MotorControllers::ARM_JOINT);
  WPI_TalonSRX *armExtension = new WPI_TalonSRX(Constants::MotorControllers::ARM_EXTENSION);
  WPI_TalonSRX *armGrabberJoint = new WPI_TalonSRX(Constants::MotorControllers::ARM_GRABBER_JOINT);
  //Define the Compressor and Pneumatic Piston that controls grabber
  //{int compressor, module type}
  Compressor *pcmCompressor = new Compressor(Constants::COMPRESSOR, PneumaticsModuleType::CTREPCM);
  //{Module type, int channel}
  Solenoid *grabberPiston = new Solenoid(PneumaticsModuleType::CTREPCM, Constants::Solenoids::ARM_SOLENOID);
  //(int achannel, int bchannel, bool reverseDirection, EncodingType type)
  Encoder *armJointEncoder = new Encoder (
    Constants::Encoders::JOINT_ENCODER_ACHANNEL,
    Constants::Encoders::JOINT_ENCODER_BCHANNEL,
    false,
    Encoder::EncodingType::k4X
  );
  Encoder *armExtensionEncoder = new Encoder (
    Constants::Encoders::EXTEND_ENCODER_ACHANNEL,
    Constants::Encoders::EXTEND_ENCODER_BCHANNEL,
    false,
    Encoder::EncodingType::k4X
  );
  Encoder *armGrabberEncoder = new Encoder (
    Constants::Encoders::GRABBER_ENCODER_ACHANNEL,
    Constants::Encoders::GRABBER_ENCODER_BCHANNEL,
    false,
    Encoder::EncodingType::k4X
  );
  // XboxController *armController = new XboxController(Constants::Controller::ARM_XBOX_CONTROLLER); //if we have seperate controllers
  Arm *m_arm = new Arm (
    this->m_controller,  //armController
    this->m_drivetrain,
    this->grabberPiston,
    this->armJoint,
    this->armGrabberJoint,
    this->armExtension,
    this->armJointEncoder,
    this->armExtensionEncoder,
    this->armGrabberEncoder
  );
  /* --=[###############]=-- */
};