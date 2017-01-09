/*********************************
 * FRC 2016 - STRONGHOLD
 * TEAM: KNIGHTRISE 5678
 * ROBOT NAME:
 * PROGRAMMERS: BEN HIRASUNA, WALTER HICKS
 *
 *********************************
 *
 *
 *
 *
 */



#define LOOPS_PER_SECOND 50 //a constant

#include "WPILib.h"
class Robot: public IterativeRobot {

	/*bool isButtonPressed(int buttonCode){//dunno why you want this, just adds more to the disassembly
	 //i.e. less efficient
	 return stick.GetRawButton(buttonCode);	//changed it to a macro
	 }*/

	RobotDrive DriveSys; // robot drive system

	Joystick stick; // only joystick
	Joystick xbox;
	Joystick xbox_2;
	LiveWindow * lw;
	int autoLoopCounter;

public:
	Robot() :
		DriveSys(0, 1),
		// these must be initialized in the same order
		stick(0), xbox(1), xbox_2(2),
		// as they are declared above.
		lw(LiveWindow::GetInstance()),
		autoLoopCounter(0) {

		DriveSys.SetExpiration(0.1);
	}

private:
	//basic movement start

	/*int MS_counter=0;
	 int second=0;
	 int rps=0;//revolutions per second
	 int revolutionCounter=0;
	 int revolutionCounterForLED = 0;//resets self
	 auto rp500ms=0;//revolutions per half second (used for LED)*/

	//auto buttonTwoToggleCounter = 0;
	bool eject = false;
	//Compressor * Compr_MoveIntoLaunch = new Compressor(0);
	Joystick &CurrentController = stick;

	Solenoid * Solenoid_Launcher_Bottom = new Solenoid(0);
	Solenoid * Solenoid_Launcher_Top = new Solenoid(1);

	Talon * Motor_FrontWheel_Left = new Talon(0);
	Talon * Motor_FrontWheel_Right = new Talon(1);
	Talon * Motor_TopOutput_Positive = new Talon(2);
	Talon * Motor_TopOutput_Negative = new Talon(3);
	Spark * Motor_Intake_Positive = new Spark(4);
	Spark * Motor_Intake_Negative = new Spark(5);
	//Spark * Spark_Motor_Undefined_Usage = new Spark(4);

	DigitalInput * HallSensor = new DigitalInput(0);
	//basic movement end
	enum JoystickInputs {UNDEFINEDJSTK, ShootBallJSTK, UNDEF2JSTK,UNDEF3JSTK,UNDEF4JSTK,LowerIOMotorJSTK};
	enum XboxInputs {UNDEFINEDXBOX, LowerOutputXBOX,UNDEF2XBOX,LowerInputXBOX,ShootBallXBOX};

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

