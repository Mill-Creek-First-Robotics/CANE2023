#include "Bindings.hpp"
#include <iostream>

template <typename T>
void Bindings::Configure(T config) {
  driveLeftX = config.driveLeftX;
  driveRightX = config.driveRightX;
  driveLeftY = config.driveLeftY;
  driveRightY = config.driveRightY;
  armLeftX = config.armLeftX;
  armRightX = config.armRightX;
  armLeftY = config.armLeftY;
  armRightY = config.armRightY;
  buttonDriveModeToggle = config.DriveModeToggle;
  buttonArmModeToggle = config.ArmModeToggle;
  buttonArmExtend = config.ArmExtend;
  buttonArmExtendReleased = config.ArmExtendReleased;
  buttonArmRetract = config.ArmRetract;
  buttonArmRetractReleased = config.ArmRetractReleased;
  buttonGrabberToggle = config.GrabberToggle;
  buttonGrabberUp = config.GrabberUp;
  buttonGrabberUpReleased = config.GrabberUpReleased;
  buttonGrabberDown = config.GrabberDown;
  buttonGrabberDownReleased = config.GrabberDownReleased;
  buttonJointUp = config.JointUp;
  buttonJointUpReleased = config.JointUpReleased;
  buttonJointDown = config.JointDown;
  buttonJointDownReleased = config.JointDownReleased;
  buttonObjectPickup = config.ObjectPickup;
  buttonObjectDropoffMid = config.ObjectDropoffMid;
  buttonObjectDropoffHigh = config.ObjectDropoffHigh;
}

void Bindings::UpdateConditions() {
  if ( currentDriver == "Bobby" ) {
    DriverConfig::Bobby bobby{};
    Configure<DriverConfig::Bobby>(bobby);
  }
  else if ( currentDriver == "Calen" ) {
    DriverConfig::Calen calen{};
    Configure<DriverConfig::Calen>(calen);
  }
  else if ( currentDriver == "Orren" ) {
    DriverConfig::Orren orren{};
    Configure<DriverConfig::Orren>(orren);
  }
  else if ( currentDriver == "Landon" ) {
    DriverConfig::Landon landon{};
    Configure<DriverConfig::Landon>(landon);
  }
  else {
    DriverConfig::Default defaultConfig{};
    Configure(defaultConfig);
  }
}

void Bindings::SetCurrentDriver(std::string driver) {
  currentDriver = driver;
}

/* --=#[ GETTER FUNCTIONS ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
double Bindings::GetDriveLeftX() {
  return driveLeftX;
}

double Bindings::GetDriveRightX() {
  return driveRightX;
}

double Bindings::GetDriveLeftY() {
  return driveLeftY;
}

double Bindings::GetDriveRightY() {
  return driveRightY;
}

double Bindings::GetArmLeftX() {
  return armLeftX;
}

double Bindings::GetArmRightX() {
  return armRightX;
}

double Bindings::GetArmLeftY() {
  return armLeftY;
}

double Bindings::GetArmRightY() {
  return armRightY;
}

bool Bindings::GetDriveModeToggle() {
  return buttonDriveModeToggle;
}

bool Bindings::GetArmModeToggle() {
  return buttonArmModeToggle;
}

bool Bindings::GetArmExtend() {
  return buttonArmExtend;
}

bool Bindings::GetArmExtendReleased() {
  return buttonArmExtendReleased;
}

bool Bindings::GetArmRetract() {
  return buttonArmRetract;
}

bool Bindings::GetArmRetractReleased() {
  return buttonArmRetractReleased;
}

bool Bindings::GetGrabberToggle() {
  return buttonGrabberToggle;
}

bool Bindings::GetGrabberUp() {
  return buttonGrabberUp;
}

bool Bindings::GetGrabberUpReleased() {
  return buttonGrabberUpReleased;
}

bool Bindings::GetGrabberDown() {
  return buttonGrabberDown;
}

bool Bindings::GetGrabberDownReleased() {
  return buttonGrabberDownReleased;
}

bool Bindings::GetJointUp() {
  return buttonJointUp;
}

bool Bindings::GetJointUpReleased() {
  return buttonJointUpReleased;
}

bool Bindings::GetJointDown() {
  return buttonJointDown;
}

bool Bindings::GetJointDownReleased() {
  return buttonJointDown;
}

bool Bindings::GetObjectPickup() {
  return buttonObjectPickup;
}

bool Bindings::GetObjectDropoffMid() {
  return buttonObjectDropoffMid;
}

bool Bindings::GetObjectDropoffHigh() {
  return buttonObjectDropoffHigh;
}
/* --=#[ END ]#=-- ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */