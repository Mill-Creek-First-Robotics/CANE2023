#pragma once

#include "Constants.h"
#include "ctre/Phoenix.h"

#include <frc/Encoder.h>
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/drive/DifferentialDrive.h>
using namespace frc;

class Arm {
 public:
  Arm(XboxController *x,
      DifferentialDrive *d,
      Solenoid *s,
      WPI_TalonSRX *w,
      WPI_TalonSRX *e,
      WPI_TalonSRX *q,
      Encoder *r,
      Encoder *o
    );
  void MoveToPosition(int pos);
  void CheckControllerState();
  void ArmFirstPosition();
  void ArmSecondPosition();
  void ArmThirdPosition();
  void ArmExtend();
  void ArmRetract();
  void ResetPosition();
  void HandleGrabber();
  void ArmExtend();
  void ArmRetract();
  void MoveVectorMotor(double speed);
 private:
  XboxController *armController;
  DifferentialDrive *armDrive;
  Solenoid *armGrabberPiston;
  WPI_TalonSRX *armJoint;
  WPI_TalonSRX *armExtension;
  WPI_TalonSRX *armJointHelper;
  Encoder *armJointEncoder;
  Encoder *armExtensionEncoder;

  //AOEIBGAOIEBGAEING ADKBFAELBG AILEBG A ILEUBG IAEULBG ILAEBG ILAIEBG ILAUEUBG 
  //Testing Victor Motor
  VictorSPX *vector = new VictorSPX(MotorControllerSRX::TEST_VICTOR_COPY);

  bool armMovingForward;
  bool armMovingBackward;
  bool armIsResetting;
  bool armIsExtending;
  bool armIsRetracting;
  bool armVectorIsMoving;
};