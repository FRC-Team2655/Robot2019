#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>
#include <RobotMap.h>

class HatchPanelClawSubsystem : public frc::Subsystem {
private:
  frc::DoubleSolenoid clawSol{ClawSolendoidA, ClawSolendoidB};
  frc::DoubleSolenoid extenderSol{ExtenderSolenoidA, ExtenderSolenoidB};
  
public:
  HatchPanelClawSubsystem();
  void InitDefaultCommand() override;
  void openClaw();
  void closeClaw();
  void extendClaw();
  void retractClaw();
  bool isExtended();
};