#include "Arm.h"

Arm::Arm(XboxController *x, DifferentialDrive *d, Solenoid *s, WPI_TalonSRX *w, WPI_TalonSRX *e, Encoder *r)
: //Initializer list
armController(x),       //armController = x; 
armDrive(d),            //armDrive = d; etc...
armGrabberPiston(s),
armJoint(w),
armExtension(e),
armEncoder(r)
{
  //Contructor Body
}

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
    armIsMoving = true;
    while(armIsMoving) {
        //move motor to reset position
        //if (armHasReachedTarget) {
        armIsMoving = false;
        //}
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
        // "->" dereferences object to access member | same as (*object).member
        MoveToPosition(1);
    }
    else if (armController->GetLeftBumperPressed()) {
        MoveToPosition(2);
    }
    else { //Delete this after testing. We do not want arm to reset on its own.
        armJoint->Set(0.0);
    }

    /** TODO: Find a way to "get button held down". 
     * Might need a loop or a "get button released"
     * and some booleans to toggle.
     */

    if (armController->GetRightTriggerAxis() > 0) {
        ArmExtend();
    }
    else if (armController->GetLeftTriggerAxis() > 0) {
        ArmRetract();
    }

    HandleGrabber();
}
//Arm positions
//This & ArmSecondPosition are for testing.
void Arm::ArmFirstPosition() {
    //When bumper is released, escape loop, return flow of control to CheckControllerState.
    //Returns true when let go, escaping loop because of the "!"
    //My way of implementing a "Get button held down"
    while(!armController->GetRightBumperReleased()) {
        armJoint->Set(1.0); //Move forwards
    }
}

void Arm::ArmSecondPosition() {
    while(!armController->GetLeftBumperReleased()) {
        armJoint->Set(-1.0); //Move backwards
    }
}

void Arm::ArmThirdPosition() {}

//Grabber Functions
void Arm::HandleGrabber() {
    if(armController->GetAButtonPressed()) {
        armGrabberPiston->Toggle();
    }
}

void Arm::ArmExtend() {
    while(armController->GetRightTriggerAxis() > 0) { //Is held down.
        armExtension->Set(1.0);
    }
}

void Arm::ArmRetract() {
    while(armController->GetLeftTriggerAxis() > 0) {
        armExtension->Set(-1.0);
    }
}