#include "Arm.h"

Arm::Arm(XboxController *x, DifferentialDrive *d, Solenoid *s, WPI_TalonSRX *w, WPI_TalonSRX *e)
: //Initializer list
armController(x),       //armController = x; 
armDrive(d),            //armDrive = d; etc...
armGrabberPiston(s),
armJoint(w),
armExtension(e)
{
  //Contructor Body (required)
};

void Arm::MoveToPosition(int pos) {
    switch(pos) {
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
    isMoving = true;
    while(isMoving) {
        isMoving = false;
    }
    /** TODO: Figure out method to stop motor when hitting something or
     * some intentional condition.
     * HAL- something maybe?
     * Limit Switches?
     * Try not to stop by resistance, bad for motor
     */
    return;
}

void Arm::CheckControllerState() {
    if(armController->GetRightBumperPressed()) {
        // "->" dereferences object to access member | same as (*object).member | arm_controller is a double pointer so
        // we need to manually dereference it then dereference it again with -> to access the member (because ->-> doesn't exist), Wow. 
        // (*(*object)).member(); should also work.
        MoveToPosition(1);
    }
    else if (armController->GetLeftBumperPressed()) {
        MoveToPosition(2);
    }
    else { //Delete this after testing. We do not want arm to reset on its own.
        armJoint->Set(0.0);
    }
    HandleGrabber();

    if (armController->GetRightTriggerAxis() > 0) {
        ArmExtend();
    }
    else if (armController->GetLeftTriggerAxis() > 0) {
        ArmRetract();
    }
}
//Arm positions
//This & ArmSecondPosition are for testing.
//TODO: Test that motor rotates forward and back with right/left bumper presses.
void Arm::ArmFirstPosition() {
    armJoint->Set(1.0); //Move forwards
}

void Arm::ArmSecondPosition() {
    armJoint->Set(-1.0); //Move backwards
}

void Arm::ArmThirdPosition() {}

//Grabber Functions
void Arm::HandleGrabber() {
    if(armController->GetAButtonPressed()) {
        armGrabberPiston->Toggle();
    }
}

void Arm::ArmExtend() {
    armExtension->Set(1.0);
}

void Arm::ArmRetract() {
    armExtension->Set(-1.0);
}