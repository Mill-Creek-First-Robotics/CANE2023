#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/drive/DifferentialDrive.h>
using namespace frc;

class Arm {
 public:
  Arm(XboxController *x, DifferentialDrive *d, Solenoid *s, WPI_TalonSRX *w, WPI_TalonSRX *e);
  void MoveToPosition(int pos);
  void CheckControllerState();
  void ArmFirstPosition();
  void ArmSecondPosition();
  void ArmThirdPosition();
  void ArmExtend();
  void ArmRetract();
  void ResetPosition();
  void HandleGrabber();
 private:
  XboxController *armController;
  DifferentialDrive *armDrive;
  Solenoid *armGrabberPiston;
  WPI_TalonSRX *armJoint;
  WPI_TalonSRX *armExtension;

  bool isMoving;
};