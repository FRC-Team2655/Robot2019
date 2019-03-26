#pragma once

#include <frc/TimedRobot.h>
#include <frc/commands/Command.h>
#include <frc/Compressor.h>
#include <frc/smartdashboard/SendableChooser.h>

#include <OI.h>
#include <subsystems/DriveBaseSubsystem.h>
#include <subsystems/BallIntakeArmSubsystem.h>
#include <subsystems/BallShooterSubsystem.h>
#include <subsystems/HatchPanelClawSubsystem.h>
#include <team2655/autonomous.hpp>

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

  bool brakeModeOverridePrevious = false;

  frc::SendableChooser<int> autoSelector;

  std::vector<std::string> autoNames = {
    "No Auto",
    "Pos 2 - Front Right",
    "Pos 2 - Front Left",
    "Pos 1 - Left Side",
    "Pos 3 - Right Side",
    "Test Mode (NEVER RUN ON FIELD)"
  };
  std::vector<std::string> autoScripts = {
    "",
    "/auto-scripts/Pos2R.csv",
    "/auto-scripts/Pos2L.csv",
    "/auto-scripts/Pos1L.csv",
    "/auto-scripts/Pos3R.csv",
    "/auto-scripts/Test.csv"
  };

  frc::Compressor compressor{0};
};
