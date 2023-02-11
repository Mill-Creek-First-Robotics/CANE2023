#pragma once

#include "Constants.h"
#include "ctre/Phoenix.h"

#include <frc/Timer.h>
#include <units/time.h>
#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/drive/DifferentialDrive.h>

using namespace frc;

//Limits for the arm positions
struct Limits {
enum Positions {
  POS1,
  POS2,
  POS3
};

enum POS1 {
  ONE_UPPER = 300,
  ONE_LOWER = 100
};

enum POS2 {
  TWO_UPPER = 600,
  TWO_LOWER = 400
};

enum POS3 {
  THREE_UPPER = 900,
  THREE_LOWER = 700
};
}; //struct Limits

enum Mode {
  DEBUG,
  NORMAL
};

class Arm {
 public:
  Arm(XboxController *x,
      DifferentialDrive *d,
      Solenoid *s,
      WPI_TalonSRX *w,
      WPI_TalonSRX *e,
      Encoder *r,
      Encoder *o
    );
  void SetJointLimits(Limits::Positions pos);
  void ArmUpdate();
  void CheckControllerState();
  void ResetPosition();
  void ArmExtend();
  void ArmRetract();
  void HandleGrabber();
  void MoveArmJoint();
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
  WPI_TalonSRX *armExtension;
  Encoder *armJointEncoder;
  Encoder *armExtensionEncoder;

  double const EXTEND_SPEED = 0.2;
  double const RETRACT_SPEED = -0.2;
  double const JOINT_UPWARDS_SPEED = 0.5;
  double const JOINT_DOWNWARDS_SPEED = 0.2;

  int armJointEncoderDistance;
  int armExtensionEncoderDistance;

  int UPPER_JOINT_LIMIT;
  int LOWER_JOINT_LIMIT;
  //Limits::Positions CURRENT_JOINT_LIMITS;

  int BPresses;
  units::second_t BBUTTON_CHECK_INTERVAL; 
  Timer BButtonTimer; //Local only, no need for pointers. Timer is off by default.

  int UPPER_EXTENSION_RANGE_LOW;
  int UPPER_EXTENSION_RANGE_HIGH;
  int LOWER_EXTENSION_RANGE_LOW;
  int LOWER_EXTENSION_RANGE_HIGH;

  bool armMovingUp;
  bool armMovingDown;
  bool armIsExtending;
  bool armIsRetracting;
  bool armExtend;
  bool armRetract;

  int MODE;
};