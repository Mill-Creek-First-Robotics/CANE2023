#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Solenoid.h>
#include <frc/Compressor.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
using namespace frc;

class Arm {
 public:
  Arm();
  void MoveToPosition(int pos);
  void CheckControllerState();
  void ArmFirstPosition();
  void ArmSecondPosition();
  void ArmThirdPosition();
  void ResetPosition();
  void HandleGrabber();
 private:
  //int deviceNumber
  WPI_TalonSRX armController{ARM_MOTOR_CONTROLLER};

  //Define the Compressor and Pneumatic Piston that controls grabber
  //{int compressor, module type}
  Compressor pcmCompressor{PNEUMATICS, PneumaticsModuleType::CTREPCM};
  //{Module type, int channel}

  XboxController *m_controller{0};

  Solenoid grabberPiston{PneumaticsModuleType::CTREPCM, 1};
};