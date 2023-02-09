# ROBOT CODE DOCUMENTATION
A *hopefully* useful and detailed walkthrough of team 6910's code for the 2023 Charged Up competition.
# TABLE OF CONTENTS
* NAMING/STYLE
* Constants
* ROBOT PT1: The Drivetrain
* DRIVE
* ROBOT PT2: The Arm
* ARM

# NAMING/STYLE

# CONSTANTS

# ROBOT PT1: THE DRIVETRAIN

In the Robot definition, you'll notice that we inherit from the TimedRobot class.
This provides our method/function templates such as RobotInit() and RobotPeriodic().
The public keyword before TimedRobot means that current members of the TimedRobot class should be inherited as public members of the Robot derived class.
When public members of TimedRobot are inherited with public, they stay public. Private stay private (are inaccesible from Robot class), and Protected remain protected.
```cpp
class Robot : public TimedRobot {
  //...
};
```
In java, this would read as "class Robot extends TimedRobot", here the colon notates
the inheritance from TimedRobot.
This will be the only time that inheritance is seen in the program.

## Private variables

### Default Template Variables

The *DEFAULT VARIABLES* are variables included in the template project.
```cpp
private:
SendableChooser<string> m_chooser;
string const kAutoNameDefault = "Default";
string const kAutoNameCustom = "My Auto";
string m_autoSelected;
```

### Drivetrain Definitions

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
//enums work similarly to constants and structs, for more info see the Constants section
```
We define the two left and two right motor controllers, then group them, making sure to dereference the pointer variables m_frontLeft and m_backLeft by using the "\*" syntax.
```cpp
//Grouping the left motor controllers defined above
MotorControllerGroup *m_left = new MotorControllerGroup(*m_frontLeft, *m_backLeft);
```
These groups are defined by passing through the two controllers to group.
On line 54 (currently), the drivetrain is defined, taking in the two motor controller
groups.
```cpp
DifferentialDrive *m_drivetrain = new DifferentialDrive(*m_left, *m_right);
```
Next, the XboxController is defined:
```cpp
XboxController *m_controller = new XboxController(Controller::DRIVE_XBOX_CONTROLLER);
//Controller::DRIVE_XBOX_CONTROLLER is another enum member. Accessed using the scope operator "::"
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

### Drive Class Instance

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

# DRIVE

The class Drive exists to simplify code, organize the project structure, and keep code out of Robot.cpp.
Here is all the code for the Drive class declaration:
```cpp
//file Drive.h
class Drive {
 public:
  Drive(DifferentialDrive *d, XboxController *x); //Constructor
  void TuxDrive(); //Actual driving
  void Autonomous();
  void TimerReset();
 private:
  DifferentialDrive *drive;
  XboxController *controller;
};
```
The Drive constructor takes in two arguments, the types being DifferentialDrive and XboxController.
Private members of type pointer are declared to store these arguments.
In the Drive.cpp file, the definition or the bodies of each function are defined:
```cpp
#include "Drive.h"

Drive::Drive(DifferentialDrive *d, XboxController *x)
:
drive(d),
controller(x) 
{
  //Empty Constructor Body
}

void Drive::TuxDrive() {
  drive->ArcadeDrive(controller->GetLeftY(),-controller->GetRightX() * 0.6);
}

void Drive::Autonomous() {

}

void Drive::TimerReset() {

}
```
The scope operator "::" along with the class name and class member function are used to implement the functions defined in Drive.h. Of course, a type is still needed, which goes before the function name like normal. Type ClassName::ClassMember() {}
The only exception to this is the constructor, which has no type, and is always just the class name.
The constructor gets called when an instance of the object is created. An instance of the drive class is created in the Robot.h file as mentioned above.
Lets focus in more on the unique syntax of the Drive constructor:
```cpp
Drive::Drive(DifferentialDrive *d, XboxController *x)
:
drive(d),
controller(x) 
{
  //Empty Constructor Body
}
```
This is called an initializer list. It sets the private drive and controller variables equal to the parameters of the same type. Syntax is:
```cpp
class ClassName {
  public:
    ClassName(type param1, type param2);
  private:
    type member1;
    type member2;
};
//Here is an initializer list, defined outside of the class
ClassName::ClassName(type param1, type param2) : member1(param1), member2(param2) {/* Constructor Body */}
```
And it looks like this when rewritten using the normal constructor syntax:
```cpp
class ClassName {
  public:
    ClassName(type param1, type param2);
  private:
    type member1;
    type member2;
};
//Here is a normal constructor, defined outside of the class
ClassName::ClassName(type param1, type param2) {
  member1 = param1;
  member2 = param2;
}
```
Note: Initializer Lists CAN ONLY be defined off of the constructor of the class.

# ROBOT PT2: THE ARM

# ARM
