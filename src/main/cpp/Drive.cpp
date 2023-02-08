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