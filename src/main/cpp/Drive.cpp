#include "Drive.h"
#include <iostream>

Drive::Drive() {
  m_timer.Start();
  m_left.SetInverted(true);

  chooser.SetDefaultOption(styleDefault, styleDefault);
  for ( string driver : drivers ) {
    chooser.AddOption(driver, driver);
  }
  SmartDashboard::PutData("Who is controlling the Drivetrain: ", &chooser);
}

void Drive::TuxDrive() {
  bindings.UpdateConditions();
  //check for mode toggle
  if ( bindings.GetDriveModeToggle() ) {
    mode == DriveMode::NORMAL ? mode = DriveMode::PRECISION : mode = DriveMode::NORMAL; 
  }

  double rightY = bindings.GetDriveRightY();
  double leftY = bindings.GetDriveLeftY();
  double rightX = bindings.GetDriveRightX();

  //half speeds if precision mode is on
  if ( mode == DriveMode::PRECISION ) {
    leftY /= 2;
    rightY /= 2;
  }

  //determine drive style based on the current driver selected throuh SendableChooser
  if ( currentDriver == "Default" ) {
    m_drive.TankDrive(leftY, rightY);
  }
  else if ( currentDriver == "Orren" ) {
    m_drive.ArcadeDrive(leftY, rightX * 0.4);
  }
}

void Drive::Autonomous() {
  
}

void Drive::UpdateSelection() {
  currentDriver = chooser.GetSelected();
  bindings.SetCurrentDriver(currentDriver);
}