#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <OI.h>
#include <subsystems/DriveBaseSubsystem.h>
#include <subsystems/BallIntakeArmSubsystem.h>
#include <team2655/autonomous.hpp>
#include <subsystems/BallShooterSubsystem.h>
#include <subsystems/HatchPanelSubsystem.h>
#include <subsystems/LandingGearArmSubsystem.h>
#include <subsystems/LandingGearDriveSubsystem.h>

class Robot : public frc::TimedRobot {
public:
  static OI oi;
  static DriveBaseSubsystem driveBase;
  static BallIntakeArmSubsystem ballIntakeArm;
  static BallShooterSubsystem ballShooter;
  static HatchPanelSubsystem hatchPanel;
  static HatchPanelSubsystem hatchMover;
  static LandingGearArmSubsystem landingGearArm;
  static LandingGearDriveSubsystem landingGearDrive;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;

private:
  team2655::AutoManager autoManager;
  std::unique_ptr<frc::CommandGroup> autoCommandPtr;
};
