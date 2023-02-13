#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Timer.h>
#include <units/time.h>
#include <frc/XboxController.h>
#include <frc/PneumaticsModuleType.h>
#include <frc/drive/DifferentialDrive.h>
using namespace frc;

class Auto {
    public:
        Auto(DifferentialDrive *d);
        void AutoCenter();
        void TimerReset();
    
    private:
        DifferentialDrive *autoDrive;
        units::second_t startTime;
        Timer timer;
};