#pragma once

#include <string>
#include <ctre/Phoenix.h>
#include <frc/Joystick.h>
#include <frc/TimedRobot.h>
#include <frc/smartdashboard/SendableChooser.h>
#include <DriveBaseSubsystem.h>

#include <team2655/autonomous.hpp>
#include <team2655/joystick.hpp>

using namespace team2655;

class Robot : public frc::TimedRobot {
 public:
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TestInit();
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;  

  WPI_TalonSRX leftMaster {1};
  WPI_TalonSRX leftSlave1 {2};
  WPI_TalonSRX leftSlave2 {3};

  WPI_TalonSRX rightMaster {5};
  WPI_TalonSRX rightSlave1 {4};
  WPI_TalonSRX rightSlave2 {6};
  
  frc::Joystick js0 {0};
  DriveBaseSubsystem driveBase;

  static Robot *currentRobot;
  AutoManager manager;

  jshelper::AxisConfig driveAxisConfig, rotateAxisConfig;
};
