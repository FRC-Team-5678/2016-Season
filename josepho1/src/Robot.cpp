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

#include "WPILib.h"

class Robot: public IterativeRobot
{
	RobotDrive myRobot; // robot drive system

	Joystick stick; // only joystick
	Joystick Xbox1;

	int autoLoopCounter;


public:
	Robot() :
		myRobot(2, 3),	// initialize the RobotDrive to use motor controllers on ports 0 and 1
		stick(0), Xbox1(1),
		autoLoopCounter(0){
		myRobot.SetExpiration(0.1);
	}

private:
	/*LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const char * autoNameDefault = "Default";
	const char * autoNameCustom = "My Auto";
	char * autoSelected;
	 */

	Talon * Motor_FrontWheel_Left 				= new Talon(2);
	Talon * Motor_FrontWheel_Right 				= new Talon(3);
	Victor * Motor_Intake_Positive 				= new Victor(4);
	Victor * Motor_Intake_Negative 				= new Victor(5);

	DigitalInput * UPPER_LIMIT                  = new DigitalInput(0);
	DigitalInput * LOWER_LIMIT					= new DigitalInput(1);

	enum JoystickInputs {UNDEFINEDJSTK, StickIn1, StickIn2, StickIn3, StickIn4, StickIn5, StickIn6, StickIn7, StickIn8, StickIn9};
	enum XboxInputs {UNDEFINEDXBOX, XboxIn1, XboxIn2, XboxIn3, XboxIn4, XboxIn5, XboxIn6, XboxIn7, XboxIn8, XboxIn9};

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

		jstkready = stick.GetRawButton(jstk);
		if(!jstkready){
			return this->Xbox1.GetRawButton(xbox);
		}
		else return jstkready;
	}
	void RobotInit(){
		/*
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		 */
	}
	void AutonomousInit() {
	}
	void AutonomousPeriodic() {
	}
	void TeleopInit() {

	}
	int limittogglecounter = 0;
	bool limiton = false;
	bool override= false;

	void TeleopPeriodic() {
		//std::cout << std::endl << UPPER_LIMIT->Get() <<std::endl <<LOWER_LIMIT->Get();


		if(!override){
			myRobot.ArcadeDrive((-stick.GetY()*((-(((-stick.GetThrottle()+1)/2))*0.8))),(stick.GetX()*((-(((-stick.GetThrottle()+1)/2))*0.75))));
			if(buttonPressed(StickIn4,XboxIn1) & LOWER_LIMIT->Get()){
				//std::cout<< std::endl<<"Down limit";
				Motor_Intake_Positive->Set(-.25);
			}
			else if(buttonPressed(StickIn6,XboxIn4)& UPPER_LIMIT->Get()){
				//std::cout<< std::endl<<"Up limit";
				Motor_Intake_Positive->Set(.4);
			}
			else{
				Motor_Intake_Positive->Set(0);
			}

			if(buttonPressed(StickIn3)){
				//std::cout<< std::endl<<"StickIn3 btn";
				Motor_Intake_Negative->Set(-.25);
			}
			else if(buttonPressed(StickIn5)){
				//std::cout<< std::endl<<"StickIn5 btn";
				Motor_Intake_Negative->Set(.25);
			}
			else{
				Motor_Intake_Negative->Set(0);
			}
		}
		if(override){
			myRobot.ArcadeDrive(Xbox1.GetY()*0.55, -Xbox1.GetX()*0.5);
			if(buttonPressed(UNDEFINEDXBOX,XboxIn1) & LOWER_LIMIT->Get()){
				//std::cout<< std::endl<<"Down limit";
				Motor_Intake_Positive->Set(-.25);
			}
			else if(buttonPressed(UNDEFINEDXBOX,XboxIn4)& UPPER_LIMIT->Get()){
				//std::cout<< std::endl<<"Up limit";
				Motor_Intake_Positive->Set(.4);
			}
			else{
				Motor_Intake_Positive->Set(0);
			}

			if(buttonPressed(UNDEFINEDXBOX,XboxIn3)){
				//std::cout<< std::endl<<"close";
				Motor_Intake_Negative->Set(-.25);
			}
			else if(buttonPressed(UNDEFINEDXBOX,XboxIn2)){
				//std::cout<< std::endl<<"open";
				Motor_Intake_Negative->Set(.25);
			}
			else{
				Motor_Intake_Negative->Set(0);
			}
		}



		if(buttonPressed(UNDEFINEDXBOX,XboxIn5)& buttonPressed(UNDEFINEDXBOX,XboxIn6)){
			override=true;
			std::cout << std::endl << "Taken!";

		}
		if(buttonPressed(UNDEFINEDXBOX,XboxIn7)& buttonPressed(UNDEFINEDXBOX,XboxIn8)){
			override=false;
			std::cout << std::endl << "Given!";

		}





	}

	void TestInit(){


	}

	bool khit = false;
	float in1x=0.0,in1y=0.0,in2x=0.0,in2y=0.0, th1=0.0;

	void TestPeriodic() {

		in1y = (-stick.GetY()*((-(((-stick.GetThrottle()+1)/2))*0.8)));
		in1x = (stick.GetX()*((-(((-stick.GetThrottle()+1)/2))*0.75)));
		in2y = (Xbox1.GetY()*0.55);
		in2x = (-Xbox1.GetX()*0.5);
		th1 = ((-stick.GetThrottle()+1)/2);

		std::cout << std::endl << "Throttle" <<std::endl <<th1;
		std::cout << std::endl << "Joystick Y" <<std::endl <<in1y;
		std::cout << std::endl << "Joystick X" <<std::endl <<in1x;
		std::cout << std::endl << "Xbox Y" <<std::endl <<in2y;
		std::cout << std::endl << "Xbox X" <<std::endl <<in2x;

		if(buttonPressed(StickIn1,XboxIn1)){std::cout << std::endl << "1";}
		if(buttonPressed(StickIn1,XboxIn2)){std::cout << std::endl << "2";}
		if(buttonPressed(StickIn1,XboxIn3)){std::cout << std::endl << "3";}
		if(buttonPressed(StickIn1,XboxIn4)){std::cout << std::endl << "4";}
		if(buttonPressed(StickIn1,XboxIn5)){std::cout << std::endl << "5";}
		if(buttonPressed(StickIn1,XboxIn6)){std::cout << std::endl << "6";}
		if(buttonPressed(StickIn1,XboxIn7)){std::cout << std::endl << "7";}
		if(buttonPressed(StickIn1,XboxIn8)){std::cout << std::endl << "8";}
		if(buttonPressed(StickIn1,XboxIn9)){std::cout << std::endl << "9";}
	}
};

START_ROBOT_CLASS(Robot)
