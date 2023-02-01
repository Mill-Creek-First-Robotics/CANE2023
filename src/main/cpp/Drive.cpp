#include "Drive.h"

Drive::Drive() {
    // this->startTime = this->m_timer->GetFPGATimestamp();
    this->m_left->SetInverted(true);
}

void Drive::TuxDrive() {
    this->m_drivetrain->ArcadeDrive(this->m_controller->GetLeftY(),-this->m_controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {
    // if (this->m_timer->GetFPGATimestamp() - this->startTime < (units::second_t)2) {
    //     this->m_drivetrain->ArcadeDrive(-1.0, 0.0); //Move backwards
    // }
    // else {
    //     this->m_drivetrain->ArcadeDrive(0.0, 0.0);
    // }
}

void Drive::TimerReset() {
    // this->startTime = this->m_timer->GetFPGATimestamp();
}