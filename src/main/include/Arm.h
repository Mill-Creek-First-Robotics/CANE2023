#pragma once

#include "Constants.h"

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
using namespace Constants;
using namespace Constants::Limits;

enum Mode {
  DEBUG,
  NORMAL
};

class Arm {
 public:
  Arm (
    XboxController *a,
    DifferentialDrive *b,
    Solenoid *c,
    WPI_TalonSRX *d,
    WPI_TalonSRX *e,
    WPI_TalonSRX *f,
    Encoder *g,
    Encoder *h,
    Encoder *i
  );
  void SetJointAndGrabberLimits(JointPositions pos);
  void SetExtensionLimits(ExtensionPositions pos);
  void MoveWithinLimits (
    WPI_TalonSRX *motor,
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
  XboxController *armController;
  DifferentialDrive *armDrive;
  Solenoid *armGrabberPiston;
  WPI_TalonSRX *armJoint;
  WPI_TalonSRX *armGrabberJoint;
  WPI_TalonSRX *armExtension;
  Encoder *armJointEncoder;
  Encoder *armExtensionEncoder;
  Encoder *armGrabberEncoder;

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