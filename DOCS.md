# TABLE OF CONTENTS
* NAMING/STYLE
* ROBOT
* DRIVE
* ARM

## NAMING/STYLE

## ROBOT

* In the Robot definition, you'll notice that we inherit from the TimedRobot class.
  This provides our method/function templates such as RobotInit() and RobotPeriodic().
```cpp
class Robot : public TimedRobot {
  //...
};
```
In java, this would read as "class Robot extends TimedRobot", here the colon notates
the inheritance from TimedRobot.
This will be the only time that inheritance is seen in the program.

### Private variables

#### Default Template Variables

The *DEFAULT VARIABLES* are variables included in the template project.
```cpp
private:
SendableChooser<string> m_chooser;
string const kAutoNameDefault = "Default";
string const kAutoNameCustom = "My Auto";
string m_autoSelected;
```

#### Drivetrain Definitions

Underneath those, the motor controllers for the drivetrain are defined:
* We have what's called a differential drive
* Our drivetrain has 4 motors, two on the left, two on the right.
  Each one has a motor controller attached
* We handle motor movement by defining these motor controllers:
```cpp
//Left Motors
WPI_TalonSRX *m_frontLeft = new WPI_TalonSRX(MotorControllerSRX::FRONT_LEFT_MOTOR);
WPI_TalonSRX *m_backLeft = new WPI_TalonSRX(MotorControllerSRX::BACK_LEFT_MOTOR);
//MotorControllerSRX is an enum defined in constants.h
//enums work similarly to constants and structs, for more info see:
//
```
We define the two left and two right motor controllers, then group them:
```cpp
//Grouping the left motor controllers defined above
MotorControllerGroup *m_left = new MotorControllerGroup(*m_frontLeft, *m_backLeft);
```
* These groups are defined by passing through the two controllers to group.
* On line 54 (currently), the drivetrain is defined, taking in the two motor controller
  groups.
```cpp
DifferentialDrive *m_drivetrain = new DifferentialDrive(*m_left, *m_right);
```
Next, the XboxController is defined:
```cpp
XboxController *m_controller = new XboxController(Controller::DRIVE_XBOX_CONTROLLER);
//Controller::DRIVE_XBOX_CONTROLLER is another enum member. Accessed using the 
//scope operator "::"
```
Here are the current Button Bindings:
* A = Toggle grabber (pneumatic piston)
* X = Move arm upwards at the joint
* Y = Move arm downwards at the joint
* B = Move the vector motor (currently not in use, was just for testing, remains because of possible future testing)
* LB = Extend the arm, needs to be held
* RB = Retract the arm, also needs to be help
* Left Joystick Y-Axis = Move robot forwards/backwards
* Right Joystick X-Axis = Rotate robot left/right

#### Drive Class Instance

Finally, we passthrough the drivetrain and the controller to the drive class, as defined in its constructor. More on that in the next section.
```cpp
Drive *m_drive = new Drive
  (
    this->m_drivetrain,
    this->m_controller
  );
```
Note: The "this->" can be omitted, I personally like to use it to mark member variables.
This is so that it is clear when member variables are used.

## DRIVE