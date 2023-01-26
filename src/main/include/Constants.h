#pragma once
//#include <frc/Joystick.h> //Just in case...
#include <frc/XboxController.h>

//frc::Joystick joystick{0};
frc::XboxController m_controller{0};//{int index} as defined in driverstation
  /** Button Bindings Overview:
   *  Left Joystick y-axis = move robot forward/back
   *  Right Joystick x-axis = rotate robot left/right
   *  'A' button = toggle the grabber pneumatics extended/retracted
   *  //
   *  //
   *  //
   */

//TalonSRX Motor Controller for the Bosch Seat Motor.
//Need to update when actually wired.
int const ARM_MOTOR_CONTROLLER = 0;
int const PNEUMATICS = 0;

int const FRONT_LEFT_MOTOR = 13;
int const BACK_LEFT_MOTOR = 12;
int const FRONT_RIGHT_MOTOR = 2;
int const BACK_RIGHT_MOTOR = 1;