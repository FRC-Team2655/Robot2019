#include <subsystems/DriveBaseSubsystem.h>
#include <RobotMap.h>

#include <commands/DriveJoystickCommand.h>

using IdleMode = rev::CANSparkMax::IdleMode;

DriveBaseSubsystem::DriveBaseSubsystem() : Subsystem("DriveBaseSubsystem") {
  leftSlave.Follow(leftMaster);
  rightSlave.Follow(rightMaster);

  leftMaster.SetInverted(true);

  leftPID.SetP(0.0005);
  leftPID.SetI(0);
  leftPID.SetD(0);
  leftPID.SetFF(1.0/LMaxVelocity);
  leftPID.SetIZone(0);
  leftPID.SetOutputRange(-1, 1);

  rightPID.SetP(0.0005);
  rightPID.SetI(0);
  rightPID.SetD(0);
  rightPID.SetFF(1.0/RMaxVelocity);
  rightPID.SetIZone(0);
  rightPID.SetOutputRange(-1, 1);
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
	rightMaster.Set(rightPercentage);
}
void DriveBaseSubsystem::driveTankVelocity(double lVel, double rVel) {
	if (lVel == 0) {
		leftMaster.Set(0);
	}else {
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
	return -1 * rightEnc.GetPosition();
}

double DriveBaseSubsystem::getLeftVelocity() {
	return leftEnc.GetVelocity();
}

double DriveBaseSubsystem::getRightVelocity() {
	return -1 * rightEnc.GetVelocity();
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
	imu.GetAngleZ();
}

void DriveBaseSubsystem::setCoastMode() {
	leftMaster.SetIdleMode(IdleMode::kCoast);
	leftSlave.SetIdleMode(IdleMode::kCoast);

	rightMaster.SetIdleMode(IdleMode::kCoast);
	rightSlave.SetIdleMode(IdleMode::kCoast);
}

void DriveBaseSubsystem::setBrakeMode() {
	leftMaster.SetIdleMode(IdleMode::kBrake);
	leftSlave.SetIdleMode(IdleMode::kBrake);

	rightMaster.SetIdleMode(IdleMode::kBrake);
	rightSlave.SetIdleMode(IdleMode::kBrake);
}