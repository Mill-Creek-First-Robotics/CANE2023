#include "Drive.h"

Drive::Drive(DifferentialDrive *d, XboxController *x)
:
drive(d),
controller(x) 
{/* Empty Constructor Body*/}

void Drive::TuxDrive() {
    drive->ArcadeDrive(controller->GetLeftY(),-controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {}

void Drive::TimerReset() {}