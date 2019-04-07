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

  void intakeOverride();

private:

  const double debounce = 0.5; // Seconds
  double lastPressedTime = -debounce;
  team2655::AutoManager autoManager;
  std::unique_ptr<frc::CommandGroup> autoCommandPtr = std::unique_ptr<frc::CommandGroup>(nullptr);
  int previousPovValue = -1;
  bool wasPressed = false;

  bool brakeModeOverridePrevious = false;

  int previousDpad = -1;

  frc::SendableChooser<int> autoSelector;

  std::vector<std::string> autoNames = {
    "No Auto",
    "Pos 2 - Front Right Cargo Ship",
    "Pos 2 - Front Left Cargo Ship",
    "Pos 1 - Left Side Cargo Ship",
    "Pos 1 - Rocket",
    "Pos 3 - Right Side Cargo Ship",
    "Pos 3 - Rocket",
    "Pos 3 Lvl 2 - Right Side Cargo Ship",
    "Pos 3 Lvl 2 - Rocket",
    "Pos 1 Lvl 2 - Left Side Cargo Ship",
    "Pos 1 Lvl 2 - Rocket",
    "Test Mode (NEVER RUN ON FIELD)",
    "THIS ONE"
  };
  std::vector<std::string> autoScripts = {
    "",
    "/auto-scripts/Pos2R-CS.csv",
    "/auto-scripts/Pos2L-CS.csv",
    "/auto-scripts/Pos1L-CS.csv",
    "/auto-scripts/Pos1L-R.csv",
    "/auto-scripts/Pos3R-CS.csv",
    "/auto-scripts/Pos3R-R.csv",
    "/auto-scripts/Pos3R-CS-L2.csv",
    "/auto-scripts/Pos3R-R-L2.csv",
    "/auto-scripts/Pos1L-CS-L2.csv",
    "/auto-scripts/Pos1L-R-L2.csv",
    "/auto-scripts/Test.csv",
    "/auto-scripts/Elim.csv"
  };

  frc::Compressor compressor{0};
};
