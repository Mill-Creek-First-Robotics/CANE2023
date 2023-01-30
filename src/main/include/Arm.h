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
  Arm(XboxController *a, DifferentialDrive *b){
    arm_drive = &b; //pointer pointer = reference pointer. normally pointer = reference. Add pointer to both sides!
    arm_controller = &a;
    pcmCompressor.Disable();
    pcmCompressor.EnableDigital();
  };
  void MoveToPosition(int pos);
  void CheckControllerState();
  void ArmFirstPosition();
  void ArmSecondPosition();
  void ArmThirdPosition();
  void ResetPosition();
  void HandleGrabber();
 private:
  //int deviceNumber
  WPI_TalonSRX arm{ARM_MOTOR_CONTROLLER};
  //Define the Compressor and Pneumatic Piston that controls grabber
  //{int compressor, module type}
  Compressor pcmCompressor{PNEUMATICS, PneumaticsModuleType::CTREPCM};
  //{Module type, int channel}
  Solenoid grabberPiston{PneumaticsModuleType::CTREPCM, SOLENOID};

  DifferentialDrive **arm_drive;   //We will be pointing to a pointer. Fun. 2 *should be* as far as it gets.
  XboxController **arm_controller;
};