		if(_sqrt){
			try {
				x = sqrt(x);
			} catch (...) {
				x = sqrt(-x) * -1;
			}
		}
		else{
			return x*x;

		}
		return x;

	}

	void AutonomousInit() {
		autoLoopCounter = 0;
	}

	void AutonomousPeriodic() {

		DriveSys.Drive(-0.5, 0.0);


	}

	int ButtonPressed(unsigned int joystick, unsigned int xbox, bool xoj=false,bool wantBoolNotInt = false) {
		// int heldVars[2] = {joystick,xbox};
		if (wantBoolNotInt)
			return (stick.GetRawButton(joystick) || this->xbox.GetRawButton(xbox),0);

		if (!((bool)joystick) && !((bool)xbox)) {
			for (int i = 1; i > 14; i++) {
				if (stick.GetRawButton(i)) joystick = i;
				if (this->xbox.GetRawButton(i))xbox = i;
				if (joystick > 0 || xbox > 0)break;

			}
			if(xoj)return joystick;else return xbox;

		}

		if (stick.GetRawButton(joystick) || this->xbox.GetRawButton(xbox))
			if (xoj)return joystick;else return xbox; //button requested is pressed

		else return 0;
	}

	float contModVal(){/*controller modification value*/

		if(!CurrentController.GetIsXbox()){
			return ((CurrentController.GetThrottle()/4)+0.75);
		}
		else return 1;
	}


	void TeleopInit() {

	}



	void TeleopPeriodic() {

		/*		MS_counter++;

		 if(HallSensor->Get()==true){
		 revolutionCounter++;
		 revolutionCounterForLED++;
		 }

		 if(MS_counter % LOOPS_PER_SECOND == 0){

		 second++;

		 rps=(revolutionCounter);//overall

		 }





		 if(MS_counter%LOOPS_PER_SECOND/2==0){

		 rp500ms = revolutionCounterForLED;
		 revolutionCounterForLED=0;
		 }
		 */
		//	LED_COLOR(rp500ms/*times some scaling amount to work with the LED*/);
		// drive with arcade style (use right stick)

		//
		/*if(buttonTwoUnlocked==false){
		 buttonTwoResetTimer++;
		 if(buttonTwoResetTimer % LOOPS_PER_SECOND == 0){
		 buttonTwoUnlocked = true;
		 buttonTwoResetTimer = 0;
		 }
		 }*/

		//stick.GetY();,stick.GetX()
		//init motor and reverse the motor if true


		/*switch (ButtonPressed(0,0,true)) { //joystick

		case UNDEFINEDJSTK:Motor_Launcher_Top->Set(0,0);

		default:break;
		 */

		//	case ShootBallJSTK:
		//	Motor_Launcher_Top->Set(1,0);
		//break;

		//	case LowerIOMotorJSTK:
		//	Motor_Launcher_Bottom->Set(1,0);


		//}



		/*switch (ButtonPressed(0,0,false)) { //xbox controller

		case UNDEFINEDXBOX:Motor_Launcher_Top->Set(0,0);
		default:
			break;

		case ShootBallXBOX:
			Motor_Launcher_Top->Set(1,0);break; //because enums resolve to their array position, you can use them in a switch as I used them.

		case LowerIOMotorXBOX:
		Motor_Launcher_Bottom->Set(1,0);break;
		}*/


		if(xbox.GetRawButton(7) && xbox.GetRawButton(8)){
			CurrentController = stick;

		}



		if(xbox_2.GetRawButton(7) && xbox_2.GetRawButton(8)){
			CurrentController = xbox_2;

		}

		if(stick.GetRawButton(11) && stick.GetRawButton(13)){
			CurrentController = xbox;

		}




		if(CurrentController.GetRawButton(ShootBallJSTK)||CurrentController.GetRawButton(ShootBallXBOX)){

			Motor_TopOutput_Negative->Set(-1);
			Motor_TopOutput_Positive->Set(1);
		}
		else{
			Motor_TopOutput_Negative->Set(0);
			Motor_TopOutput_Positive->Set(0);

		}
		if(CurrentController.GetRawButton(LowerIOMotorJSTK)||CurrentController.GetRawButton(LowerOutputXBOX)){
			Motor_Intake_Negative->Set(-1);
			Motor_Intake_Positive->Set(1);
		}
		else if(CurrentController.GetRawButton(6)||CurrentController.GetRawButton(3)){
			Motor_Intake_Negative->Set(1);
			Motor_Intake_Positive->Set(-1);
		}
		else{
			Motor_Intake_Negative->Set(0);
			Motor_Intake_Positive->Set(0);

		}

		DriveSys.ArcadeDrive(CurrentController.GetY(), CurrentController.GetX()*contModVal());

		if(45 <=CurrentController.GetPOV() && CurrentController.GetPOV() <=135 ){
			Solenoid_Launcher_Top->Set(DoubleSolenoid::kForward);
		}

		if(45 <=CurrentController.GetPOV() && CurrentController.GetPOV() <=135 ){
			Solenoid_Launcher_Top->Set(DoubleSolenoid::kForward);
		}

		if(45 <=CurrentController.GetPOV() && CurrentController.GetPOV() <=135 ){
			Solenoid_Launcher_Top->Set(DoubleSolenoid::kForward);
		}

		if(45 <=CurrentController.GetPOV() && CurrentController.GetPOV() <=135 ){
			Solenoid_Launcher_Top->Set(DoubleSolenoid::kForward);
			Solenoid_Launcher_Top->Set(DoubleSolenoid::kReverse);
			Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kOff);
		}

		if(215 <=CurrentController.GetPOV() && CurrentController.GetPOV() <=315 ){
			Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kForward);
			Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kReverse);
			Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kOff);
		}




		/*		if(stick==true) buttonTwoToggleCounter++;
		 else buttonTwoToggleCounter=0;

		 if(buttonTwoToggleCounter==1)eject=!eject;

		 if(isButtonPressed(1))
		 if(eject==true)Motor_Launcher->Set(0.5,1.0);
		 else Motor_Launcher->Set(0.5,-1);
		 else Motor_Launcher->SetExpiration(0.1);*/

		//as optimized as its gonna get
		//yes, it's hard to understand if you didn't write it
		//But, it uses minimal memory and the robot will be very responsive.

	}

	void TestPeriodic() {
		lw->Run();


	}
};

START_ROBOT_CLASS(Robot)
