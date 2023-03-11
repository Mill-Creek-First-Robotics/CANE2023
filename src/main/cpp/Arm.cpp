#include "Arm.h"

#include <iostream>

Arm::Arm(shared_ptr<XboxController>& controller) : armController(controller) {
  //All encoders assume initial position is 0.
  //Therefore, arm must be all the way down and fully retracted at start.
  armJointEncoder.Reset();
  armGrabberEncoder.Reset();
  armExtensionEncoder.Reset();
  armGrabberEncoder.SetDistancePerRotation(4.0);
  
  SetJointAndGrabberLimits(JointPositions::POS1); //Default joint & grabber limits
  SetExtensionLimits(ExtensionPositions::EXT_L);  //Default extension limits
  compressor.Disable();
  compressor.EnableDigital();
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
void Arm::SetExtensionLimits(ExtensionPositions pos) {
  switch(pos) {
  case ExtensionPositions::EXT_U:
    UPPER_EXTENSION_LIMIT = ExtensionLimits::EXT_U_UPPER;
    LOWER_EXTENSION_LIMIT = ExtensionLimits::EXT_U_LOWER;
    break;
  case ExtensionPositions::EXT_L:
    UPPER_EXTENSION_LIMIT = ExtensionLimits::EXT_L_UPPER;
    LOWER_EXTENSION_LIMIT = ExtensionLimits::EXT_L_LOWER;
  }
}

void Arm::ArmUpdate() {
 /* --=[ UPDATE VARIABLES]=-- */
  armGrabberEncoderDistance = armGrabberEncoder.GetDistance();
  armJointEncoderDistance = armJointEncoder.GetDistance();
  armExtensionEncoderDistance = armExtensionEncoder.GetDistance();
 /* --=[ END ]=-- */
  if ( armController->GetLeftStickButtonPressed() ) {
    if ( MODE == Mode::DEBUG ) MODE = Mode::NORMAL;
    else MODE = Mode::DEBUG;
  }
 /* --=[ FUNCTION CALLS ]=-- */
  if ( MODE == Mode::NORMAL ) {
    HandleJointInput();
    MoveGrabber();
    HandleExtensionInput();
  }
  else if ( MODE == Mode::DEBUG ) {
    DebugArm();
  }
  HandleGrabberPneumatics();
 /* --=[ END ]=-- */
}

void Arm::HandleExtensionInput() {
  if ( armController->GetXButtonPressed() ) {
    armExtensionToggle = !armExtensionToggle;
    armExtensionToggle ? SetExtensionLimits(ExtensionPositions::EXT_U)  //T
    : SetExtensionLimits(ExtensionPositions::EXT_L);                    //F
  }
  MoveArmExtension();
}
void Arm::MoveArmExtension() {
  MoveWithinLimits ( //deref, pass by value. @see: MoveWithinLimits()
    &armExtension,
    armExtensionEncoderDistance,
    Speeds::EXTEND_SPEED,
    Speeds::RETRACT_SPEED,
    UPPER_EXTENSION_LIMIT,
    LOWER_EXTENSION_LIMIT
  );
}

void Arm::HandleGrabberPneumatics() {
  if ( armController->GetAButtonPressed() ) {
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
  if ( armController->GetBButtonPressed() ) {
    BPresses++;
  }
  if ( armController->GetBButtonReleased() ) {
    //Start timer for multiple button presses when the first button is released.
    //needs if statement so that a button held from previous interval
    //doesn't start next interval w/out increasing b
    if (BPresses > 0) BButtonTimer.Start(); //does nothing when called again & the timer is already running.
  }
  //runs once a second has passed since the timer was started
  if ( BButtonTimer.HasElapsed(Speeds::BBUTTON_CHECK_INTERVAL) ) {
    switch(BPresses) { //Match # of button presses, setting joint limits respectively.
    case 1:
      SetJointAndGrabberLimits(JointPositions::POS1);
      break;
    case 2:
      SetJointAndGrabberLimits(JointPositions::POS2);
      break;
    case 3:
      SetJointAndGrabberLimits(JointPositions::POS3);
    }
    BPresses = 0;
    BButtonTimer.Reset(); //set time = 0
    BButtonTimer.Stop();  //stop timer
  }

  MoveArmJoint();
}

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
/**
 * To watch variables do:
 * Ctrl + P
 * type "view watch"
 * hit enter
 * under watch dropdown, hit the + and type in variable name
*/
void Arm::DebugArm() {
  //Print values to SmartDashboard
  SmartDashboard::PutNumber("Joint: ",armJointEncoderDistance);
  SmartDashboard::PutNumber("Grabber: ",armGrabberEncoderDistance);
  SmartDashboard::PutNumber("Extension: ",armExtensionEncoderDistance);

  //Call DebugFunctions
  DebugArmJoint();
  DebugArmExtension();
  DebugArmGrabber();

  //Reset Encoders
  if ( armController->GetRightStickButtonPressed() ) {
    armJointEncoder.Reset();
    armGrabberEncoder.Reset();
    armExtensionEncoder.Reset();
  }
}

void Arm::DebugArmJoint() {
  if (armController->GetRightBumperPressed()) armMovingUp = true;
  if (armController->GetRightBumperReleased()) armMovingUp = false;

  if (armController->GetLeftBumperPressed()) armMovingDown = true;
  if (armController->GetLeftBumperReleased()) armMovingDown = false;

  //make sure that if both buttons are pressed, arm doesn't try to move both ways
  if (armMovingUp && !armMovingDown) {
    armJoint.Set(Speeds::JOINT_UPWARDS_SPEED);
  }
  else if (!armMovingDown) { //arm isn't currently trying to move back
    armJoint.Set(0.0);
  }

  if (armMovingDown && !armMovingUp) {
    armJoint.Set(Speeds::JOINT_DOWNWARDS_SPEED);
  }
  else if (!armMovingUp) {
    armJoint.Set(0.0);
  }
}

void Arm::DebugArmExtension() {
  if (armController->GetXButtonPressed()) armIsExtending = true;
  if (armController->GetXButtonReleased()) armIsExtending = false;

  if (armController->GetYButtonPressed()) armIsRetracting = true;
  if (armController->GetYButtonReleased()) armIsRetracting = false;

  if(armIsRetracting && !armIsExtending) {
    armExtension.Set(Speeds::RETRACT_SPEED);
  }
  else if (!armIsExtending) {
    armExtension.Set(0.0);
  }

  if(armIsExtending && !armIsRetracting) {
    armExtension.Set(Speeds::EXTEND_SPEED);
  }
  else if (!armIsRetracting) {
    armExtension.Set(0.0);
  }
}

void Arm::DebugArmGrabber() {
  if ( armController->GetLeftTriggerAxis() > 0.0 ) {
    armGrabberJoint.Set(Speeds::GRABBER_UPWARDS_SPEED);
  }
  else if ( armController->GetRightTriggerAxis() > 0.0 ) {
    armGrabberJoint.Set(Speeds::GRABBER_DOWNWARDS_SPEED);
  }
  else {
    armGrabberJoint.Set(0.0);
  } 
}