#pragma once

#include <string>
#include <frc/DoubleSolenoid.h>




/**
 *  MAKE SURE TO SET THIS TO THE CORRECT VALUE BEFORE DEPLOYING CODE!!!
 */
#define COMPBOT true




#define MINVAL(x, y) (((x) > (y)) ? (x) : (y)) // Get the minimum of two values (macro)




// SmartDashboard keys
const extern std::string LeftVelocity;
const extern std::string RightVelocity;
const extern std::string ArmPosition;
const extern std::string ArmSpeed;


// Drivebase settings
const extern double RMaxVelocity;
const extern double LMaxVelocity;     
const extern double GearRatio;
const extern double WheelDiameter;
const extern double MaxVelocity;
const extern double PathfinderMaxVelocity;
const extern double PathfinderMaxRPM;
const extern double DriveRampRate;
const extern double WheelbaseWidth;

// SPARK MAX IDs
const extern int LMaster;
const extern int LSlave;
const extern int LSlave2;
const extern int RMaster;
const extern int RSlave;
const extern int RSlave2;
const extern int IntakeArmMotor;

// Talon SRX IDs
const extern int BallShooter;

// Solenoid IDs
const extern int ShooterSolenoidA;
const extern int ShooterSolenoidB;
const extern int ClawSolenoidA;
const extern int ClawSolenoidB;
const extern int ExtenderSolenoidA;
const extern int ExtenderSolenoidB;
const extern int ClawLockSolenoidA;
const extern int ClawLockSolenoidB;

// Limit switches
const extern int LimitSwitchID;
const extern int SecondLimitSwitchId;

//BallIntake PID values
const extern double BallIntake_gearRatio;

const extern int BallIntakeDownDirection;
const extern double BallIntakeDownPosLimit;
const extern double BallIntakeUpPosLimit;
const extern double BallIntakeUpPos;

const extern bool BallIntake_LimitSwitchPressed;
const extern bool BallIntake_SecondSwitchPressed;

//Up
const extern double BallIntake_kpUp;
const extern double BallIntake_kiUp;
const extern double BallIntake_kdUp;
const extern double BallIntake_kfUp;
const extern double BallIntake_izoneUp;
const extern double BallIntake_minOutUp;
const extern double BallIntake_maxOutUp;
const extern double BallIntake_allowedErrorUp;
const extern double BallIntake_maxAccelUp;
const extern double BallIntake_minVelocityUp;
const extern double BallIntake_maxVelocityUp;
const extern double BallIntake_UpPID;

//Down
const extern double BallIntake_kpDown;
const extern double BallIntake_kiDown;
const extern double BallIntake_kdDown;
const extern double BallIntake_kfDown;
const extern double BallIntake_izoneDown;
const extern double BallIntake_minOutDown;
const extern double BallIntake_maxOutDown;
const extern double BallIntake_allowedErrorDown;
const extern double BallIntake_maxAccelDown;
const extern double BallIntake_minVelocityDown;
const extern double BallIntake_maxVelocityDown;
const extern double BallIntake_DownPID;

//Lock arm
const extern double BallIntake_kpLock;
const extern double BallIntake_kiLock;
const extern double BallIntake_kdLock;
const extern double BallIntake_kfLock;
const extern double BallIntake_izoneLock;
const extern double BallIntake_minOutLock;
const extern double BallIntake_maxOutLock;
const extern double BallIntake_allowedErrorLock;
const extern double BallIntake_maxAccelLock;
const extern double BallIntake_minVelocityLock;
const extern double BallIntake_maxVelocityLock;
const extern double BallIntake_LockPID;

//Ball Shooter Subsystem Extend and Retract for the Solenoids
const extern frc::DoubleSolenoid::Value BallShooter_Extend; 
const extern frc::DoubleSolenoid::Value BallShooter_Retract; 

//Hatch Panel Claw Subsystem Extend, Retract, Open, and Close for the Solenoids
const extern frc::DoubleSolenoid::Value Claw_Extend, Claw_Retract,
                                        Claw_Open, Claw_Close,
                                        Claw_Lock, Claw_Unlock;