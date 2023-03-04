#pragma once

#include "Constants.h"

#include <memory>

#include <frc/Timer.h>
#include <units/time.h>
#include <frc/Encoder.h>
#include <frc/DutyCycleEncoder.h>
#include <frc/AnalogEncoder.h>
#include "ctre/Phoenix.h"
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/smartdashboard/SmartDashboard.h>

using namespace frc;
using namespace std;
using namespace Constants;
using namespace Constants::Limits;

enum class Mode {
  DEBUG,
  NORMAL
};

class Arm {
 public:
  Arm(shared_ptr<XboxController>& controller);
  void SetJointAndGrabberLimits(JointPositions pos);
  void SetExtensionLimits(ExtensionPositions pos);
  void MoveWithinLimits (
    WPI_TalonSRX* motor,
    int distance,
    double speedf,
    double speedb,
    int limitUpper,
    int limitLower 
  );
  void ArmUpdate();
  void MoveArmExtension();
  void MoveArmJoint();
  void MoveGrabber();
  void HandleGrabberPneumatics();
  void HandleJointInput();
  void HandleExtensionInput();
  
  void AutoMoveArmToPosition(JointPositions pos);
  void AutoExtendArm();
  void AutoRetractArm();
  //debug functions are for manually moving respective parts
  //useful for getting encoder values to set accurate limits
  void DebugArmJoint();         
  void DebugArmExtension();
  void DebugArmExtend();
  void DebugArmRetract();

  // Unit Testing
  WPI_TalonSRX *GetExtensionMotor() {
    return &armExtension;
  }
 private:
  shared_ptr<XboxController> armController;
  WPI_TalonSRX armJoint{MotorControllers::ARM_JOINT};
  WPI_TalonSRX armGrabberJoint{MotorControllers::ARM_GRABBER_JOINT};
  WPI_TalonSRX armExtension{MotorControllers::ARM_EXTENSION};
  Encoder armJointEncoder{Encoders::JOINT_ENCODER_ACHANNEL, Encoders::JOINT_ENCODER_BCHANNEL};
  Encoder armExtensionEncoder{Encoders::EXTEND_ENCODER_ACHANNEL, Encoders::EXTEND_ENCODER_BCHANNEL};
  AnalogEncoder armGrabberEncoder{Encoders::GRABBER_ENCODER};
  Solenoid armGrabberPiston{PneumaticsModuleType::CTREPCM, Solenoids::ARM_SOLENOID};
  Compressor compressor{COMPRESSOR, PneumaticsModuleType::CTREPCM};

  Mode MODE = Mode::DEBUG;

  double UPPER_JOINT_LIMIT;
  double LOWER_JOINT_LIMIT;
  double UPPER_GRABBER_LIMIT;
  double LOWER_GRABBER_LIMIT;
  double UPPER_EXTENSION_LIMIT;
  double LOWER_EXTENSION_LIMIT;

  double armJointEncoderDistance;
  double armExtensionEncoderDistance;
  double armGrabberEncoderDistance;

  int BPresses;
  Timer BButtonTimer; //Local only, no need for pointers. Timer is off by default.

  bool armExtensionToggle;

  //following 5 are for debug purposes
  bool armMovingUp;
  bool armMovingDown;
  bool armIsExtending;
  bool armIsRetracting;
};