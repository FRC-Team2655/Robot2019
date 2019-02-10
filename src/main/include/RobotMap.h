#pragma once

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
