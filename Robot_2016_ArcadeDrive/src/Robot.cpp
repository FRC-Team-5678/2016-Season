#include "WPILib.h"

class Robot: public IterativeRobot
{
	RobotDrive DriveSys; // robot drive system

	Joystick stick; // only joystick
	Joystick xbox;
	int autoLoopCounter;
public:
	Robot() :
		DriveSys(2, 3),	// initialize the RobotDrive to use motor controllers on ports 0 and 1
		stick(0), xbox(1),
		autoLoopCounter(0){
		DriveSys.SetExpiration(0.1);
	}

private:
	LiveWindow *lw = LiveWindow::GetInstance();
	SendableChooser *chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;


	USBCamera   * Bottom_Capture_Field = new USBCamera("cam0",true);

	DoubleSolenoid * DSolenoid_PosBall_Bottom 	= new DoubleSolenoid(0,1);
	DoubleSolenoid * DSolenoid_PosBall_Top 		= new DoubleSolenoid(2,3);
	Talon * Motor_FrontWheel_Left 				= new Talon(2);
	Talon * Motor_FrontWheel_Right 				= new Talon(3);
	Talon * Motor_TopOutput_Positive 			= new Talon(4);
	Talon * Motor_TopOutput_Negative 			= new Talon(5);
	Spark * Motor_Intake_Positive 				= new Spark(6);
	Spark * Motor_Intake_Negative 				= new Spark(7);



	SmartDashboard * sd = new SmartDashboard;


	enum JoystickInputs {UNDEFINEDJSTK, ShootBallJSTK, UNDEF2JSTK,UNDEF3JSTK,UNDEF4JSTK,LowerOutputJSTK,LowerInputJSTK,SendToXBOX1,UNDEF6JSTK,SendToXBOX2};
	enum XboxInputs {UNDEFINEDXBOX, LowerOutputXBOX,UNDEF2XBOX,LowerInputXBOX,ShootBallXBOX, UNDEF5XBOX,UNDEF6XBOX,SendToJSTK1,SendToJSTK2};

	int solenoid1_toggleCounter = 0;

	bool init = false;
	bool solenoid0_open = false;
	bool solenoid1_direction = false;
	bool solenoid1_open = false;

	void RobotInit()
	{
		chooser = new SendableChooser();
		chooser->AddDefault(autoNameDefault, (void*)&autoNameDefault);
		chooser->AddObject(autoNameCustom, (void*)&autoNameCustom);
		SmartDashboard::PutData("Auto Modes", chooser);
		CameraServer::GetInstance()->StartAutomaticCapture("cam0");
	}
	bool spyenabled = false;
	bool annoying = false;


	/**
	 * This autonomous (along with the chooser code above) shows how to select between different autonomous modes
	 * using the dashboard. The sendable chooser code works with the Java SmartDashboard. If you prefer the LabVIEW
	 * Dashboard, remove all of the chooser code and uncomment the GetString line to get the auto name from the text box
	 * below the Gyro
	 *
	 * You can add additional auto modes by adding additional comparisons to the if-else structure below with additional strings.
	 * If using the SendableChooser make sure to add them to the chooser code above as well.
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

			jstkready = stick.GetRawButton(jstk);
			if(!jstkready){
				return this->xbox.GetRawButton(xbox);
			}
			else return jstkready;

		return false;
	}


	void AutonomousInit() {
			Motor_FrontWheel_Left->Set(stick.GetThrottle());
			Motor_FrontWheel_Right->Set(-stick.GetThrottle());

		}

		void AutonomousPeriodic() {

			Motor_FrontWheel_Left->Set(stick.GetThrottle());
			Motor_FrontWheel_Right->Set(-stick.GetThrottle());

		}

	void TeleopInit() {


	}



	void TeleopPeriodic() {





		if(xbox.GetRawButton(SendToJSTK1) & xbox.GetRawButton(SendToJSTK2))
			spyenabled = false;


		if(stick.GetRawButton(SendToXBOX1 ) & stick.GetRawButton(SendToXBOX2))
			spyenabled = true;

		if(!spyenabled){
			DriveSys.ArcadeDrive((-stick.GetY()*(((((-stick.GetThrottle()+1)/2))*1))),(stick.GetX()*((-(((-stick.GetThrottle()+1)/2))*0.9))));
		}
		if(spyenabled){
			//DriveSys.ArcadeDrive((xbox.GetRawAxis(5)),(-xbox.GetRawAxis(4)));
			DriveSys.ArcadeDrive((xbox.GetY()*0.8),(-xbox.GetX()*0.8));
		}


		if(buttonPressed(ShootBallJSTK,ShootBallXBOX)){
			Motor_TopOutput_Negative->Set(1);
			Motor_TopOutput_Positive->Set(-1);
		}
		else{
			Motor_TopOutput_Negative->Set(0);
			Motor_TopOutput_Positive->Set(0);
		}



		if(buttonPressed(LowerOutputJSTK,LowerOutputXBOX)){
			Motor_Intake_Negative->Set(1);
			Motor_Intake_Positive->Set(-1);
		}
		else if(buttonPressed(LowerInputJSTK,LowerInputXBOX)){
			Motor_Intake_Negative->Set(-0.35);
			Motor_Intake_Positive->Set(0.35);
		}
		else{
			Motor_Intake_Negative->Set(0);
			Motor_Intake_Positive->Set(0);

		}


		if( buttonPressed(11,6)){
			//Solenoid_Pos_Top->Set(true);
			DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kReverse);
			solenoid0_open = true;
		}

		else if(!buttonPressed(11,6) & solenoid0_open){
			solenoid0_open = false;
			DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kForward);

		}
		else DSolenoid_PosBall_Bottom->Set(DoubleSolenoid::kOff);




		if(buttonPressed(12,5)){
			solenoid1_toggleCounter++;
			if(solenoid1_direction)
				DSolenoid_PosBall_Top->Set(DoubleSolenoid::kForward);


			else if(!solenoid1_direction)
				DSolenoid_PosBall_Top->Set(DoubleSolenoid::kReverse);
		}


		else   {
			solenoid1_toggleCounter=0;
			DSolenoid_PosBall_Top->Set(DoubleSolenoid::kOff);
		}

		if(solenoid1_toggleCounter==1)
			solenoid1_direction = !solenoid1_direction; //hackiest hack in the history of hacks
	}





	void TestInit(){


	}
	bool khit = false;
	float in1x=0.0,in1y=0.0,in2x=0.0,in2y=0.0, th1=0.0;
	void TestPeriodic() {
		lw->Run();


		in1y = (-stick.GetY()*(( (( (-stick.GetThrottle()+1) /2 )) *0.8)) );
		in1x = (stick.GetX()*((-(((-stick.GetThrottle()+1)/2))*0.75)));
		in2y = (xbox.GetY()*0.5);
		in2x = (-xbox.GetX()*0.55);
		th1 = ((-stick.GetThrottle()+1)/2);

		std::cout << std::endl << "Throttle" <<std::endl <<th1;
		std::cout << std::endl << "Joystick Y" <<std::endl <<in1y;
		std::cout << std::endl << "Joystick X" <<std::endl <<in1x;
		std::cout << std::endl << "Xbox Y" <<std::endl <<in2y;
		std::cout << std::endl << "Xbox X" <<std::endl <<in2x;



	}
};

START_ROBOT_CLASS(Robot)
