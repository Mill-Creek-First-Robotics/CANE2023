#pragma once

int const COMPRESSOR = 0;

//Enums so we don't have to restructure this later
enum Controller {
    DRIVE_XBOX_CONTROLLER = 0,
    ARM_XBOX_CONTROLLER
};

enum MotorControllerSRX {
    TEST_VICTOR_COPY = 0,
    TEST_WPI_COPY = 7,
    ARM_EXTENSION_MOTOR_CONTROLLER = 45,
    ARM_JOINT_MOTOR_CONTROLLER = 7,
    BACK_RIGHT_MOTOR = 1,
    FRONT_RIGHT_MOTOR,
    BACK_LEFT_MOTOR = 13,
    FRONT_LEFT_MOTOR,
};

enum Encoders {
    JOINT_ENCODER_ACHANNEL,
    JOINT_ENCODER_BCHANNEL,
    EXTEND_ENCODER_ACHANNEL,
    EXTEND_ENCODER_BCHANNEL
};

enum ChannelSolenoid {
    ARM_SOLENOID = 0
};