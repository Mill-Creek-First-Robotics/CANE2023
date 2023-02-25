#include "Auto.h"

Auto::Auto(DifferentialDrive *d)
: //Initializer list
autoDrive(d)            //armDrive = d; etc...
{
  TimerReset();
};

void Auto::AutoCenter() {
    /**
     * Autonomous function for starting in the center starting area.
     * 
     * @param[in] d Pointer to Differential Drive
    */
  if (timer.GetFPGATimestamp() - startTime < (units::second_t)2) {
    this->autoDrive->ArcadeDrive(-1.0, 0.0); //Move backwards for 2 seconds
  }
  else {
    this->autoDrive->ArcadeDrive(0.0, 0.0);
  }
};

void Auto::TimerReset() {
  startTime = timer.GetFPGATimestamp();
}