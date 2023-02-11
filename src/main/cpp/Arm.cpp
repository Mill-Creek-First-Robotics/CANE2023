#include "Arm.h"

Arm::Arm(XboxController *x, DifferentialDrive *d, Solenoid *s, WPI_TalonSRX *w,
         WPI_TalonSRX *e, WPI_TalonSRX *q, Encoder *r, Encoder *o)
:                   // Initializer list
armController(x),   // armController = x;
armDrive(d),        // armDrive = d; etc...
armGrabberPiston(s),
armJoint(w),
armExtension(e),
armJointHelper(q),
armJointEncoder(r),
armExtensionEncoder(o)
{ // Contructor Body
  armMovingForward = false;
  armMovingBackward = false;
  armIsResetting = false;
  armIsExtending = false;
  armIsRetracting = false;
  armVectorIsMoving = false;
}

void Arm::MoveToPosition(int pos) {
  switch (pos) {
  case 1:
    ResetPosition();
    ArmFirstPosition();
    break;
  case 2:
    ResetPosition();
    ArmSecondPosition();
    break;
  case 3:
    ResetPosition();
    ArmThirdPosition();
  }
}

void Arm::ResetPosition() {
  armIsResetting = true;
  /** TODO: Figure out method to stop motor when hitting something or
   * some intentional condition.
   * HAL- something maybe?
   * Limit Switches?
   * Try not to stop by resistance, bad for motor
   */
  return;
}

void Arm::CheckControllerState() {
 /* --=[ ARM JOINT ]=-- */
  // "->" dereferences object to access member | same as (*object).member
  // === LOOP CONDITIONS ===
  if (armController->GetXButtonPressed()) {
    armMovingForward = true;
  }
  if (armController->GetXButtonReleased()) {
    armMovingForward = false;
  }

  if (armController->GetYButtonPressed()) {
    armMovingBackward = true;
  }
  if (armController->GetYButtonReleased()) {
    armMovingBackward = false;
  }
  // === END LOOP CONDITIONS ===

  // ===== IF "LOOPS" =====
  //make sure that if both buttons are pressed, arm doesn't try to move both ways
  if (armMovingForward && !armMovingBackward) {
    armJoint->Set(1.0);
  }
  else if (!armMovingBackward) {//arm isn't currently trying to move back
    armJoint->Set(0.0);
  }

  if (armMovingBackward && !armMovingForward) {
    armJoint->Set(-1.0);
  }
  else if (!armMovingForward) {
    armJoint->Set(0.0);
  }
  // ===== END IF "LOOPS" =====
 /* --=[ END ]=-- */

 /* --=[ ARM EXTENSION ]=-- */
  if (armController->GetRightBumperPressed()) {
    armIsExtending = true;
  }
  if (armController->GetRightBumperReleased()) {
    armIsExtending = false;
  } 

  if (armController->GetLeftBumperPressed()) {
    armIsRetracting = true;
  }
  if (armController->GetLeftBumperReleased()) {
    armIsRetracting = false;
  }
  ArmExtend();
  ArmRetract();
 /* --=[ END ]=-- */

 /* --=[ VECTOR MOTOR ]=-- */
  if (armController->GetBButtonPressed()) {
    armVectorIsMoving = true;
  }
  if (armController->GetBButtonReleased()) {
    armVectorIsMoving = false;
  }
  MoveVectorMotor(1.0);
 /* --=[ END ]=-- */

  HandleGrabber();
}

// Arm positions
void Arm::ArmFirstPosition() {}

void Arm::ArmSecondPosition() {}

void Arm::ArmThirdPosition() {}

// Grabber Functions
void Arm::HandleGrabber() {
  if (armController->GetAButtonPressed()) {
    armGrabberPiston->Toggle();
  }
}

void Arm::ArmExtend() {
  if(armIsExtending && !armIsRetracting) {
    armExtension->Set(0.1);
  }
  else if (!armIsRetracting) {
    armExtension->Set(0.0);
  }
}

void Arm::ArmRetract() {
  if(armIsRetracting && !armIsExtending) {
    armExtension->Set(-0.5);
  }
  else if (!armIsExtending) {
    armExtension->Set(0.0);
  }
}

void Arm::MoveVectorMotor(double speed) {
  if (armVectorIsMoving) {
    vector->Set(ControlMode::PercentOutput, speed);
  }
  else {
    vector->Set(ControlMode::PercentOutput, 0.0);
  }
}