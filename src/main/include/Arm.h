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
  ONE_LOWER = 0
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
  void ArmExtend();
  void ArmRetract();
  void MoveArmJoint();
  void HandleGrabber();
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

  VictorSPX *victor = new VictorSPX(0);

  int const MODE = Mode::DEBUG;

  int UPPER_JOINT_LIMIT;
  int LOWER_JOINT_LIMIT;
  //Limits::Positions CURRENT_JOINT_LIMITS;

  double const JOINT_UPWARDS_SPEED = -0.3;
  double const JOINT_DOWNWARDS_SPEED = 0.3;
  double const EXTEND_SPEED = 0.2;
  double const RETRACT_SPEED = -0.2;

  int const UPPER_EXTENSION_RANGE_LOW  = 500;
  int const UPPER_EXTENSION_RANGE_HIGH = 600;
  int const LOWER_EXTENSION_RANGE_LOW  = 0;
  int const LOWER_EXTENSION_RANGE_HIGH = 100;

  int armJointEncoderDistance;
  int armExtensionEncoderDistance;

  int BPresses;
  units::second_t const BBUTTON_CHECK_INTERVAL = 1_s; 
  Timer BButtonTimer; //Local only, no need for pointers. Timer is off by default.

  bool armExtend;
  bool armRetract;

  //following 4 are for debug purposes
  bool armMovingUp;
  bool armMovingDown;
  bool armIsExtending;
  bool armIsRetracting;
};