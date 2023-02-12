#include "Arm.h"

#include <iostream>

Arm::Arm(XboxController *x, DifferentialDrive *d, Solenoid *s, WPI_TalonSRX *w,
         WPI_TalonSRX *e, Encoder *r, Encoder *o)
:                   //Initializer list
armController(x),   //armController = x;
armDrive(d),        //armDrive = d; etc...
armGrabberPiston(s),
armJoint(w),
armExtension(e),
armJointEncoder(r),
armExtensionEncoder(o),
//END OF PARAMS USAGE
//MANUALLY ENTER FOLLOWING VALUES
BPresses(0),
armExtend(false),
armRetract(false),
armMovingUp(false),
armMovingDown(false),
armIsExtending(false),
armIsRetracting(false)
{ //Contructor Body
  //Both encoders assume initial position is 0.
  //Therefore, arm must be all the way down and fully retracted at start.
  armJointEncoder->Reset();
  armExtensionEncoder->Reset();

  SetJointLimits(Limits::Positions::POS1); //Default joint limits
}

void Arm::SetJointLimits(Limits::Positions pos) {
  switch(pos) {
  case Limits::Positions::POS1:
    UPPER_JOINT_LIMIT = Limits::POS1::ONE_UPPER;
    LOWER_JOINT_LIMIT = Limits::POS1::ONE_LOWER;
    break;
  case Limits::Positions::POS2:
    UPPER_JOINT_LIMIT = Limits::POS2::TWO_UPPER;
    LOWER_JOINT_LIMIT = Limits::POS2::TWO_LOWER;
    break;
  case Limits::Positions::POS3:
    UPPER_JOINT_LIMIT = Limits::POS3::THREE_UPPER;
    LOWER_JOINT_LIMIT = Limits::POS3::THREE_LOWER;
  }
  //CURRENT_JOINT_LIMITS = pos;
}

void Arm::ArmUpdate() {
 /* --=[ UPDATE VARIABLES]=-- */
  armJointEncoderDistance = armJointEncoder->GetDistance();
  armExtensionEncoderDistance = armExtensionEncoder->GetDistance();
 /* --=[ END ]=-- */
 
 /* --=[ FUNCTION CALLS ]=-- */
  if ( MODE == Mode::NORMAL ) {
    HandleJointInput();
    HandleGrabber();
    //Will not work because currently the arm extension does not have an encoder...
    HandleExtensionInput();
  }
  else if ( MODE == Mode::DEBUG ) {
    DebugArmJoint();
    DebugArmExtension();
  }
 /* --=[ END ]=-- */
}

void Arm::HandleExtensionInput() {
  // || armExtend is another way to loop this without using "while"
  // function is called repeatedly until it internally sets armExtend to false
  if ( armController->GetRightBumperPressed() || armExtend ) {
    armExtend = true;
    ArmExtend();
  }
  else if ( armController->GetLeftBumperPressed() || armRetract ) {
    armRetract = true;
    ArmRetract();
  }
  else if ( !armExtend && !armRetract ) armExtension->Set(0.0);
}

void Arm::ArmExtend() {
  if ( armExtensionEncoderDistance > UPPER_EXTENSION_RANGE_LOW 
    && armExtensionEncoderDistance < UPPER_EXTENSION_RANGE_HIGH )
  {
    //Function is no longer called, escape repeated function call
    armExtend = false;
  }
  else if ( armExtensionEncoderDistance < UPPER_EXTENSION_RANGE_LOW ) {
    armExtension->Set(EXTEND_SPEED);
  }
  else if ( armExtensionEncoderDistance > UPPER_EXTENSION_RANGE_HIGH ) {
    armExtension->Set(RETRACT_SPEED);
  }
}

void Arm::ArmRetract() {
  if ( armExtensionEncoderDistance > LOWER_EXTENSION_RANGE_LOW
    && armExtensionEncoderDistance < LOWER_EXTENSION_RANGE_HIGH )
  {
    armExtend = false;
  }
  else if ( armExtensionEncoderDistance < LOWER_EXTENSION_RANGE_LOW ) {
    armExtension->Set(EXTEND_SPEED);
  }
  else if ( armExtensionEncoderDistance > LOWER_EXTENSION_RANGE_HIGH ) {
    armExtension->Set(RETRACT_SPEED);
  }
}

