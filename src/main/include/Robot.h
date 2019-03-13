#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <OI.h>
#include <subsystems/DriveBaseSubsystem.h>
#include <subsystems/BallIntakeArmSubsystem.h>
#include <team2655/autonomous.hpp>
#include <subsystems/BallShooterSubsystem.h>
#include <subsystems/HatchPanelClawSubsystem.h>

#include <frc/Compressor.h>

class Robot : public frc::TimedRobot {
public:
  static OI oi;
  static DriveBaseSubsystem driveBase;
  static BallIntakeArmSubsystem ballIntakeArm;
  static BallShooterSubsystem ballShooter;
  static HatchPanelClawSubsystem hatchPanelClaw;
  static bool hasEverResetBallIntakeArm;
  //frc::Command *slowIntakeCmd = nullptr;

  void RobotInit() override;
  void RobotPeriodic() override;
  void DisabledInit() override;
  void DisabledPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;
  void LimitSwitchReset();
  void DefaultSolonoidState();

private:

  const double debounce = 0.5; // Seconds
  double lastPressedTime = -debounce;
  team2655::AutoManager autoManager;
  std::unique_ptr<frc::CommandGroup> autoCommandPtr = std::unique_ptr<frc::CommandGroup>(nullptr);
  int previousPovValue = -1;
  bool wasPressed = false;

  frc::Compressor compressor{0};
};
