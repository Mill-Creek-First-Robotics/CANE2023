#pragma once

#include "Constants.h"
#include "DriverConfig.hpp"
#include <memory>
#include <iostream>
#include <frc/XboxController.h>

class Bindings {
 public:
  template <typename T = DriverConfig::Default>
  void Configure(T config);
  void UpdateConditions();
  void SetCurrentDriver(std::string driver);
  //getters
  double GetDriveLeftX();
  double GetDriveRightX();
  double GetDriveLeftY();
  double GetDriveRightY();
  double GetArmLeftX();
  double GetArmRightX();
  double GetArmLeftY();
  double GetArmRightY();
  bool GetDriveModeToggle();
  bool GetArmModeToggle();
  bool GetArmExtend();
  bool GetArmExtendReleased();
  bool GetArmRetract();
  bool GetArmRetractReleased();
  bool GetGrabberToggle();
  bool GetGrabberUp();
  bool GetGrabberUpReleased();
  bool GetGrabberDown();
  bool GetGrabberDownReleased();
  bool GetJointUp();
  bool GetJointUpReleased();
  bool GetJointDown();
  bool GetJointDownReleased();
  bool GetObjectPickup();
  bool GetObjectDropoffMid();
  bool GetObjectDropoffHigh();
 private:
  std::string currentDriver;
  double driveLeftX;
  double driveRightX;
  double driveLeftY;
  double driveRightY;
  double armLeftX;
  double armRightX;
  double armLeftY;
  double armRightY;
  bool buttonDriveModeToggle;
  bool buttonArmModeToggle;
  bool buttonArmExtend;
  bool buttonArmExtendReleased;
  bool buttonArmRetract;
  bool buttonArmRetractReleased;
  bool buttonGrabberToggle;
  bool buttonGrabberUp;
  bool buttonGrabberUpReleased;
  bool buttonGrabberDown;
  bool buttonGrabberDownReleased;
  bool buttonJointUp;
  bool buttonJointUpReleased;
  bool buttonJointDown;
  bool buttonJointDownReleased;
  bool buttonObjectPickup;
  bool buttonObjectDropoffMid;
  bool buttonObjectDropoffHigh;
};