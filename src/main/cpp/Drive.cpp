#include "Drive.h"
#include <iostream>

Drive::Drive() {
  m_timer.Start();
  m_left.SetInverted(true);

  //Drivetrain driver options setup on smartdashboard
  chooser.SetDefaultOption(styleDefault, styleDefault);
  for ( string driver : drivers ) {
    chooser.AddOption(driver, driver);
  }
  SmartDashboard::PutData("Who is controlling the Drivetrain: ", &chooser);
}

void Drive::TuxDrive() {
  bindings.UpdateConditions(); //needed to update bindings/controller state.
  //check for mode toggles
  if ( bindings.GetGrabberToggle() ) {
    mode == DriveMode::NORMAL ? mode = DriveMode::PRECISION : mode = DriveMode::NORMAL; 
  }
  if ( bindings.GetDriveUltraSlowModeToggle() ) {
    mode != DriveMode::FINEPRECISION ? mode = DriveMode::FINEPRECISION : mode = DriveMode::NORMAL; 
  }

  double rightY = bindings.GetDriveRightY();
  double leftY = bindings.GetDriveLeftY();
  double rightX = bindings.GetDriveRightX();

  //half speeds if precision mode is on
  if ( mode == DriveMode::PRECISION ) {
    leftY /= 2;
    rightY /= 2;
  }
  if ( mode == DriveMode::FINEPRECISION ) {
    leftY /= 4;
    rightY /= 4;
  }

  //determine drive style based on the current driver selected throuh SendableChooser
  if ( currentDriver == "Default" ) {
    m_drive.ArcadeDrive(leftY, rightY);
  }
  else if ( currentDriver == "Orren" ) {
    m_drive.ArcadeDrive(leftY, rightX * 0.4);
  }
}

void Drive::AutoSimple() {
  if ( m_timer.Get() < 2_s ) {
    m_drive.ArcadeDrive(0.5,0.0);
  }
  if ( m_timer.Get() > 2_s && m_timer.Get() < 4_s) {
    m_drive.ArcadeDrive(-0.5,0.0);
  }
}

void Drive::AutoSimpleForward() {
  if (m_timer.Get() < 2_s) {
    m_drive.ArcadeDrive(0.5,0.0);
  }
}

void Drive::UpdateSelection() {
  currentDriver = chooser.GetSelected();
  bindings.SetCurrentDriver(currentDriver);
}

void Drive::TimerReset() {
  m_timer.Reset();
}