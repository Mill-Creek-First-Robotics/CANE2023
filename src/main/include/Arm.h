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
  Arm(XboxController *a, DifferentialDrive *b)
  : arm_controller(&a), //Initializer list
    arm_drive(&b) 
  { //Constructor Body
    pcmCompressor->Disable(); 
    pcmCompressor->EnableDigital();
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
  WPI_TalonSRX *arm = new WPI_TalonSRX(MotorControllerSRX::ARM_MOTOR_CONTROLLER);
  //Define the Compressor and Pneumatic Piston that controls grabber
  //{int compressor, module type}
  Compressor *pcmCompressor = new Compressor(COMPRESSOR, PneumaticsModuleType::CTREPCM);
  //{Module type, int channel}
  Solenoid *grabberPiston = new Solenoid(PneumaticsModuleType::CTREPCM, ChannelSolenoid::ARM_SOLENOID);
  //We will be pointing to a pointer. Fun. 2 *should be* as far as it gets.
  XboxController **arm_controller;
  //Had this listed above **arm_controller. Got a warning "controller will be initialized before drive"
  //As it turns out, order matters. In the initializer list, controller is initialized before drive
  //so- order variable decleration same as the initializer list. Swapping order here fixed that error.
  DifferentialDrive **arm_drive;
};