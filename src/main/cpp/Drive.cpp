#include "Drive.h"
#include <iostream>

Drive::Drive(shared_ptr<XboxController>& controller) : m_controller(controller) {
  m_timer.Start();
}

void Drive::TuxDrive() {
  m_drive.ArcadeDrive(m_controller->GetLeftY(),-m_controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {
  
}