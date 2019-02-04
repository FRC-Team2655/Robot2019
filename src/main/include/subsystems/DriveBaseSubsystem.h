#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <adi/ADIS16470_IMU.h>

using MotorType = rev::CANSparkMax::MotorType;


class DriveBaseSubsystem : public frc::Subsystem {
public:
  DriveBaseSubsystem();
  void InitDefaultCommand() override;

  /**
   * Drive in percentage mode (arcade drive style)
   * @param speed speed to drive (power)
   * @param rotation Percent rotation
   */
  void drivePercentage(double speed, double rotation);
  void driveVelocity(double speed, double rotation);
  void driveTankVelocity(double lVel, double rVel);
  void driveTankPercentage(double leftPercentage, double rightPercentage);


  double getLeftPosition();
  double getRightPosition();
  double getLeftVelocity();
  double getRightVelocity();

  double getLeftOutputPosition();
  double getRightOutputPosition();
  double getLeftOutputVelocity();
  double getRightOutputVelocity();

  double getIMUAngle();

  void setCoastMode();
  void setBrakeMode();

private:
  rev::CANSparkMax leftMaster {1, MotorType::kBrushless};
  rev::CANSparkMax leftSlave {2, MotorType::kBrushless};

  rev::CANSparkMax rightMaster {3, MotorType::kBrushless};
  rev::CANSparkMax rightSlave {4, MotorType::kBrushless};

  rev::CANEncoder leftEnc = leftMaster.GetEncoder();
  rev::CANEncoder rightEnc = rightMaster.GetEncoder();

  rev::CANPIDController leftPID = leftMaster.GetPIDController();
  rev::CANPIDController rightPID = rightMaster.GetPIDController();

  frc::ADIS16470_IMU imu;

  std::array<double, 2> arcadeDrive(double xSpeed, double zRotation);
};