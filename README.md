# 2019-Robot
Robot code for 2019 FRC Season

## Documentation
Documentation may be automatically generated for this project using the AutoDoc.vi tool.  The most recently published documentation is available on this project's [GitHub Pages site](https://frc1756-argos.github.io/2019-Robot/).

## Notable Features
+ Multiple robot configurations to enable common software on all robot platforms
    + Support for different motor controller addresses and types
    + Support for different tuning values for closed loop control systems
    + Support for different motor controller configurations (e.g. brake mode)
    + Support for disabling motors on configurations with limited hardware installed
+ Auto homing of encoder positions on startup
    + Climbers retract to known locations when robot is first enabled to ensure known locations
    + Arm position initialized using mechanically constrained position and a "homing button"
        + On startup, the homing button daughter board indicates not initialized with a red LED.  In this state, automated path planning is disabled
        + User presses the homing button while the arm is in home position until the LED goes from red to yellow to green.  In this state, the arm is ready for fully-automated control
    + Motor stall and timeout detection to handle sensor failure
    + Homing status provided to operator on dashboard
    + Arm will attempt home recovery in brownout conditions automatically
+ Semi-automated climb procedure
    + Operator completes climb sequence with only two button presses
+ Three degree-of-freedom arm with custom path planning and motion profiling
    + Setpoints for all rocket heights, loading station, and cargo ship on either side of the robot
    + Path planning performed in Cartesian coordinate space (x,y) to optimize path lengths and converts to actuator coordinate space (shoulder angle, extension, wrist angle) when commanding motors
    + Paths constrained by avoidance polygon to keep manipulator inside maximum frame perimeter extension and prevent collisions with other robot components
    + Paths constrained by arm physical limits to prevent over extension or under extension
    + Additional contraints enforced on wrist position to prevent game piece collisions with robot chassis when swinging through robot
    + All paths generated on-demand to move from current position to commanded position
    + Path velocities smoothed using s-curve motion profile to provide smooth speed ramping between positions.  This is based on the motion profile generator Excel spreadsheet provided by Cross The Road Electronics
    + Uses Talon SRX motion profiles to synchronize motion of rotation and extension motors
    + Visualization in VI front panel to see path plans and executed path
    + Demo program to generate and play paths interactively on a PC ([InteractiveDrawArmPath.vi](InteractiveDrawArmPath.vi))
+ [Operator control box](OperatorController)
    + Simple selection of 24 position presets using custom HID controller
    + Every button has integrated LED feedback
    + Based on Arduino Due
+ [Automatic code documentation](#Documentation)

## Dependencies
+ LabVIEW 2018 with 2019 FRC Updates
+ Cross the Road Electronics Hero Toolsuite [v5.14.1](https://github.com/CrossTheRoadElec/Phoenix-Releases/releases/download/aPhoenix-v5.14.0.0/CTRE.Phoenix.Framework.v5.14.0.0.zip)

## Robot Configuration
There are configurations for "Competition", "Practice", "Programming", and "Demo" chassis.  To select which to use, create a file named "/home/lvuser/RobotID" on the RoboRIO and create a line with one of the chassis names only.  If there are any non-whitespace characters before or after the robot ID, the configuration will default to "Competition".  If multiple lines have valid robot IDs, the first will be used.

## Special Thanks (in no particular order)
+ [MHeironimus's Arduino Joystick Library](https://github.com/MHeironimus/ArduinoJoystickLibrary). This made programming the operator control box simple
+ Our sponsors for the 2019 season.  Thank you for your continued support!
    + [Caterpillar](https://www.caterpillar.com)
    + [Limestone Community High School](http://limestone.k12.il.us)
    + [SC2](http://www.sc2services.com)

## License
This software is licensed under the [GNU General Public License v3](http://www.gnu.org/licenses/#GPL).  If you would like to use this software under the terms of a different license agreement, please [contact us](mailto:1756argos1756@limestone310.org).
