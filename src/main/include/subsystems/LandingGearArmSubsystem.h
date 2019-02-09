/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once
//set up ballintake system
#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>

class LandingGearArmSubsystem : public frc::Subsystem {
 private:
  rev::CANSparkMax landingGearArmMotor{1, rev::CANSparkMaxLowLevel::MotorType::kBrushless};
  rev::CANEncoder landingGearArmEncoder = landingGearArmMotor.GetEncoder();
  rev::CANPIDController landingGearArmPid = landingGearArmMotor.GetPIDController();

 public:
  LandingGearArmSubsystem();
  void InitDefaultCommand() override;
  void moveLandingArmSpeed(double percentage);
  void moveLandingArmToPosition(double ticks);
  void stopLandingArm();
  double getLandingArmPosition();
  void resetLandingArmPosition();
};
