#include <RobotMap.h>

// SmartDashboard Keys
const std::string LeftVelocity = "LeftVelocity";
const std::string RightVelocity = "RightVelocity";
const std::string ArmPosition = "Intake Arm Position";
const std::string ArmSpeed = "Intake Arm Velocity";

// Drivebase Settings
const double RMaxVelocity = 5800.0;
const double LMaxVelocity = 5700.0; //5580.0      
const double GearRatio = 9.47 / 1.0;       // 9.47 motor revolutions to 1 output revolution
const double WheelDiameter = .1524;      // wheel diameter in meters (6")
const double MaxVelocity = MINVAL(RMaxVelocity, LMaxVelocity);    // This is capped at the slowest velocity on ANY robot to ensure that paths work the same
const double PathfinderMaxVelocity = 1.20075; // Meters/second
const double PathfinderMaxRPM = PathfinderMaxVelocity * 60.0 / (WheelDiameter * 3.141592) * GearRatio;
const double DriveRampRate = 0.25;  // Minimum time (sec) to go from 0 to full
const double WheelbaseWidth = 0.6223; // Meters

// SPARK MAX IDs
const int LMaster = 1;
const int LSlave = 2;
const int LSlave2 = 6;
const int RMaster = 3;
const int RSlave = 4;
const int RSlave2 = 7;
const int IntakeArmMotor = 5;

// Talon SRX IDs
const int BallShooter = 1;

// Solenoid IDs
const int ShooterSolenoidA = 2;
const int ShooterSolenoidB = 3;
const int ClawSolenoidA = 4;
const int ClawSolenoidB = 5;
const int ExtenderSolenoidA = 0;
const int ExtenderSolenoidB = 1;
const int ClawLockSolenoidA = 6;
const int ClawLockSolenoidB = 7;

// Limit switches
const int LimitSwitchID = 0;

// Ball Intake Settings
#if COMPBOT
    const double BallIntake_gearRatio = 62.5; // 50:1 gearbox and 12:15 sprocket
#else
    const double BallIntake_gearRatio = 50.0; // 50:1 gearbox
#endif

const int BallIntakeDownDirection = -1; // Sign of moving downwards
const double BallIntakeDownPosLimit = 0.5;  // Magnitude of downward rotation allowed (do not put sign)
const double BallIntakeUpPosLimit = 0.1; //Magitude of upward rotation allowed (do not put sign)
const double BallIntakeUpPos = 0.05;

// Limit switch pressed position (true = closed, false = open)
#if COMPBOT
    const bool BallIntake_LimitSwitchPressed = true;
#else
    const bool BallIntake_LimitSwitchPressed = false;
#endif

// Up
const double BallIntake_kpUp = 0.02;
const double BallIntake_kiUp = 0;
const double BallIntake_kdUp = 0;
const double BallIntake_kfUp = 0;
const double BallIntake_izoneUp = 0;
const double BallIntake_minOutUp = -1;
const double BallIntake_maxOutUp = 1;
const double BallIntake_allowedErrorUp = 0;
const double BallIntake_maxAccelUp = 2000;
const double BallIntake_minVelocityUp = 0;
const double BallIntake_maxVelocityUp = 4000;
const double BallIntake_UpPID = 0;

//Down
const double BallIntake_kpDown = 0.001;
const double BallIntake_kiDown = 1e-12;
const double BallIntake_kdDown = 0;
const double BallIntake_kfDown = 0;
const double BallIntake_izoneDown = 0;
const double BallIntake_minOutDown = -0.7;
const double BallIntake_maxOutDown = 1;
const double BallIntake_allowedErrorDown = 0;
const double BallIntake_maxAccelDown = 850;
const double BallIntake_minVelocityDown = 0;
const double BallIntake_maxVelocityDown = 1100;
const double BallIntake_DownPID = 1;

//Lock arm
const double BallIntake_kpLock = 1;
const double BallIntake_kiLock = 0;
const double BallIntake_kdLock = 0;
const double BallIntake_kfLock = 0;
const double BallIntake_izoneLock = 0;
const double BallIntake_minOutLock = 0.05;
const double BallIntake_maxOutLock = 0.3;
const double BallIntake_allowedErrorLock = 0;
const double BallIntake_maxAccelLock = 0;
const double BallIntake_minVelocityLock = 0;
const double BallIntake_maxVelocityLock = 0;
const double BallIntake_LockPID = 3;

//Ball Shooter Subsystem Extend and Retract for the Solenoids
#if COMPBOT
    const frc::DoubleSolenoid::Value BallShooter_Extend = frc::DoubleSolenoid::Value::kReverse; 
    const frc::DoubleSolenoid::Value BallShooter_Retract = frc::DoubleSolenoid::Value::kForward; 
#else
    const frc::DoubleSolenoid::Value BallShooter_Extend = frc::DoubleSolenoid::Value::kReverse; 
    const frc::DoubleSolenoid::Value BallShooter_Retract = frc::DoubleSolenoid::Value::kForward; 
#endif

//Hatch Panel Claw Subsystem Extend, Retract, Open, and Close for the Solenoid
#if COMPBOT
    const frc::DoubleSolenoid::Value Claw_Extend = frc::DoubleSolenoid::Value::kForward;
    const frc::DoubleSolenoid::Value Claw_Retract = frc::DoubleSolenoid::Value::kReverse;
    const frc::DoubleSolenoid::Value Claw_Open = frc::DoubleSolenoid::Value::kReverse;
    const frc::DoubleSolenoid::Value Claw_Close = frc::DoubleSolenoid::Value::kForward;
    const frc::DoubleSolenoid::Value Claw_Lock = frc::DoubleSolenoid::Value::kReverse;
    const frc::DoubleSolenoid::Value Claw_Unlock = frc::DoubleSolenoid::Value::kForward;
#else
    const frc::DoubleSolenoid::Value Claw_Extend = frc::DoubleSolenoid::Value::kForward;
    const frc::DoubleSolenoid::Value Claw_Retract = frc::DoubleSolenoid::Value::kReverse;
    const frc::DoubleSolenoid::Value Claw_Open = frc::DoubleSolenoid::Value::kReverse;
    const frc::DoubleSolenoid::Value Claw_Close = frc::DoubleSolenoid::Value::kForward;
    const frc::DoubleSolenoid::Value Claw_Lock = frc::DoubleSolenoid::Value::kForward;
    const frc::DoubleSolenoid::Value Claw_Unlock = frc::DoubleSolenoid::Value::kReverse;
#endif