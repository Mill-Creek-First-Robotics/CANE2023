#include "Auto.h"

Auto::Auto(DifferentialDrive *d)
: //Initializer list
autoDrive(d)            //armDrive = d; etc...
{
  this->startTime = frc2::Timer::GetFPGATimestamp();
};

void Auto::AutoCenter() {
    /**
     * Autonomous function for starting in the center starting area.
     * 
     * @param[in] d Pointer to Differential Drive
    */
   if (frc2::Timer::GetFPGATimestamp() - this->startTime < (units::second_t)2) {
         this->autoDrive->ArcadeDrive(-1.0, 0.0); //Move backwards
     }
     else {
         this->autoDrive->ArcadeDrive(0.0, 0.0);
     }
};

void Auto::TimerReset() {
    // this->startTime = frc2::Timer::GetFPGATimestamp();
}