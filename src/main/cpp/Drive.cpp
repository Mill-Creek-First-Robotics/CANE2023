#include "Drive.h"
#include <iostream>

Drive::Drive(shared_ptr<XboxController>& controller) : m_controller(controller) {
  m_timer.Start();
  m_left.SetInverted(true);
}

void Drive::TuxDrive() {
  if (m_controller->GetLeftStickButtonPressed()) {
    mode == DriveMode::NORMAL ? mode = DriveMode::SLOW : mode = DriveMode::NORMAL;
  }
  double leftY = m_controller->GetLeftY();
  double rightX = m_controller->GetRightX();
  if (mode == DriveMode::NORMAL) {
    leftY /= 1.3;
    rightX /= 1.3;
  } 
  if (mode == DriveMode::SLOW) {
    leftY /= 1.6;
    rightX /= 1.6;
  }
  m_drive.ArcadeDrive(leftY,rightX);
}

void Drive::SimpleAuto() {
  if (m_timer.Get() < 2_s) {
    m_drive.ArcadeDrive(0.5,0.0);
  } else {
    m_drive.ArcadeDrive(0.0,0.0);
  }
}

void Drive::BalanceAuto() {
  //needs to be back 1 Orren's foot from the charging station
  if (m_timer.Get() < 2_s) { 
    m_drive.ArcadeDrive(0.57, 0.0);
  } else {
    m_drive.ArcadeDrive(0.0,0.0);
  }
}

/**
 * Move forward at half speed for 3 seconds, past the charging station
 * move backwards for 2 seconds, onto the charging station
 * stop moving.
 */
void Drive::BalancePastLineAuto() {
  if (m_timer.Get() < 3_s) {
    m_drive.ArcadeDrive(0.57,0.0);
  }

  if (m_timer.Get() > 4_s && m_timer.Get() < 6_s) {
    m_drive.ArcadeDrive(-0.5,0.0);
  } 
  else if (m_timer.Get() >= 6_s) {
    m_drive.ArcadeDrive(0.0,0.0);
  }
}

void Drive::TimerReset() {
  m_timer.Reset();
}