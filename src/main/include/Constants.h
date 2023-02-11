#pragma once

namespace Constants {

int const COMPRESSOR = 0;

//Enums so we don't have to restructure this later
enum Controller {
    DRIVE_XBOX_CONTROLLER = 0,
    ARM_XBOX_CONTROLLER
};

enum MotorControllers {
    ARM_EXTENSION = 7,
    ARM_JOINT = 45,
    BACK_RIGHT = 1,
    FRONT_RIGHT,
    BACK_LEFT = 13,
    FRONT_LEFT,
};

enum Encoders {
    JOINT_ENCODER_ACHANNEL,
    JOINT_ENCODER_BCHANNEL,
    EXTEND_ENCODER_ACHANNEL,
    EXTEND_ENCODER_BCHANNEL
};

enum Solenoids {
    ARM_SOLENOID = 0
};
} //namespace Constants