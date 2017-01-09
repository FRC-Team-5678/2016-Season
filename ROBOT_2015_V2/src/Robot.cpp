/*********************************
 * FRC 2015 -
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

//#define pnm


#define LOOPS_PER_SECOND 50 //a constant

#include "WPILib.h"
class Robot: public IterativeRobot {

	/*bool isButtonPressed(int buttonCode){//dunno why you want this, just adds more to the disassembly
	 //i.e. less efficient
	 return stick.GetRawButton(buttonCode);	//changed it to a macro
	 }*/


	RobotDrive DriveSys; // robot drive system

	Joystick stick; // only joystick
	Joystick stick_2;
	Joystick xbox;
	Joystick xbox_2;



	//CameraServer * cs;
	CameraServer * cs0;

	int autoLoopCounter;

public:
	Robot() :
		DriveSys(0, 1),
		// these must be initialized in the same order
		stick(0), stick_2(1), xbox(2), xbox_2(3),
		// as they are declared above.

		//cs(CameraServer::GetInstance()),
		cs0(CameraServer::GetInstance()),

		//sd();
		autoLoopCounter(0){

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
	//bool eject = false;

	USBCamera   * Bottom_Capture_Field = new USBCamera("cam0",true);
	//AxisCamera * Top_Capture_Field = new AxisCamera("Top");
	//bool debug = true;
	Talon * Motor_FrontWheel_Left 				= new Talon(2);
	Talon * Motor_FrontWheel_Right 				= new Talon(3);
	Victor * Motor_Intake_Positive 				= new Victor(4);
	Victor * Motor_Intake_Negative 				= new Victor(5);

	DigitalInput * UPPER_LIMIT                  = new DigitalInput(0);
	DigitalInput * LOWER_LIMIT					= new DigitalInput(1);
	SmartDashboard * sd = new SmartDashboard;
	//DigitalInput * HallSensor = new DigitalInput(0);
	//basic movement end
	// 7,9 :: 11,12 ::

	enum JoystickInputs {UNDEFINEDJSTK, LowerOutputJSTK, UNDEF2JSTK,UNDEF3JSTK,UNDEF4JSTK, ShootBallJSTK,LowerInputJSTK,SendToXBOX1,UNDEF6JSTK,SendToXBOX2};
	enum XboxInputs {UNDEFINEDXBOX, LowerOutputXBOX,UNDEF2XBOX,ShootBallXBOX,LowerInputXBOX, UNDEF5XBOX,UNDEF6XBOX,SendToJSTK1,SendToJSTK2};

	int solenoid1_toggleCounter = 0;

	bool init = false;
	bool solenoid0_open = false;
	bool solenoid1_direction = false;
	bool solenoid1_open = false;
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
			try {return x = sqrt(x);}
			catch (...) {return  sqrt(-x) * -1;}}
		else return x*x;
	}

	int bintodec(std::string bin){
		int conv = 0;
		for( unsigned i=0; i<bin.length(); i++ ) {
			if( bin[bin.length()-i-1] == '0' ) continue;
			conv += pow( 2, i );
		}
		return conv;
	}

	bool buttonPressed(unsigned int jstk=0, unsigned int xbox=0){
		bool jstkready = false;
		if(!spyenabled){
			jstkready = stick.GetRawButton(jstk);
			if(!jstkready){
				return this->xbox.GetRawButton(xbox);
			}
			else return jstkready;
		}

		else if(spyenabled){
			return xbox_2.GetRawButton(xbox);
		}
		return false;
	}
	void RobotInit(){

		//std::cout << &stick << "\t" << &xbox << "\t" << &xbox_2;
		//	cs->StartAutomaticCapture("Top");
		//		//	cs->SetQuality(320);
		//	cs0->SetQuality(320);

		//CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}


	void AutonomousInit() {
		//Motor_FrontWheel_Left->Set(stick_2.GetThrottle());
		//Motor_FrontWheel_Right->Set(-stick_2.GetThrottle());

	}

	void AutonomousPeriodic() {

		//Motor_FrontWheel_Left->Set(stick_2.GetThrottle());
		//Motor_FrontWheel_Right->Set(-stick_2.GetThrottle());

	}

	//int joystickIndex = 0;
	bool spyenabled = false;


	/*
	 *
	 *
	 *
	 *
	 *
	 *
	 */

	bool annoying = false;



	void TeleopInit() {


	}



	void TeleopPeriodic() {





		if(xbox_2.GetRawButton(SendToJSTK1) & xbox_2.GetRawButton(SendToJSTK2))
			spyenabled = false;


		if(stick.GetRawButton(SendToXBOX1 ) & stick.GetRawButton(SendToXBOX2))
			spyenabled = true;




		if(!spyenabled){
			if(!annoying){
				//DriveSys.ArcadeDrive(stick.GetY(), -stick.GetX()*((stick.GetThrottle()/4)+0.75));

				if(stick_2.GetRawButton(1)){

					DriveSys.ArcadeDrive(stick.GetY(),stick.GetX());

				}
				else{
					Motor_FrontWheel_Left->Set(stick.GetY());
					Motor_FrontWheel_Right->Set(-stick_2.GetY());
					//DriveSys.ArcadeDrive(stick_2.GetY(), -stick_2.GetX()*((stick_2.GetThrottle()/4)+0.75));

				}
			}
			else{
				Motor_FrontWheel_Left->Set(sin(stick.GetY()));

				Motor_FrontWheel_Left->Set(sin(stick_2.GetY()));
				if(rand()%100 == 0)
					Motor_FrontWheel_Left->Set((rand()%3)-1);
				Wait((float)((rand()%100)/100));
			}
		}
		if(spyenabled){
			DriveSys.ArcadeDrive((xbox_2.GetRawAxis(5)),(-xbox_2.GetRawAxis(4)));
			DriveSys.ArcadeDrive(xbox_2.GetY(),(-xbox_2.GetX()*0.5));

		}



		if(buttonPressed(LowerOutputJSTK,LowerOutputXBOX) & LOWER_LIMIT->Get()){
			Motor_Intake_Negative->Set(1);
			Motor_Intake_Positive->Set(-1);
		}


		else if(buttonPressed(LowerInputJSTK,LowerInputXBOX)& UPPER_LIMIT->Get()){
			Motor_Intake_Negative->Set(-0.35);
			Motor_Intake_Positive->Set(0.35);
		}
		else{
			Motor_Intake_Negative->Set(0);
			Motor_Intake_Positive->Set(0);

		}

	}





	void TestInit(){


	}
	bool khit = false;
	void TestPeriodic() {


		DriveSys.ArcadeDrive(stick.GetY(), -stick.GetX()*((stick.GetThrottle()/4)+0.75));

		/*if( buttonPressed(11,6)||xbox.GetRawButton(6)){
			//Solenoid_Pos_Top->Set(true);
			DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kReverse);
			solenoid0_open = true;
		}

		else if(!buttonPressed(11,6) && solenoid0_open){
			solenoid0_open = false;
			DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kForward);

		}
		else DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kOff);



		if( buttonPressed(12,5)||xbox.GetRawButton(5)){
			//Solenoid_Pos_Top->Set(true);
			DSolenoid_PosBall_Top->Set(DoubleSolenoid::kReverse);
			solenoid0_open = true;
		}

		else if(!buttonPressed(11,6) && solenoid0_open){
			solenoid0_open = false;
			DSolenoid_PosBall_Top->Set(DoubleSolenoid::kForward);

		}
		else DSolenoid_PosBall_Top->Set(DoubleSolenoid::kOff);


		 */
		//DSolenoid_PositionBall->Set(DoubleSolenoid::kOff);

		//	if(stick.GetRawButton(1))
		//Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kForward);
		//else Solenoid_Launcher_Bottom->Set(DoubleSolenoid::kOff);
		/*	if(!khit){
			if(stick.GetRawButton(5)){
				DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kForward);
				khit = true;
			}
			if(stick.GetRawButton(4)){
				DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kReverse);
				khit = true;
			}
			if(stick.GetRawButton(3)){
				DSolenoid_PosBall_Top->Set(DoubleSolenoid::kForward);
				khit = true;

			}
			if(stick.GetRawButton(6)){
				DSolenoid_PosBall_Top->Set(DoubleSolenoid::kReverse);
				khit = true;
			}
		}

		else{
			DSolenoid_PosBall_Top->Set(DoubleSolenoid::kOff);
			khit=false;
		}*/
	}
};

START_ROBOT_CLASS(Robot);