void Arm::HandleGrabber() {
  if ( armController->GetAButtonPressed() ) {
    armGrabberPiston->Toggle();
  }
}

void Arm::HandleJointInput() {
  if ( armController->GetBButtonPressed() ) {
    BPresses++;
  }
  if ( armController->GetBButtonReleased() ) {
    //Start timer for multiple button presses when the first button is released.
    BButtonTimer.Start(); //does nothing when called again & the timer is already running.
  }
  //runs once a second has passed since the timer was started
  if ( BButtonTimer.HasElapsed(BBUTTON_CHECK_INTERVAL) ) {
    switch(BPresses) { //Match # of button presses, setting joint limits respectively.
    case 1:
      SetJointLimits(Limits::Positions::POS1);
      break;
    case 2:
      SetJointLimits(Limits::Positions::POS2);
      break;
    case 3:
      SetJointLimits(Limits::Positions::POS3);
    }
    BPresses = 0;
    BButtonTimer.Reset(); //set time = 0
    BButtonTimer.Stop();  //stop timer
  }

  MoveArmJoint();
}

void Arm::MoveArmJoint() {
  //is in range, don't move
  if ( armJointEncoderDistance < UPPER_JOINT_LIMIT
    && armJointEncoderDistance > LOWER_JOINT_LIMIT )
  {
    armJoint->Set(0.0);
  }
  else if ( armJointEncoderDistance > UPPER_JOINT_LIMIT ) {
    armJoint->Set(JOINT_DOWNWARDS_SPEED);
  }
  else if ( armJointEncoderDistance < LOWER_JOINT_LIMIT ) {
    armJoint->Set(JOINT_UPWARDS_SPEED); 
  }
}

/* --=========[ DEBUG FUNCTIONS ]========-- */
void Arm::DebugArmJoint() {
 /* --=[ DEBUGGING WATCHERS ]=-- */
  std::cout << "JOINT ENCODER DISTANCE: " << armJointEncoderDistance << std::endl;
  std::cout << "EXTENSION ENCODER DISTANCE: " << armExtensionEncoderDistance
            << std::endl << std::endl;
 /* --=[ END ]=-- */
 /* --=[ ARM JOINT ]=-- */
  // === LOOP CONDITIONS ===
  if (armController->GetRightBumperPressed()) armMovingUp = true;
  if (armController->GetRightBumperReleased()) armMovingUp = false;

  if (armController->GetLeftBumperPressed()) armMovingDown = true;
  if (armController->GetLeftBumperReleased()) armMovingDown = false;
  //=== END LOOP CONDITIONS ===
  //===== IF "LOOPS" =====
  //make sure that if both buttons are pressed, arm doesn't try to move both ways
  if (armMovingUp && !armMovingDown) {
    armJoint->Set(0.5);
  }
  else if (!armMovingDown) { //arm isn't currently trying to move back
    armJoint->Set(0.0);
  }

  if (armMovingDown && !armMovingUp) {
    //used to be negative, I've since reversed encoder direction in Robot.h
    //so we work with + instead
    // if (armJointEncoder->GetDistance() > 800) {
    //   armJoint->Set(-0.5); //move down
    // }
    // else if (armJointEncoder->GetDistance() < 600){
    //   armJoint->Set(0.5); //move up
    // }
    armJoint->Set(-0.2);
  }
  else if (!armMovingUp) {
    armJoint->Set(0.0);
  }
  //===== END IF "LOOPS" =====
 /* --=[ END ]=-- */
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

/* --=[ SPOT TO RECORD LIMITS ]=-- */
/* === JOINT === */
// 1st UPPER:
// 1st LOWER:

// 2nd UPPER:
// 2nd LOWER:

// 3rd UPPER:
// 3rd LOWER:
/* === EXTENSION === */
// EXTEND LOW:
// EXTEND UP:

// RETRACT LOW:
// RETRACT UP: