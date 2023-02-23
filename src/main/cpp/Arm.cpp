#include "Arm.h"

#include <iostream>

Arm::Arm(shared_ptr<XboxController>& controller) : armController(controller) {
  //All encoders assume initial position is 0.
  //Therefore, arm must be all the way down and fully retracted at start.
  armJointEncoder->Reset();
  armGrabberEncoder->Reset();
  armExtensionEncoder->Reset();
  armGrabberEncoder->SetDistancePerRotation(4.0);
  
  SetJointAndGrabberLimits(JointPositions::POS1); //Default joint & grabber limits
  SetExtensionLimits(ExtensionPositions::EXT_L);  //Default extension limits
  DebugTimer.Start();
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
  armGrabberEncoderDistance = armGrabberEncoder->GetAbsolutePosition();
  armJointEncoderDistance = armJointEncoder->GetDistance();
  armExtensionEncoderDistance = armExtensionEncoder->GetDistance();
 /* --=[ END ]=-- */

 /* --=[ FUNCTION CALLS ]=-- */
  if ( MODE == Mode::NORMAL ) {
    HandleJointInput();
    HandleGrabberPneumatics();
    MoveGrabber();
    //Will not work because currently the arm extension does not have an encoder...
    //HandleExtensionInput();
  }
  else if ( MODE == Mode::DEBUG ) {
    DebugArmExtension();
    DebugArmJoint();
    HandleGrabberPneumatics();
  }
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
    *armExtension,
    armExtensionEncoderDistance,
    Speeds::EXTEND_SPEED,
    Speeds::RETRACT_SPEED,
    UPPER_EXTENSION_LIMIT,
    LOWER_EXTENSION_LIMIT
  );
}

void Arm::HandleGrabberPneumatics() {
  if ( armController->GetAButtonPressed() ) {
    armGrabberPiston->Toggle();
  }
}

void Arm::MoveGrabber() {
  MoveWithinLimits (
    *armGrabberJoint,
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
    *armJoint, 
    armJointEncoderDistance,
    Speeds::JOINT_UPWARDS_SPEED,
    Speeds::JOINT_DOWNWARDS_SPEED,
    UPPER_JOINT_LIMIT,
    LOWER_JOINT_LIMIT 
  );
}

//recieve motor by reference, was passed by value
void Arm::MoveWithinLimits( WPI_TalonSRX &motor, int distance,
  double speedf, double speedb,
  int limitUpper, int limitLower )
{
  if ( limitLower < distance && distance < limitUpper ) {
    motor.Set(0.0);
  }
  else if ( limitLower > distance ) {
    motor.Set(speedf);
  }
  else if ( limitUpper < distance ) {
    motor.Set(speedb);
  }
}

/* --=========[ DEBUG FUNCTIONS ]========-- */
/**
 * To watch variables do:
 * Ctrl + P
 * type "view watch"
 * hit enter
 * under watch dropdown, hit the + and type in variable name
*/
void Arm::DebugArmJoint() {
  //Watchers didn't work last time, added timer back in.
  if ( DebugTimer.HasElapsed(1_s) ) {
    SmartDashboard::PutNumber("Joint: ",armJointEncoderDistance);
    SmartDashboard::PutNumber("Grabber: ",armGrabberEncoderDistance);
    SmartDashboard::PutNumber("Extension: ",armExtensionEncoderDistance);
    std::cout << armGrabberEncoder->GetAbsolutePosition() << std::endl;
    DebugTimer.Reset();
    DebugTimer.Start();
  }
 /* --=[ ARM JOINT ]=-- */
  armGrabberJoint->Set(armController->GetLeftY());
  // === LOOP CONDITIONS ===
  if (armController->GetRightBumperPressed()) armMovingUp = true;
  if (armController->GetRightBumperReleased()) armMovingUp = false;

  if (armController->GetLeftBumperPressed()) armMovingDown = true;
  if (armController->GetLeftBumperReleased()) armMovingDown = false;
  //=== END LOOP CONDITIONS ===
  //===== IF "LOOPS" =====
  //make sure that if both buttons are pressed, arm doesn't try to move both ways
  if (armMovingUp && !armMovingDown) {
    armJoint->Set(-0.5);
  }
  else if (!armMovingDown) { //arm isn't currently trying to move back
    armJoint->Set(0.0);
  }

  if (armMovingDown && !armMovingUp) {
    armJoint->Set(0.5);
  }
  else if (!armMovingUp) {
    armJoint->Set(0.0);
  }
  //===== END IF "LOOPS" =====
 /* --=[ END ]=-- */
  if ( Brendan ) {
    do {
      std::cout << "Brendan Moment" << std::endl;
    } while(true);
  }
  if ( noseIsBleeding ) {
    do {
      std::cout << "Nose Is Bleeding" << std::endl;
    } while(true);
  }
}

void Arm::DebugArmExtension() {
  if (armController->GetXButtonPressed()) armIsExtending = true;
  if (armController->GetXButtonReleased()) armIsExtending = false;

  if (armController->GetYButtonPressed()) armIsRetracting = true;
  if (armController->GetYButtonReleased()) armIsRetracting = false;

  DebugArmExtend();
  DebugArmRetract();
}

void Arm::DebugArmExtend() {
  if(armIsExtending && !armIsRetracting) {
    armExtension->Set(-0.5);
  }
  else if (!armIsRetracting) {
    armExtension->Set(0.0);
  }
}

void Arm::DebugArmRetract() {
  if(armIsRetracting && !armIsExtending) {
    armExtension->Set(0.1);
  }
  else if (!armIsExtending) {
    armExtension->Set(0.0);
  }
}