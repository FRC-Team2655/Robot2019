/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

class LandingGearDriveSubsystem : public frc::Subsystem {
 private:
  rev::CANSparkMax landingGearMotor{1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder landingGearEncoder = landingGearMotor.GetEncoder();
  rev::CANPIDController landingGearPID = landingGearMotor.GetPIDController();

 public:
  LandingGearDriveSubsystem();
  void moveLandingGearSpeed(double percentage);
  void moveLandingGearToPosition(double ticks);
  void stopLandingGear();
  double getLandingGearPosition();
  void resetLandingGearPosition();
  void InitDefaultCommand() override;
  void moveLandingGearSpeed(double speed);
};
