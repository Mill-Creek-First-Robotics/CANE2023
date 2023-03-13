#include "Auto.h"

Auto::Auto() {
    m_timer.Start();
    m_left.SetInverted(true);
}

void Auto::Normal() {
  if (m_timer.Get() < 2_s) { 
    m_drive.ArcadeDrive(0.5, 0.0, false);
  } else {
    m_drive.ArcadeDrive(0.0,0.0);
  }
}

void Auto::Gyro() {
    
}

void Auto::TimerReset() {
  m_timer.Reset();
}