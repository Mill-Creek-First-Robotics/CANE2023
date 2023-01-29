#include "Arm.h"

Arm::Arm() { //Constructor
    pcmCompressor.Disable();
    pcmCompressor.EnableDigital();
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
    /** TODO: Figure out method to stop motor when hitting something or
     * some intentional condition.
     * HAL- something maybe?
     * Limit Switches?
     * Try not to stop by resistance, bad for motor
     */
    return;
}

void Arm::CheckControllerState() {
    if(m_controller->GetRightBumperPressed()) {
        MoveToPosition(1);
    }
    else if (m_controller->GetLeftBumperPressed()) {
        MoveToPosition(2);
    }
    else { //Delete this after testing. We do not want arm to reset on its own.
        armController.Set(0.0);
    }
    HandleGrabber();
}
//Arm positions
//This & ArmSecondPosition are for testing.
//TODO: Test that motor rotates forward and back with right/left bumper presses.
void Arm::ArmFirstPosition() {
    armController.Set(1.0); //Move forwards
}

void Arm::ArmSecondPosition() {
    armController.Set(-1.0); //Move backwards
}

void Arm::ArmThirdPosition() {}

//Grabber Functions
void Arm::HandleGrabber() {
    if(m_controller->GetAButtonPressed()) {
        grabberPiston.Toggle();
    }
}