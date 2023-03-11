#include "Arm.h"

#include <iostream>

// Arm::Arm() {
Arm::Arm() {
  //All encoders assume initial position is 0.
  //Therefore, arm must be all the way down and fully retracted at start.
  armJointEncoder.Reset();
  armExtensionEncoder.Reset();
  armGrabberEncoder.Reset();

  // armGrabberEncoder.SetDownSourceEdge(true,true);
  armGrabberEncoder.SetUpSource(Encoders::GRABBER_ENCODER);  
  armGrabberEncoder.SetUpSourceEdge(true,true);  
  armGrabberEncoder.SetUpDownCounterMode();
  //// armGrabberEncoder.SetDistancePerPulse(500./256.);

  SetJointAndGrabberLimits(JointPositions::POS1); //Default joint & grabber limits
  // SetExtensionLimits(ExtensionPositions::EXT_L);  //Default extension limits
  compressor.Disable();
  compressor.EnableDigital();

  //Arm Driver options setup on smartdashboard
  chooser.SetDefaultOption(defaultArm, defaultArm);
  for ( string driver : drivers ) {
    chooser.AddOption(driver, driver);
  }
  SmartDashboard::PutData("Who is controlling the Arm: ", &chooser);
}

void Arm::PutToSmartDashboard() {
  SmartDashboard::PutNumber("Joint: ",armJointEncoderDistance);
  SmartDashboard::PutNumber("Grabber: ",armGrabberEncoderDistance);
  SmartDashboard::PutNumber("GrabberPos: ",armGrabberPosition);
  SmartDashboard::PutNumber("Extension: ",armExtensionEncoderDistance);
  SmartDashboard::PutNumber("Count: ",armGrabberEncoder.Get());
}

void Arm::UpdateSelection() {
  currentDriver = chooser.GetSelected();
  bindings.SetCurrentDriver(currentDriver);
}

void Arm::SetJointAndGrabberLimits(JointPositions pos) {
  switch(pos) {
  case JointPositions::POS1:
    UPPER_JOINT_LIMIT = JointLimits::ONE_UPPER;
    LOWER_JOINT_LIMIT = JointLimits::ONE_LOWER;
    UPPER_GRABBER_LIMIT = GrabberLimits::G_ONE_UPPER;
    LOWER_GRABBER_LIMIT = GrabberLimits::G_ONE_LOWER;
    break;
  case JointPositions::POS2:
    UPPER_JOINT_LIMIT = JointLimits::TWO_UPPER;
    LOWER_JOINT_LIMIT = JointLimits::TWO_LOWER;
    UPPER_GRABBER_LIMIT = GrabberLimits::G_TWO_UPPER;
    LOWER_GRABBER_LIMIT = GrabberLimits::G_TWO_LOWER;
    break;
  case JointPositions::POS3:
    UPPER_JOINT_LIMIT = JointLimits::THREE_UPPER;
    LOWER_JOINT_LIMIT = JointLimits::THREE_LOWER;
    UPPER_GRABBER_LIMIT = GrabberLimits::G_THREE_UPPER;
    LOWER_GRABBER_LIMIT = GrabberLimits::G_THREE_LOWER;
  }
}
// void Arm::SetExtensionLimits(ExtensionPositions pos) {
//   switch(pos) {
//   case ExtensionPositions::EXT_U:
//     UPPER_EXTENSION_LIMIT = ExtensionLimits::EXT_U_UPPER;
//     LOWER_EXTENSION_LIMIT = ExtensionLimits::EXT_U_LOWER;
//     break;
//   case ExtensionPositions::EXT_L:
//     UPPER_EXTENSION_LIMIT = ExtensionLimits::EXT_L_UPPER;
//     LOWER_EXTENSION_LIMIT = ExtensionLimits::EXT_L_LOWER;
//   }
// }

