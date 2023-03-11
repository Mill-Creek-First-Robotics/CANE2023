#pragma once

#include "Bindings.hpp"
#include <frc/XboxController.h>
#include <memory>

/**
 * @desc: Configuration for each driver's desired bindings
 * @note: This is the only place where controllers are defined.
 * this DriverConfig namespace works as a wrapper for the controllers.
*/
namespace DriverConfig {
  /**
   * Procedure to add a new driver:
   * 1. add a new struct with all variables like in the other structs
   * 2. add definitions to the struct using arm and driveControllers
   * 3. goto Bindings.cpp and add an if statement in the UpdateConfitions functions
   * that goes related to the driver's name
   * 4. goto Arm.h and Arm.cpp and add the driver's name to the list of options
   * 5. goto Drive.cpp and add the driver's drive style preference (arcade/tank)
   * to the relevant if statements.
   */
  // ================================================================
  /**
   * Procedure to add a new command:
   * 1. add a new bool/double that depends on the controller(s)
   * 2. copy and paste that to each driver struct
   * 3. goto bindings.hpp, add a private member of the same name
   * as that of the variable you  just made.
   * 4. add a public getter function that returns that variable
   * 5. in bindings.cpp, in the Configure function, set the variable name
   * equal to config(the params) variable of the same name.
   * 
   * @example:
   * 1. in struct Default, add "bool doSomething = driveController.GetAButtonPressed();"
   * 2. Copy and paste that to all the other structs
   * 3. in Bindings.hpp, add - under private - "bool buttonDoSomething;"
   * 4. in Bindings.hpp, add - under public - "bool GetDoSomething();" and define it in
   * Bindings.cpp as bool Bindings::GetDoSomething() { return buttonDoSomething; }
   * 5. add "buttonDoSomething = config.doSomething;" under the Configure function in
   * Bindings.cpp
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
    bool DriveSlowModeToggle = driveController->GetLeftStickButtonPressed();
    bool DriveUltraSlowModeToggle = driveController->GetRightStickButtonPressed();
    bool ArmModeToggle = armController->GetLeftStickButtonPressed();
    bool ArmExtend = driveController->GetYButtonPressed();
    bool ArmExtendReleased = driveController->GetYButtonReleased();
    bool ArmRetract = driveController->GetXButtonPressed();
    bool ArmRetractReleased = driveController->GetXButtonReleased();
    bool GrabberToggle = driveController->GetAButtonPressed();
    bool GrabberUp = driveController->GetRightTriggerAxis() > threshold;
    bool GrabberUpReleased = driveController->GetRightTriggerAxis() <= threshold;
    bool GrabberDown = driveController->GetLeftTriggerAxis() > threshold;
    bool GrabberDownReleased = driveController->GetLeftTriggerAxis() <= threshold;
    bool JointUp = driveController->GetRightBumperPressed();
    bool JointUpReleased = driveController->GetRightBumperReleased();
    bool JointDown = driveController->GetLeftBumperPressed();
    bool JointDownReleased = driveController->GetLeftBumperReleased();
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
    bool DriveSlowModeToggle = driveController->GetLeftStickButtonPressed();
    bool DriveUltraSlowModeToggle = driveController->GetRightStickButtonPressed();
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
    bool DriveSlowModeToggle = driveController->GetLeftStickButtonPressed();
    bool DriveUltraSlowModeToggle = driveController->GetRightStickButtonPressed();
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
    bool DriveSlowModeToggle = driveController->GetLeftStickButtonPressed();
    bool DriveUltraSlowModeToggle = driveController->GetRightStickButtonPressed();
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
    bool DriveSlowModeToggle = driveController->GetLeftStickButtonPressed();
    bool DriveUltraSlowModeToggle = driveController->GetRightStickButtonPressed();
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