#pragma once
#include "Constants.h"
#include "ctre/Phoenix.h"
#include <frc/Timer.h>
#include <frc/XboxController.h>
#include <frc/DifferentialDrive.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/motorcontrol/MotorControllerGroup.h>
//#include <frc/SpeedControllerGroup.h>
using namespace frc;

class Drive {
 public:
    Drive(); //Constructor
    void TuxDrive(); //Actual driving
    void Autonomous();
    void TimerReset();
    void ToggleBrakes();
    void Balance();
 private:
    //Left Motors
    WPI_TalonSRX m_frontLeft{FRONT_LEFT_MOTOR};
    WPI_TalonSRX m_rearLeft{BACK_LEFT_MOTOR};
    MotorControllerGroup m_left{m_frontLeft, m_rearLeft};

    //Right Motors
    WPI_TalonSRX m_frontRight{FRONT_RIGHT_MOTOR};
    WPI_TalonSRX m_rearRight{BACK_RIGHT_MOTOR};
    MotorControllerGroup m_right{m_frontRight, m_rearRight};

    //Create a differential drive using the two previously defined groups.
    DifferentialDrive m_drivetrain{m_left, m_right};

    Timer m_timer;
};