void Arm::ArmUpdate() {
  bindings.UpdateConditions();
  PutToSmartDashboard();
 /* --=[ UPDATE VARIABLES]=-- */
  armGrabberEncoderDistance = armGrabberEncoder.Get();
  //convert to position
  if (armGrabberJoint.GetMotorOutputPercent() > 0.0) {
    armGrabberPosition += armGrabberEncoderDistance;
  }
  else {
    armGrabberPosition -= armGrabberEncoderDistance;
  }
  //reset the count
  armGrabberEncoder.Reset();
  armJointEncoderDistance = -armJointEncoder.GetDistance();
  armExtensionEncoderDistance = armExtensionEncoder.GetDistance();
 /* --=[ END ]=-- */
  // if ( bindings.GetArmModeToggle() ) {
  //   MODE == ArmMode::MANUAL ? MODE = ArmMode::NORMAL : MODE = ArmMode::MANUAL;
  // }
 /* --=[ FUNCTION CALLS ]=-- */
    ManualArmJoint();
    ManualArmGrabber();
    ManualArmExtension();
  HandleGrabberPneumatics();
 /* --=[ END ]=-- */
}

// void Arm::HandleExtensionInput() {
//   if ( bi ) {
//     armExtensionToggle = !armExtensionToggle;
//     armExtensionToggle ? SetExtensionLimits(ExtensionPositions::EXT_U)  //T
//     : SetExtensionLimits(ExtensionPositions::EXT_L);                    //F
//   }
//   MoveArmExtension();
// }
// void Arm::MoveArmExtension() {
//   MoveWithinLimits (
//     &armExtension,
//     armExtensionEncoderDistance,
//     Speeds::EXTEND_SPEED,
//     Speeds::RETRACT_SPEED,
//     UPPER_EXTENSION_LIMIT,
//     LOWER_EXTENSION_LIMIT
//   );
// }

void Arm::HandleGrabberPneumatics() {
  bindings.UpdateConditions();

  if ( bindings.GetGrabberToggle() ) {
    armGrabberPiston.Toggle();
  }
}

void Arm::MoveGrabber() {
  MoveWithinLimits (
    &armGrabberJoint,
    armGrabberEncoderDistance,
    Speeds::GRABBER_UPWARDS_SPEED,
    Speeds::GRABBER_DOWNWARDS_SPEED,
    UPPER_GRABBER_LIMIT,
    LOWER_GRABBER_LIMIT 
  );
}

void Arm::HandleJointInput() {
  if ( bindings.GetObjectPickup() ) {
    SetJointAndGrabberLimits(JointPositions::POS1);
  }
  if ( bindings.GetObjectDropoffMid() ) {
    SetJointAndGrabberLimits(JointPositions::POS2);
  }
  if ( bindings.GetObjectDropoffHigh() ) {
    SetJointAndGrabberLimits(JointPositions::POS3);
  }
  MoveArmJoint();
}
//herese a schhchahnbge
void Arm::MoveArmJoint() {
  MoveWithinLimits (
    &armJoint, 
    armJointEncoderDistance,
    Speeds::JOINT_UPWARDS_SPEED,
    Speeds::JOINT_DOWNWARDS_SPEED,
    UPPER_JOINT_LIMIT,
    LOWER_JOINT_LIMIT 
  );
}

void Arm::MoveWithinLimits( WPI_TalonSRX *motor, int distance,
  double speedf, double speedb,
  int limitUpper, int limitLower )
{
  if ( limitLower + 30 < distance && distance < limitUpper - 30 ) { //offset so arm doesn't vibrate in place
    motor->Set(0.0);
  }
  else if ( limitLower > distance ) {
    motor->Set(speedf);
  }
  else if ( limitUpper < distance ) {
    motor->Set(speedb);
  }
}


