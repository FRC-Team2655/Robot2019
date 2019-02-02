#pragma once

#include <string>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include<frc/Compressor.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <DriveBaseSubsystem.h>

#include <AutoCommands.h>
#include <team2655/autonomous.hpp>
#include <team2655/joystick.hpp>
#include <adi/ADIS16470_IMU.h>

#define MINVAL(x, y) (((x) > (y)) ? (x) : (y)) // Get the minimum of two values (macro)

#define RMaxVelocity 5950.0      // motor revolutions / min
#define LMaxVelocity 5580.0      
#define GearRatio 9.47 / 1       // 9.47 motor revolutions to 1 output revolution
#define WheelDiameter .1524      // wheel diameter in meters (6")
#define MaxVelocity MINVAL(LMaxVelocity, RMaxVelocity)
#define PathfinderMaxVelocity MaxVelocity / GearRatio / 60 * WheelDiameter * 3.141592

using MotorType = rev::CANSparkMax::MotorType;

using namespace team2655;

class Robot : public frc::TimedRobot {
public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;

  rev::CANSparkMax leftMaster {1, MotorType::kBrushless};
  rev::CANSparkMax leftSlave {2, MotorType::kBrushless};

  rev::CANSparkMax rightMaster {3, MotorType::kBrushless};
  rev::CANSparkMax rightSlave {4, MotorType::kBrushless};

  rev::CANEncoder leftEnc = leftMaster.GetEncoder();
  rev::CANEncoder rightEnc = rightMaster.GetEncoder();

  rev::CANPIDController leftPID = leftMaster.GetPIDController();
  rev::CANPIDController rightPID = rightMaster.GetPIDController();
  
  frc::Joystick js0 {0};

  frc::ADIS16470_IMU imu;
  
  //frc::Compressor compressor {0};
  DriveBaseSubsystem driveBase;

  static Robot *currentRobot;

  jshelper::AxisConfig driveAxisConfig, rotateAxisConfig;

  double leftStartRevolutions;

  AutoManager mgr; 
};
