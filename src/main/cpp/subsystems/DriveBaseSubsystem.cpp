#include <subsystems/DriveBaseSubsystem.h>
#include <RobotMap.h>
#include <Robot.h>
#include <commands/DriveJoystickCommand.h>

using IdleMode = rev::CANSparkMax::IdleMode;

//////////////////////////////////////////////////////////////
/// DriveBaseSubsystem
//////////////////////////////////////////////////////////////

DriveBaseSubsystem::DriveBaseSubsystem() : Subsystem("DriveBaseSubsystem") {
  leftSlave.Follow(leftMaster);
  leftSlave2.Follow(leftMaster);
  rightSlave.Follow(rightMaster);
  rightSlave2.Follow(rightMaster);

  leftPID.SetP(1e-4);
  leftPID.SetI(0);
  leftPID.SetD(0);
  leftPID.SetFF(1/LMaxVelocity);
  leftPID.SetIZone(0);
  leftPID.SetOutputRange(-1, 1);

  rightPID.SetP(1e-4);
  rightPID.SetI(0);
  rightPID.SetD(0);
  rightPID.SetFF(1/RMaxVelocity);
  rightPID.SetIZone(0);
  rightPID.SetOutputRange(-1, 1);

  rightMaster.SetInverted(true);

  leftMaster.SetClosedLoopRampRate(DriveRampRate);
  rightMaster.SetClosedLoopRampRate(DriveRampRate);

  leftMaster.BurnFlash();
  rightMaster.BurnFlash();

  rightMaster.SetInverted(true);
  rightSlave.SetInverted(true);
  rightSlave2.SetInverted(true);
}

void DriveBaseSubsystem::InitDefaultCommand() {
	SetDefaultCommand(new DriveJoystickCommand());
}

void DriveBaseSubsystem::drivePercentage(double speed, double rotation){
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	driveTankPercentage(speeds[0], speeds[1]);
}
void DriveBaseSubsystem::driveVelocity(double speed, double rotation) {
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	speeds[0] *= MaxVelocity;
	speeds[1] *= MaxVelocity;
	driveTankVelocity(speeds[0], speeds[1]);
}
void DriveBaseSubsystem::driveTankPercentage(double leftPercentage, double rightPercentage) {
	leftMaster.Set(leftPercentage);
	//leftSlave.Set(leftPercentage);
	//leftSlave2.Set(leftPercentage);

	rightMaster.Set(rightPercentage);
	//rightSlave.Set(rightPercentage);
	//rightSlave2.Set(rightPercentage);
}
void DriveBaseSubsystem::driveTankVelocity(double lVel, double rVel) {
	if (lVel == 0) {
		// If target velocity is 0 do not use PID to get to 0 just cut power (0%)
		leftMaster.Set(0);
	}else {
		// Drive the left side in velocity closed loop mode (set pid reference = setpoint for PID)
		leftPID.SetReference(lVel, rev::ControlType::kVelocity);
	}

	if (rVel == 0) {
		rightMaster.Set(0);
	}
	else {
		rightPID.SetReference(rVel, rev::ControlType::kVelocity);
	}
}
double DriveBaseSubsystem::getLeftPosition() {
	return leftEnc.GetPosition();

}
double DriveBaseSubsystem::getRightPosition() {
	return rightEnc.GetPosition();
}

double DriveBaseSubsystem::getLeftVelocity() {
	return leftEnc.GetVelocity();
}

double DriveBaseSubsystem::getRightVelocity() {
	return rightEnc.GetVelocity();
}

std::array<double, 2> DriveBaseSubsystem::arcadeDrive(double xSpeed, double zRotation) {

	double leftMotorOutput;
	double rightMotorOutput;

	// Prevent -0 from breaking the arcade drive...
	xSpeed += 0.0;
	zRotation += 0.0;

	double maxInput = std::copysign(std::max(std::abs(xSpeed), std::abs(zRotation)), xSpeed);

	if (xSpeed >= 0.0) {
		// First quadrant, else second quadrant
		if (zRotation >= 0.0) {
			leftMotorOutput = maxInput;
			rightMotorOutput = xSpeed - zRotation;
		} else {
			leftMotorOutput = xSpeed + zRotation;
			rightMotorOutput = maxInput;
		}
	} else {
		// Third quadrant, else fourth quadrant
		if (zRotation >= 0.0) {
			leftMotorOutput = xSpeed + zRotation;
			rightMotorOutput = maxInput;
		} else {
			leftMotorOutput = maxInput;
			rightMotorOutput = xSpeed - zRotation;
		}
	}

	return { leftMotorOutput, rightMotorOutput };
}

double DriveBaseSubsystem::getLeftOutputPosition() {
	return getLeftPosition() / GearRatio;
}

double DriveBaseSubsystem::getRightOutputPosition() {
	return getRightPosition() / GearRatio;
}

double DriveBaseSubsystem::getLeftOutputVelocity() {
	return getLeftVelocity() / GearRatio;
}


double DriveBaseSubsystem::getRightOutputVelocity() {
	return getRightVelocity() / GearRatio;
}

double DriveBaseSubsystem::getIMUAngle() {
	return (imu.GetAngleZ()) + imuOffSet;
}

void DriveBaseSubsystem::setCoastMode() {
	leftMaster.SetIdleMode(IdleMode::kCoast);
	leftSlave.SetIdleMode(IdleMode::kCoast);
	leftSlave2.SetIdleMode(IdleMode::kCoast);

	rightMaster.SetIdleMode(IdleMode::kCoast);
	rightSlave.SetIdleMode(IdleMode::kCoast);
	rightSlave2.SetIdleMode(IdleMode::kCoast);
}

void DriveBaseSubsystem::setBrakeMode() {
	leftMaster.SetIdleMode(IdleMode::kBrake);
	leftSlave.SetIdleMode(IdleMode::kBrake);
	leftSlave2.SetIdleMode(IdleMode::kBrake);

	rightMaster.SetIdleMode(IdleMode::kBrake);
	rightSlave.SetIdleMode(IdleMode::kBrake);
	rightSlave2.SetIdleMode(IdleMode::kBrake);
}

void DriveBaseSubsystem::setRampRate(double rampRate) {
	leftMaster.SetClosedLoopRampRate(rampRate);
	rightMaster.SetClosedLoopRampRate(rampRate);
}

void DriveBaseSubsystem::resetEncoders(){
	leftEnc.SetPosition(0);
	rightEnc.SetPosition(0);
}

void DriveBaseSubsystem::resetIMUForward() {
	imuOffSet = 0;
	imu.Reset();
}

void DriveBaseSubsystem::resetIMUReverse() {
	imuOffSet = 180;
	imu.Reset();
}

double DriveBaseSubsystem::getAvgOutputPos(){
	return (getLeftOutputPosition() + getRightOutputPosition()) / 2.0;
}