void Arm::AutoMoveArmToPosition(JointPositions pos) {
  int low{};
  int high{};
  switch (pos) {
  case JointPositions::POS1:
    low = JointLimits::ONE_LOWER;
    high = JointLimits::ONE_UPPER;
    break;
  case JointPositions::POS2:
    low = JointLimits::TWO_LOWER;
    high = JointLimits::TWO_UPPER;
    break;
  case JointPositions::POS3:
    low = JointLimits::THREE_LOWER;
    high = JointLimits::THREE_UPPER;
  }
  while ( armJointEncoderDistance > high ) {
    armJoint.Set(Speeds::JOINT_DOWNWARDS_SPEED);
  }
  while ( armJointEncoderDistance < low ) {
    armJoint.Set(Speeds::JOINT_UPWARDS_SPEED);
  }
}

void Arm::AutoExtendArm() {
  while ( armExtensionEncoderDistance > ExtensionLimits::EXT_U_UPPER ) {
    armExtension.Set(Speeds::RETRACT_SPEED);
  }
  while ( armExtensionEncoderDistance < ExtensionLimits::EXT_U_LOWER ) {
    armExtension.Set(Speeds::EXTEND_SPEED);
  }
}

void Arm::AutoRetractArm() {
  while ( armExtensionEncoderDistance > ExtensionLimits::EXT_L_UPPER ) {
    armExtension.Set(Speeds::RETRACT_SPEED);
  }
  while ( armExtensionEncoderDistance < ExtensionLimits::EXT_L_LOWER ) {
    armExtension.Set(Speeds::EXTEND_SPEED);
  }
}

/* --=========#[ DEBUG FUNCTIONS ]#========-- */
void Arm::DebugArm() {
  //Call Debug/Manual Functions
  ManualArmJoint();
  ManualArmExtension();
  ManualArmGrabber();

  //Reset Encoders
  if ( bindings.GetArmModeToggle() ) {
    armJointEncoder.Reset();
    armGrabberEncoder.Reset();
    armExtensionEncoder.Reset();
  }
}

//TODO: Make these simpler with functions to avoid repeating
void Arm::ManualArmJoint() {
  NotGravity(
    &armJoint,
    bindings.GetJointUp(),
    bindings.GetJointUpReleased(),
    bindings.GetJointDown(),
    bindings.GetJointDownReleased(),
    &jointMovingUp,
    &jointMovingDown,
    Speeds::JOINT_UPWARDS_SPEED,
    Speeds::JOINT_DOWNWARDS_SPEED
  );
}

void Arm::ManualArmExtension() {
  NotGravity(
    &armExtension,
    bindings.GetArmExtend(),
    bindings.GetArmExtendReleased(),
    bindings.GetArmRetract(),
    bindings.GetArmRetractReleased(),
    &extensionMovingUp,
    &extensionMovingDown,
    Speeds::EXTEND_SPEED,
    Speeds::RETRACT_SPEED
  );
}

void Arm::ManualArmGrabber() {
  NotGravity(
    &armGrabberJoint,
    bindings.GetGrabberUp(),
    bindings.GetGrabberUpReleased(),
    bindings.GetGrabberDown(),
    bindings.GetGrabberDownReleased(),
    &grabberMovingUp,
    &grabberMovingDown,
    Speeds::GRABBER_UPWARDS_SPEED,
    Speeds::GRABBER_DOWNWARDS_SPEED
  );
}

void Arm::NotGravity(WPI_TalonSRX* motor,
  bool upCondition, bool upReleaseCondition,
  bool downCondition, bool downReleaseCondition,
  bool* movingUp, bool* movingDown,
  double upwardsSpeed, double downwardsSpeed ) {

  bindings.UpdateConditions();

  if ( upCondition ) {
    *movingUp = true;
  } else if ( upReleaseCondition ) {
    *movingUp = false;
  }
  if ( downCondition ) {
    *movingDown = true;
  } else if ( downReleaseCondition ) {
    *movingDown = false;
  }

  if ( movingUp && !movingDown ) {
    motor->Set(upwardsSpeed);
  } else if ( !movingDown ) {
    motor->Set(0.0);
  }

  if ( movingDown && !movingUp ) {
    motor->Set(downwardsSpeed);
  } else if ( !movingUp ) {
    motor->Set(0.0);
  }
}