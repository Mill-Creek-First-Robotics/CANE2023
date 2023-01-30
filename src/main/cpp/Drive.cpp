#include "Drive.h"

Drive::Drive() {
    startTime = m_timer.GetFPGATimestamp();
    m_left.SetInverted(true);
    m_driveptr = &m_drivetrain; //Yay! We now have something to point to. Thats why this is in the constructor.
    m_controlptr = &m_controller;
}

void Drive::TuxDrive() {
    m_drivetrain.ArcadeDrive(m_controller.GetLeftY(),-m_controller.GetRightX() * 0.6);
}

void Drive::Autonomous() {
    if (m_timer.GetFPGATimestamp() - startTime < (units::second_t)2) {
        m_drivetrain.ArcadeDrive(-1.0, 0.0); //Move backwards
    }
    else {
        m_drivetrain.ArcadeDrive(0.0, 0.0);
    }
}

void Drive::TimerReset() {
    startTime = m_timer.GetFPGATimestamp();
}