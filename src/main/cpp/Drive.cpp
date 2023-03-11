#include "Drive.h"
#include <iostream>

Drive::Drive(shared_ptr<XboxController>& controller) : m_controller(controller) {
  m_timer.Start();
  m_left.SetInverted(true);
}

void Drive::TuxDrive() {
  if (m_controller->GetLeftStickButtonPressed()) {
    mode == DriveMode::NORMAL ? mode = DriveMode::SLOW : mode = DriveMode::NORMAL;
  }
  double leftY = m_controller->GetLeftY();
  double rightX = m_controller->GetRightX();
  if (mode == DriveMode::SLOW) {
    leftY /= 2;
    rightX /= 2;
  }
  m_drive.ArcadeDrive(leftY,rightX);
}

void Drive::Autonomous() {
  if (m_timer.Get() < 2_s) { 
    m_drive.ArcadeDrive(-0.5, 0.0, false);
  }

  if (m_timer.Get() < 4_s && m_timer.Get() > 2_s) {
    m_drive.ArcadeDrive(0.5, 0.0, false);
  } else if (m_timer.Get() > 4_s) {
    m_drive.ArcadeDrive(0.0, 0.0, false);
  }
}