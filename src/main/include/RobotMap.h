#pragma once







/**
 *  MAKE SURE TO SET THIS TO THE CORRECT VALUE BEFORE DEPLOYING CODE!!!
 */
#define COMPBOT false






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
#define MaxVelocity 1425 //5700    // This is capped at the slowest velocity on ANY robot to ensure that paths work the same
#define PathfinderMaxVelocity 0.600375 //2.4015
#define DriveRampRate 0.25  // Minimum time (sec) to go from 0 to full

// SPARK MAX IDs
#define LMaster 1
#define LSlave 2
#define LSlave2 6
#define RMaster 3
#define RSlave 4
#define RSlave2 7
#define IntakeArmMotor 5

// Talon SRX IDs
#define BallShooter 1

// Solenoid IDs
#define ShooterSolenoidA 2
#define ShooterSolenoidB 3
#define ClawSolenoidA 4
#define ClawSolenoidB 5
#define ExtenderSolenoidA 0
#define ExtenderSolenoidB 1
#define ClawLockSolenoidA 6
#define ClawLockSolenoidB 7

#define LimitSwitchID 0

//BallIntake PID values
#define BallIntake_gearRatio 50.0

#define BallIntakeDownDirection -1 // Sign of moving downwards
#define BallIntakeDownPosLimit 0.5  // Magnitude of downward rotation allowed (do not put sign)
#define BallIntakeUpPosLimit 0.1 //Magitude of upward rotation allowed (do not put sign)
#define BallIntakeUpPos 0.05

#if COMPBOT
    #define BallIntake_LimitSwitchPressed true
#else
    #define BallIntake_LimitSwitchPressed false
#endif

//Up
#define BallIntake_kpUp 0.03
#define BallIntake_kiUp 0
#define BallIntake_kdUp 0
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
#define BallIntake_kpDown 0.015
#define BallIntake_kiDown 0
#define BallIntake_kdDown 0
#define BallIntake_kfDown 0
#define BallIntake_izoneDown 0
#define BallIntake_minOutDown -0.5
#define BallIntake_maxOutDown 1
#define BallIntake_allowedErrorDown 0
#define BallIntake_maxAccelDown 2000
#define BallIntake_minVelocityDown 0
#define BallIntake_maxVelocityDown 4000
#define BallIntake_DownPID 1

//Climb
#define BallIntake_kpClimb 1
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

//Lock arm
#define BallIntake_kpLock 1
#define BallIntake_kiLock 0
#define BallIntake_kdLock 0
#define BallIntake_kfLock 0
#define BallIntake_izoneLock 0
#define BallIntake_minOutLock 0.05
#define BallIntake_maxOutLock 0.3
#define BallIntake_allowedErrorLock 0
#define BallIntake_maxAccelLock 0
#define BallIntake_minVelocityLock 0
#define BallIntake_maxVelocityLock 0
#define BallIntake_LockPID 3

//Ball Shooter Subsystem Extend and Retract for the Solenoids
#if COMPBOT
#define BallShooter_Extend frc::DoubleSolenoid::Value::kReverse
#define BallShooter_Retract frc::DoubleSolenoid::Value::kForward
#else
#define BallShooter_Extend frc::DoubleSolenoid::Value::kForward
#define BallShooter_Retract frc::DoubleSolenoid::Value::kReverse
#endif

//Hatch Panel Claw Subsystem Extend, Retract, Open, and Close for the Solenoids
#if COMPBOT
#define Claw_Extend frc::DoubleSolenoid::Value::kForward
#define Claw_Retract frc::DoubleSolenoid::Value::kReverse
#define Claw_Close frc::DoubleSolenoid::Value::kForward
#define Claw_Open frc::DoubleSolenoid::Value::kReverse
#else
#define Claw_Extend frc::DoubleSolenoid::Value::kForward
#define Claw_Retract frc::DoubleSolenoid::Value::kReverse
#define Claw_Close frc::DoubleSolenoid::Value::kForward
#define Claw_Open frc::DoubleSolenoid::Value::kReverse
#endif

#define Claw_Lock frc::DoubleSolenoid::Value::kReverse
#define Claw_Unlock frc::DoubleSolenoid::Value::kForward

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

// Rotate PID
#define Rotate_kp 0
#define Rotate_ki 0
#define Rotate_kd 0
#define Rotate_minOut -1
#define Rotate_maxOut 1