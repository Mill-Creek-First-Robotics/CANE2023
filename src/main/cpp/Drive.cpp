#include "Drive.h"

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