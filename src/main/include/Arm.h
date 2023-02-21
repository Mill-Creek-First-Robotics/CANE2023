#pragma once

#include "Constants.h"

#include <memory>

#include <frc/Timer.h>
#include <units/time.h>
#include <frc/Encoder.h>
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

enum Mode {
  DEBUG,
  NORMAL
};

class Arm {
 public:
  Arm(shared_ptr<XboxController>& controller);
  void SetJointAndGrabberLimits(JointPositions pos);
  void SetExtensionLimits(ExtensionPositions pos);
  void MoveWithinLimits (
    WPI_TalonSRX &motor,
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
  //debug functions are for manually moving respective parts
  //useful for getting encoder values to set accurate limits
  void DebugArmJoint();         
  void DebugArmExtension();
  void DebugArmExtend();
  void DebugArmRetract();
 private:
  shared_ptr<XboxController> armController;
  unique_ptr<Solenoid> armGrabberPiston = make_unique<Solenoid>(PneumaticsModuleType::CTREPCM, Solenoids::ARM_SOLENOID);
  unique_ptr<WPI_TalonSRX> armJoint = make_unique<WPI_TalonSRX>(MotorControllers::ARM_JOINT);
  unique_ptr<WPI_TalonSRX> armGrabberJoint = make_unique<WPI_TalonSRX>(MotorControllers::ARM_GRABBER_JOINT);
  unique_ptr<WPI_TalonSRX> armExtension = make_unique<WPI_TalonSRX>(MotorControllers::ARM_EXTENSION);
  unique_ptr<Encoder> armJointEncoder = make_unique<Encoder>(Encoders::JOINT_ENCODER_ACHANNEL, Encoders::JOINT_ENCODER_BCHANNEL);
  unique_ptr<Encoder> armExtensionEncoder = make_unique<Encoder>(Encoders::EXTEND_ENCODER_ACHANNEL, Encoders::EXTEND_ENCODER_BCHANNEL);
  unique_ptr<Encoder> armGrabberEncoder = make_unique<Encoder>(Encoders::GRABBER_ENCODER_ACHANNEL, Encoders::GRABBER_ENCODER_BCHANNEL);
  unique_ptr<Compressor> compressor = make_unique<Compressor>(COMPRESSOR, PneumaticsModuleType::CTREPCM);

  int const MODE = Mode::DEBUG;

  int UPPER_JOINT_LIMIT;
  int LOWER_JOINT_LIMIT;
  int UPPER_GRABBER_LIMIT;
  int LOWER_GRABBER_LIMIT;
  int UPPER_EXTENSION_LIMIT;
  int LOWER_EXTENSION_LIMIT;

  int armJointEncoderDistance;
  int armExtensionEncoderDistance;
  int armGrabberEncoderDistance;

  int BPresses;
  Timer BButtonTimer; //Local only, no need for pointers. Timer is off by default.

  bool armExtensionToggle;

  //following 5 are for debug purposes
  bool armMovingUp;
  bool armMovingDown;
  bool armIsExtending;
  bool armIsRetracting;
  Timer DebugTimer;
 
  bool Brendan;
  bool noseIsBleeding;
};