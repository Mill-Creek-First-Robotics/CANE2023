#pragma once

#include "Bindings.hpp"
#include <frc/XboxController.h>
#include <memory>

/**
 * @desc: Configuration for each driver's desired bindings
*/
namespace DriverConfig {
  /**
   * Precidure to add a new driver
   * 1. add a new struct with all variables like in the other structs
   * 2. add definitions to the struct using arm and driveControllers
   * 3. goto Bindings.cpp and add an if statement in the UpdateConfitions functions
   * that goes related to the driver's name
   * 4. goto Arm.h and Arm.cpp and add the driver's name to the list of options
   * 5. goto Drive.cpp and add the driver's drive style preference (arcade/tank)
   * to the relevant if statements.
   */
  std::unique_ptr<frc::XboxController> const driveController = std::make_unique<frc::XboxController>(Constants::Controller::DRIVE_XBOX_CONTROLLER);
  std::unique_ptr<frc::XboxController> const armController = std::make_unique<frc::XboxController>(Constants::Controller::ARM_XBOX_CONTROLLER);
  struct Default {
    double const threshold = 0.8; //0.0 <-> 1.0
    double driveLeftX = driveController->GetLeftX();
    double driveRightX = driveController->GetRightX();
    double driveLeftY = driveController->GetLeftY();
    double driveRightY = driveController->GetRightY();
    double armLeftX = armController->GetLeftX();
    double armRightX = armController->GetRightX();
    double armLeftY = armController->GetLeftY();
    double armRightY = armController->GetRightY();
    bool DriveModeToggle = driveController->GetLeftStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = armController->GetYButtonPressed();
    bool ArmExtendReleased = armController->GetYButtonReleased();
    bool ArmRetract = armController->GetXButtonPressed();
    bool ArmRetractReleased = armController->GetXButtonReleased();
    bool GrabberToggle = armController->GetAButtonPressed();
    bool GrabberUp = armController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = armController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = armController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = armController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = armController->GetRightBumperPressed();
    bool JointUpReleased = armController->GetRightBumperReleased();
    bool JointDown = armController->GetLeftBumperPressed();
    bool JointDownReleased = armController->GetLeftBumperReleased();
    bool ObjectPickup;
    bool ObjectDropoffMid;
    bool ObjectDropoffHigh;
  };
  struct Bobby {
    double const threshold = 0.8; //0.0 <-> 1.0
    double driveLeftX = driveController->GetLeftX();
    double driveRightX = driveController->GetRightX();
    double driveLeftY = driveController->GetLeftY();
    double driveRightY = driveController->GetRightY();
    double armLeftX = armController->GetLeftX();
    double armRightX = armController->GetRightX();
    double armLeftY = armController->GetLeftY();
    double armRightY = armController->GetRightY();
    bool DriveModeToggle = driveController->GetLeftStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = armController->GetYButtonPressed();
    bool ArmExtendReleased = armController->GetYButtonReleased();
    bool ArmRetract = armController->GetXButtonPressed();
    bool ArmRetractReleased = armController->GetXButtonReleased();
    bool GrabberToggle = armController->GetAButtonPressed();
    bool GrabberUp = armController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = armController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = armController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = armController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = armController->GetRightBumperPressed();
    bool JointUpReleased = armController->GetRightBumperReleased();
    bool JointDown = armController->GetLeftBumperPressed();
    bool JointDownReleased = armController->GetLeftBumperReleased();
    bool ObjectPickup;
    bool ObjectDropoffMid;
    bool ObjectDropoffHigh;
  };
  struct Calen {
    double const threshold = 0.8; //0.0 <-> 1.0
    double driveLeftX = driveController->GetLeftX();
    double driveRightX = driveController->GetRightX();
    double driveLeftY = driveController->GetLeftY();
    double driveRightY = driveController->GetRightY();
    double armLeftX = armController->GetLeftX();
    double armRightX = armController->GetRightX();
    double armLeftY = armController->GetLeftY();
    double armRightY = armController->GetRightY();
    bool DriveModeToggle = driveController->GetLeftStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = armController->GetYButtonPressed();
    bool ArmExtendReleased = armController->GetYButtonReleased();
    bool ArmRetract = armController->GetXButtonPressed();
    bool ArmRetractReleased = armController->GetXButtonReleased();
    bool GrabberToggle = armController->GetAButtonPressed();
    bool GrabberUp = armController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = armController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = armController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = armController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = armController->GetRightBumperPressed();
    bool JointUpReleased = armController->GetRightBumperReleased();
    bool JointDown = armController->GetLeftBumperPressed();
    bool JointDownReleased = armController->GetLeftBumperReleased();
    bool ObjectPickup;
    bool ObjectDropoffMid;
    bool ObjectDropoffHigh;
  };
  struct Orren {
    double const threshold = 0.8; //0.0 <-> 1.0
    double driveLeftX = driveController->GetLeftX();
    double driveRightX = driveController->GetRightX();
    double driveLeftY = driveController->GetLeftY();
    double driveRightY = driveController->GetRightY();
    double armLeftX = armController->GetLeftX();
    double armRightX = armController->GetRightX();
    double armLeftY = armController->GetLeftY();
    double armRightY = armController->GetRightY();
    bool DriveModeToggle = driveController->GetLeftStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = armController->GetYButtonPressed();
    bool ArmExtendReleased = armController->GetYButtonReleased();
    bool ArmRetract = armController->GetXButtonPressed();
    bool ArmRetractReleased = armController->GetXButtonReleased();
    bool GrabberToggle = armController->GetAButtonPressed();
    bool GrabberUp = armController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = armController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = armController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = armController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = armController->GetRightBumperPressed();
    bool JointUpReleased = armController->GetRightBumperReleased();
    bool JointDown = armController->GetLeftBumperPressed();
    bool JointDownReleased = armController->GetLeftBumperReleased();
    bool ObjectPickup;
    bool ObjectDropoffMid;
    bool ObjectDropoffHigh;
  };
  struct Landon {
    double const threshold = 0.8; //0.0 <-> 1.0
    double driveLeftX = driveController->GetLeftX();
    double driveRightX = driveController->GetRightX();
    double driveLeftY = driveController->GetLeftY();
    double driveRightY = driveController->GetRightY();
    double armLeftX = armController->GetLeftX();
    double armRightX = armController->GetRightX();
    double armLeftY = armController->GetLeftY();
    double armRightY = armController->GetRightY();
    bool DriveModeToggle = driveController->GetLeftStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = armController->GetYButtonPressed();
    bool ArmExtendReleased = armController->GetYButtonReleased();
    bool ArmRetract = armController->GetXButtonPressed();
    bool ArmRetractReleased = armController->GetXButtonReleased();
    bool GrabberToggle = armController->GetAButtonPressed();
    bool GrabberUp = armController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = armController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = armController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = armController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = armController->GetRightBumperPressed();
    bool JointUpReleased = armController->GetRightBumperReleased();
    bool JointDown = armController->GetLeftBumperPressed();
    bool JointDownReleased = armController->GetLeftBumperReleased();
    bool ObjectPickup;
    bool ObjectDropoffMid;
    bool ObjectDropoffHigh;
  };
};