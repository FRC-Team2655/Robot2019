#pragma once

#include <frc/commands/Subsystem.h>
#include <RobotMap.h>
#include <rev/CANSparkMax.h>
#include <frc/DigitalInput.h>

class BallIntakeArmSubsystem : public frc::Subsystem {
private:
  rev::CANSparkMax armMotor {IntakeArmMotor, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder armEncoder = armMotor.GetEncoder();
  rev::CANPIDController armPid = armMotor.GetPIDController();
  frc::DigitalInput topLimitSwitch { LimitSwitchID };
  bool atRocketHeight = false;

public:
  BallIntakeArmSubsystem();
  void InitDefaultCommand() override;
  void moveArmSpeed(double percentage);
  void moveToPosition(double ticks);

  bool getAtRocketHeight();
  void setAtRocketHeight(bool atRocketHeight);

  void lockPosition();

  void stopArm();
  double getArmPosition();
  double getArmVelocity();
  void resetPosition();
  bool isTopLimitSwitchPressed();
  void setCoastMode();
  void setBrakeMode();
  double restrictPosition(double displacement);
  double restrictSpeed(double speed);
};
