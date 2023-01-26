#include "Drive.h"
#include <units/second_t.h>

units::second_t startTime;

Drive::Drive() {
    startTime = m_timer.GetFPGATimestamp();
    m_left.SetInverted(true);
}

void Drive::TuxDrive() {
    m_drive.ArcadeDrive(m_controller.GetLeftY(),-m_controller.GetRightX() * 0.6);
}

void Drive::Autonomous() {
    if (m_timer.GetFPGATimestamp() - startTime < (units::second_t)2) {
        m_drive.ArcadeDrive(-1.0, 0.0); //Move backwards
    }
    else {
        m_drive.ArcadeDrive(0.0, 0.0);
    }
}

void Drive::TimerReset() {
    startTime = m_timer.GetFPGATimestamp();
}

void Drive::Balance() {
    //TODO: Write balancing code for charging station placement.
}

void Drive::ToggleBrakes() {
    //TODO: Write code to toggle brakes if we go that route. Should be called from Balance.
}