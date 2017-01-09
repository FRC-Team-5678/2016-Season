/*********************************
 * FRC 2015 robot - code made in 2016
 * TEAM: KNIGHTRISE 5678
 * ROBOT NAME:
 * PROGRAMMERS: BEN HIRASUNA, WALTER HICKS, ANDREW LEVIN
 *
 *********************************
 *
 *
 *
 *
 */
//FOR ALL FUTURE VERSIONS, IF YOU WANT PNUMATICS, UNCOMMENT THE LINE BELOW

#define LOOPS_PER_SECOND 50 //a constant

#include "WPILib.h"
class Robot: public IterativeRobot {

	RobotDrive myRobot; // robot drive system
	Joystick driveStick;
	Joystick stick; // only joystick
	Joystick xbox;
	Joystick xbox_2;
	Joystick unused;

	int autoLoopCounter;

public:
	Robot() :
			myRobot(0, 1),
			// these must be initialized in the same order
			stick(0), xbox(1), xbox_2(2),unused(3),
			// as they are declared above.

			autoLoopCounter(0) {
		myRobot.SetExpiration(0.1);
	}

private:
	Talon * Motor_FrontWheel_Left = new Talon(2);
	Talon * Motor_FrontWheel_Right = new Talon(3);
	Victor * Motor_Intake_Positive = new Victor(4);
	Victor * Motor_Intake_Negative = new Victor(5);

	DigitalInput * UPPER_LIMIT = new DigitalInput(0);
	DigitalInput * LOWER_LIMIT = new DigitalInput(1);
	SmartDashboard * sd = new SmartDashboard;

	enum JoystickInputs {UNDEFINEDJSTK,LowerOutputJSTK,UNDEF2JSTK,UNDEF3JSTK,UNDEF4JSTK,ShootBallJSTK,LowerInputJSTK,SendToXBOX1,UNDEF6JSTK,SendToXBOX2};
	enum XboxInputs 	{UNDEFINEDXBOX,XboxIn1,XboxIn2,XboxIn3,XboxIn4,XboxIn5,XboxIn6,XboxIn7,XboxIn8};

	/*
	 * FOR THE ROBOT CODE, DO NOT USE 0. BECAUSE JOYSTICKS READ FROM 1 - 14, AND
	 * YOU CANNOT INCREMENT AN ENUM POSITION (These are not strings, they are terms that represent
	 * their number in their respective slots) IT WILL NOT WORK, AND YOU'RE GOING TO
	 * CAUSE A BIG PROBLEM DUE TO YOU MAKING THE PROGRAM SCAN FOR SOMETHING THAT DOESN'T EXIST
	 *
	 * I don't know what the robot does when the program throws an exception.
	 * I don't want to find out either.
	 *
	 * An enum is a collection of constants in which each value is assigned to
	 * its array position (0-max)
	 *
	 *	This way, we can just name each varriable the same thing for each one. (with an extension
	 *	to avoid ambiguity)
	 *
	 */
	float SmoothCurve(float x, bool _sqrt) {
		if (_sqrt) {
			try {
				return x = sqrt(x);
			} catch (...) {
				return sqrt(-x) * -1;
			}
		} else
			return x * x;
	}
	int bintodec(std::string bin) {
		int conv = 0;
		for (unsigned i = 0; i < bin.length(); i++) {
			if (bin[bin.length() - i - 1] == '0')
				continue;
			conv += pow(2, i);
		}
		return conv;
	}
	bool buttonPressed(unsigned int jstk = 0, unsigned int xbox = 0) {
		bool jstkready = false;
		if (!spyenabled) {
			jstkready = stick.GetRawButton(jstk);
			if (!jstkready) {
				return this->xbox.GetRawButton(xbox);
			} else
				return jstkready;
		}
		else if (spyenabled) {
			return xbox_2.GetRawButton(xbox);
		}
		return false;
	}
	void RobotInit() {
	}
	void AutonomousInit() {
		Motor_FrontWheel_Left->Set(stick.GetThrottle());
		Motor_FrontWheel_Right->Set(-stick.GetThrottle());
	}
	void AutonomousPeriodic() {
		Motor_FrontWheel_Left->Set(stick.GetThrottle());
		Motor_FrontWheel_Right->Set(-stick.GetThrottle());
	}
	//int joystickIndex = 0;
	bool spyenabled = false;
	bool annoying = false;
	float limiter=((stick.GetThrottle()/4)+0.75);
	driveStick = new Joystick(1);
	void TeleopInit() {
	}
	void TeleopPeriodic() {
		if (xbox_2.GetRawButton(XboxIn7) & xbox_2.GetRawButton(XboxIn8)){
			spyenabled = false;
			limiter=((stick.GetThrottle()/4)+0.75);
			//Joystick DriveStick=stick;
		}
		if (stick.GetRawButton(SendToXBOX1) & stick.GetRawButton(SendToXBOX2)){
			spyenabled = true;
			limiter=0.25;
			//Joystick DriveStick=xbox;
		}
		//myRobot.ArcadeDrive(DriveStick*limiter);

	if(buttonPressed(stick.GetRawButton(LowerOutputJSTK),XboxIn1)& LOWER_LIMIT->Get()) {

		Motor_Intake_Positive->Set(-.25);
	}else if(buttonPressed(stick.GetRawButton(LowerInputJSTK),XboxIn4)& UPPER_LIMIT->Get()) {
		Motor_Intake_Negative->Set(.25);
	} else {
		Motor_Intake_Negative->Set(0);
		Motor_Intake_Positive->Set(0);
	}
}
void TestInit() {

}
void TestPeriodic() {

}
};

START_ROBOT_CLASS(Robot);
