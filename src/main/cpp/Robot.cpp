#include "Robot.h"

void Robot::RobotInit() {
  m_chooser.SetDefaultOption(kAutoNameNormal, kAutoNameNormal);
  m_chooser.AddOption(kAutoNameGyro, kAutoNameGyro);
  SmartDashboard::PutData("Auto Modes", &m_chooser);
}

/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() {}

/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() {m_auto.TimerReset(); }

void Robot::AutonomousPeriodic() {
  if (m_autoSelected == kAutoNameGyro) {
    m_auto.Gyro();
  }
}

void Robot::TeleopInit() {}

void Robot::TeleopPeriodic() {
  m_drive.TuxDrive();
  m_arm.ArmUpdate();
}

void Robot::DisabledInit() {}
void Robot::DisabledPeriodic() {}

void Robot::TestInit() {}
void Robot::TestPeriodic() {}

void Robot::SimulationInit() {}
void Robot::SimulationPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() {
  return StartRobot<Robot>();
}
#endif