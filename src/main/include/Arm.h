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
      Encoder *r
    );
  void MoveToPosition(int pos);
  void CheckControllerState();
  void ArmFirstPosition();
  void ArmSecondPosition();
  void ArmThirdPosition();
  void ResetPosition();
  void HandleGrabber();
  void ArmExtend();
  void ArmRetract();
 private:
  XboxController *armController;
  DifferentialDrive *armDrive;
  Solenoid *armGrabberPiston;
  WPI_TalonSRX *armJoint;
  WPI_TalonSRX *armExtension;
  Encoder *armEncoder;
  VictorSPX *vector = new VictorSPX(MotorControllerSRX::TEST_VICTOR_COPY);

  bool armIsMoving;
};