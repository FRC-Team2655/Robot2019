#pragma once

#include <frc/commands/Subsystem.h>
#include <frc/DoubleSolenoid.h>
#include <RobotMap.h>

class HatchPanelClawSubsystem : public frc::Subsystem {
private:
  frc::DoubleSolenoid clawSol{ClawSolenoidA, ClawSolenoidB};
  frc::DoubleSolenoid extenderSol{ExtenderSolenoidA, ExtenderSolenoidB};
  frc::DoubleSolenoid lockSolenoid{ClawLockSolenoidA, ClawLockSolenoidB};
  
public:
  HatchPanelClawSubsystem();
  void InitDefaultCommand() override;
  void openClaw();
  void closeClaw();
  void extendClaw();
  void retractClaw();
  bool isExtended();
  void lock();
  void unlock();
};