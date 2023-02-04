#pragma once

int const COMPRESSOR = 0;

//Enums so we don't have to restructure this later
enum Controller {
    DRIVE_XBOX_CONTROLLER = 0,
    ARM_XBOX_CONTROLLER
};

enum MotorControllerSRX {
    ARM_MOTOR_CONTROLLER = 0,
    BACK_RIGHT_MOTOR = 1,
    FRONT_RIGHT_MOTOR,
    BACK_LEFT_MOTOR = 13,
    FRONT_LEFT_MOTOR
};

enum ChannelSolenoid {
    ARM_SOLENOID = 0
};