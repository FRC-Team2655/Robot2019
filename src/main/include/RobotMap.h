#pragma once









/**
 *  MAKE SURE TO SET THIS TO THE CORRECT VALUE BEFORE DEPLOYING CODE!!!
 */
#define COMPBOT true






// SmartDashboard keys
#define LeftVelocity "LeftVelocity"
#define RightVelocity "RightVelocity"
#define ArmPosition "Intake Arm Position"
#define ArmSpeed "Intake Arm Velocity"

#define MINVAL(x, y) (((x) > (y)) ? (x) : (y)) // Get the minimum of two values (macro)

// Drivebase settings (leave in this header because important to pathfinder use)
#define RMaxVelocity 5800.0 //5950.0      // motor revolutions / min
#define LMaxVelocity 5700.0 //5580.0      
#define GearRatio 9.47 / 1.0       // 9.47 motor revolutions to 1 output revolution
#define WheelDiameter .1524      // wheel diameter in meters (6")
#define MaxVelocity MINVAL(LMaxVelocity, RMaxVelocity)
#define PathfinderMaxVelocity MaxVelocity / GearRatio / 60 * WheelDiameter * 3.141592

// SPARK MAX IDs
#define LMaster 1
#define LSlave 2
#define RMaster 3
#define RSlave 4
#define IntakeArmMotor 5
#define LandingGearArmMotor 6
#define LandingGearDriveMotor 7
#define LandingGearArmSlave 8
#define LandingGearArmSlave2 9

// Talon SRX IDs
#define BallShooter 1

// Solenoid IDs
#define ShooterSolenoidA 2
#define ShooterSolenoidB 3
#define ClawSolendoidA 4
#define ClawSolendoidB 5
#define ExtenderSolenoidA 0
#define ExtenderSolenoidB 1
#define LockSolenoid 6

#define LimitSwitchID 0

#define BallIntakeDownDirection -1 // Sign of moving downwards

//BallIntake PID values
#define BallIntake_gearRatio (50.0 / 1.0) * (12.0 / 15.0)  // Gearbox ratio * sprocket ratio

#if COMPBOT
#define BallIntake_LimitSwitchPressed true
#else
#define BallIntake_LimitSwitchPressed false
#endif

//Up
#define BallIntake_kpUp 0.0005
#define BallIntake_kiUp 0
#define BallIntake_kdUp 1e-3
#define BallIntake_kfUp 0
#define BallIntake_izoneUp 0
#define BallIntake_minOutUp -1
#define BallIntake_maxOutUp 1
#define BallIntake_allowedErrorUp 0
#define BallIntake_maxAccelUp 2000
#define BallIntake_minVelocityUp 0
#define BallIntake_maxVelocityUp 4000
#define BallIntake_UpPID 0

//Down
#define BallIntake_kpDown 0.00075
#define BallIntake_kiDown 0
#define BallIntake_kdDown 0
#define BallIntake_kfDown 0
#define BallIntake_izoneDown 0
#define BallIntake_minOutDown -1
#define BallIntake_maxOutDown 1
#define BallIntake_allowedErrorDown 0.05
#define BallIntake_maxAccelDown 1000
#define BallIntake_minVelocityDown 0
#define BallIntake_maxVelocityDown 2000
#define BallIntake_DownPID 1

//Climb
#define BallIntake_kpClimb 0.4
#define BallIntake_kiClimb 0
#define BallIntake_kdClimb 0
#define BallIntake_kfClimb 0
#define BallIntake_izoneClimb 0
#define BallIntake_minOutClimb -1
#define BallIntake_maxOutClimb 1
#define BallIntake_allowedErrorClimb 0
#define BallIntake_maxAccelClimb 18000
#define BallIntake_minVelocityClimb 0
#define BallIntake_maxVelocityClimb 6000
#define BallIntake_ClimbPID 2

//Ball Shooter Subsystem Extend and Retract for the Solenoids
#define BallShooter_Extend frc::DoubleSolenoid::Value::kForward
#define BallShooter_Retract frc::DoubleSolenoid::Value::kReverse

//Hatch Panel Claw Subsystem Extend, Retract, Open, and Close for the Solenoids
#define Claw_Extend frc::DoubleSolenoid::Value::kReverse
#define Claw_Retract frc::DoubleSolenoid::Value::kForward
#define Claw_Close frc::DoubleSolenoid::Value::kReverse
#define Claw_Open frc::DoubleSolenoid::Value::kForward

//LandingGearArm PID values
#define LandingGearArm_gearRatio 45.33 / 1.0
#define LandingGearArm_kp 0
#define LandingGearArm_ki 0
#define LandingGearArm_kd 0
#define LandingGearArm_kf 0
#define LandingGearArm_izone 0
#define LandingGearArm_minOut -1
#define LandingGearArm_maxOut 1
#define LandingGearArm_allowedError 0
#define LandingGearArm_maxAccel 0
#define LandingGearArm_minVelocity 0
#define LandingGearArm_maxVelocity 0