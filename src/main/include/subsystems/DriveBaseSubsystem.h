#pragma once

#include <frc/commands/Subsystem.h>
#include <rev/CANSparkMax.h>
#include <adi/ADIS16470_IMU.h>
#include <RobotMap.h>
#include <frc/PIDController.h>

#include <frc/PIDController.h>
#include <frc/PIDSource.h>
#include <frc/PIDOutput.h>

class RotatePIDSource : public frc::PIDSource{
  double PIDGet() override;
};

class RotatePIDOutput : public frc::PIDOutput{
  void PIDWrite(double output) override;
};

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

  /**
   * Drive in velocity mode (arcade drive style)
   * @param speed Speed to drive (power)
   * @param rotation Percent rotation
   */ 
  void driveVelocity(double speed, double rotation);

  /**
   * Drive in velocity mode not using arcade drive.
   * @param lVel The velocity for the left side.
   * @param rVel The velocity for the right side.
   */
  void driveTankVelocity(double lVel, double rVel);

  /**
   * Drive in percentage mode not using arcade drive.
   * @param leftPercentage The percentage to drive the left side.
   * @param rightPercentage The percentage to drive the right side.
   */ 
  void driveTankPercentage(double leftPercentage, double rightPercentage);

  // These get the position/velocity from the hall effect sensor (motor revolutions)
  double getLeftPosition();
  double getRightPosition();
  double getLeftVelocity();
  double getRightVelocity();

  // These get the position/velocity from the hall effect sensor in output (wheel) revolutions
  // Applies correction using Gear box ratio specified in RobotMap.h
  double getLeftOutputPosition();
  double getRightOutputPosition();
  double getLeftOutputVelocity();
  double getRightOutputVelocity();

  // Gets the IMU angle.
  double getIMUAngle();

  // Setting coast mode for the motors.
  void setCoastMode();

  // Setting brake mode for the motors.
  void setBrakeMode();

  void resetEncoders();

  void resetIMUForward();
  void resetIMUReverse();

  double getAvgOutputPos();

  void enableRotatePID(double setpoint);
  void disableRotatePID();

  void setRampRate(double rampRate);

private:
  double imuOffSet = 0;

  rev::CANSparkMax leftMaster {LMaster, MotorType::kBrushless};
  rev::CANSparkMax leftSlave {LSlave, MotorType::kBrushless};
  rev::CANSparkMax leftSlave2 {LSlave2, MotorType::kBrushless};
  rev::CANSparkMax rightMaster {RMaster, MotorType::kBrushless};
  rev::CANSparkMax rightSlave {RSlave, MotorType::kBrushless};
  rev::CANSparkMax rightSlave2 {RSlave2, MotorType::kBrushless};

  // When getting encoders/pid controllers from SPARK MAXs the function instantiates a new object.
  //    Make sure to store the object instead of using GetEncoder/GetPIDController each time

  rev::CANEncoder leftEnc = leftMaster.GetEncoder();
  rev::CANEncoder rightEnc = rightMaster.GetEncoder();

  rev::CANPIDController leftPID = leftMaster.GetPIDController();
  rev::CANPIDController rightPID = rightMaster.GetPIDController();
  
  frc::ADIS16470_IMU imu;

  frc::PIDController rotatePIDController {.007, 0.000000005, 0.000000016, new RotatePIDSource(), new RotatePIDOutput(), 0.01};

  std::array<double, 2> arcadeDrive(double xSpeed, double zRotation);
};