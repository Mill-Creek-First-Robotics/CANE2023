#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Timer.h>
#include <units/time.h>
#include <frc/XboxController.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
//#include <frc/SpeedControllerGroup.h>
using namespace frc;

class Drive {
 public:
  Drive(DifferentialDrive *d, XboxController *x); //Constructor
  void TuxDrive(); //Actual driving
  void Autonomous();
  void TimerReset();
 private:
  DifferentialDrive *drive;
  XboxController *controller;
};