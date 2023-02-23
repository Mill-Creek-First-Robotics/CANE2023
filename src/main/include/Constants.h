#pragma once

#include <units/time.h>

namespace Constants {

int const COMPRESSOR = 0;

//Enums so we don't have to restructure this later
/**
 * @desc: Controller index as defined in driverstation.
 */
enum Controller {
    DRIVE_XBOX_CONTROLLER = 0,
    ARM_XBOX_CONTROLLER
};

/**
 * @desc: Enter motor controller ports from Phoenix here. 
 */
enum MotorControllers {
    //= Arm
    ARM_GRABBER_JOINT = 7,
    ARM_EXTENSION = 0,
    ARM_JOINT = 45,
    //= Drivetrain
    BACK_RIGHT = 1,
    FRONT_RIGHT,
    BACK_LEFT = 13,
    FRONT_LEFT,
};

/**
 * @desc: Encoder class needs a and b channels as params.
 * @note: GRABBER_ENCODER is an AnalogEncoder which only needs 1 argument, the DIO port. 
 */
enum Encoders {
    JOINT_ENCODER_ACHANNEL = 5,
    JOINT_ENCODER_BCHANNEL,
    EXTEND_ENCODER_ACHANNEL = 9,
    EXTEND_ENCODER_BCHANNEL,
    GRABBER_ENCODER = 0,
};

/**
 * @desc: channel for solenoids.
 */
enum Solenoids {
    ARM_SOLENOID = 0
};

/**
 * @desc: Speed constants for both the arm and drivetrain.
 * Speeds is a namespace because enums can't have double values
 */
namespace Speeds {
 /* === ARM === */
  units::second_t const BBUTTON_CHECK_INTERVAL = 1_s; 
  double const JOINT_UPWARDS_SPEED = -0.3;
  double const JOINT_DOWNWARDS_SPEED = 0.3;
  double const EXTEND_SPEED = 0.2;
  double const RETRACT_SPEED = -0.2;
  double const GRABBER_UPWARDS_SPEED = -0.2;
  double const GRABBER_DOWNWARDS_SPEED = 0.2;
 /* === DRIVETRAIN === */
  double const AUTO_SPEED = -0.5;
} //namespace Speeds

//Limits for the arm positions
namespace Limits {
enum class JointPositions {
  POS1,
  POS2,
  POS3
};
enum JointLimits {
  ONE_UPPER,
  ONE_LOWER,
  TWO_UPPER,
  TWO_LOWER,
  THREE_UPPER,
  THREE_LOWER
};
//Follows JointPositions because the grabber follows the Arm
enum GrabberLimits {
  G_ONE_UPPER,
  G_ONE_LOWER,
  G_TWO_UPPER,
  G_TWO_LOWER,
  G_THREE_UPPER,
  G_THREE_LOWER
};

enum class ExtensionPositions {
  EXT_U, //Upper
  EXT_L  //Lower
};
enum ExtensionLimits {
  EXT_L_LOWER,
  EXT_L_UPPER,
  EXT_U_LOWER,
  EXT_U_UPPER
};
} //namespace Limits
} //namespace Constants