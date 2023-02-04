#include "Drive.h"

Drive::Drive(DifferentialDrive *d, XboxController *x)
:
drive(d),
controller(x) 
{
    // this->startTime = this->m_timer->GetFPGATimestamp();
}

void Drive::TuxDrive() {
    drive->ArcadeDrive(controller->GetLeftY(),-controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {
    // if (m_timer->GetFPGATimestamp() - startTime < (units::second_t)2) {
    //     m_drivetrain->ArcadeDrive(-1.0, 0.0); //Move backwards
    // }
    // else {
    //     m_drivetrain->ArcadeDrive(0.0, 0.0);
    // }
}

void Drive::TimerReset() {
    // this->startTime = this->m_timer->GetFPGATimestamp();
}