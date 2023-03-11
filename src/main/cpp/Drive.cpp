#include "Drive.h"
#include <iostream>

Drive::Drive(shared_ptr<XboxController>& controller) : m_controller(controller) {
  m_timer.Start();
  m_left.SetInverted(true);
}

void Drive::TuxDrive() {
  m_drive.ArcadeDrive(m_controller->GetLeftY(),m_controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {
   
    if (m_timer.Get() < 2_s) {
      
      m_drive.ArcadeDrive(-0.5, 0.0, false);
    } else {
      
      m_drive.ArcadeDrive(0.0, 0.0, false);
    }
  

    if (m_timer.Get() < 4_s && m_timer.Get() > 2_s) {
      
      m_drive.ArcadeDrive(0.5, 0.0, false);
    } else {
      
      m_drive.ArcadeDrive(0.0, 0.0, false);
    }
  }