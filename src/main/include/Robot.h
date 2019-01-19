#pragma once

#include <string>
#include <rev/CANSparkMax.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include<frc/Compressor.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <DriveBaseSubsystem.h>

#include <team2655/autonomous.hpp>
#include <team2655/joystick.hpp>

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
  
  frc::Compressor compressor {0};
  DriveBaseSubsystem driveBase;

  static Robot *currentRobot;

  jshelper::AxisConfig driveAxisConfig, rotateAxisConfig;

  double leftStartRevolutions;
};
