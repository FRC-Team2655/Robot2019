#include <DriveBaseSubsystem.h>
#include <Robot.h>

#include <cmath>

DriveBaseSubsystem::DriveBaseSubsystem() : Subsystem("DriveBaseSubsystem") {}
void DriveBaseSubsystem::drivePercentage(double speed, double rotation){
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	Robot::currentRobot->leftMaster.Set(speeds[0]);
	Robot::currentRobot->rightMaster.Set(speeds[1]);
}
void DriveBaseSubsystem::driveVelocity(double speed, double rotation) {
	std::array<double, 2> speeds = arcadeDrive(speed, rotation);
	speeds[0] *= MaxVelocity;
	speeds[1] *= MaxVelocity;
	driveTankVelocity(speeds[0], speeds[1]);
}
void DriveBaseSubsystem::driveTankPercentage(double leftPercentage, double rightPercentage) {
	Robot::currentRobot->leftMaster.Set(leftPercentage);
	Robot::currentRobot->rightMaster.Set(rightPercentage);
}
void DriveBaseSubsystem::driveTankVelocity(double lVel, double rVel) {
	if (lVel == 0) {
		Robot::currentRobot->leftMaster.Set(0);
	}else {
		Robot::currentRobot->leftPID.SetReference(lVel, rev::ControlType::kVelocity);
	}

	std::cout << lVel << std::endl;
	if (rVel == 0) {
		Robot::currentRobot->rightMaster.Set(0);
	}
	else {
		Robot::currentRobot->rightPID.SetReference(rVel, rev::ControlType::kVelocity);
	}
	std::cout << rVel << std::endl;
	std::cout << "------------------------------------" << std::endl;
}
void DriveBaseSubsystem::InitDefaultCommand() {
   
}
double DriveBaseSubsystem::getLeftPosition() {
	return Robot::currentRobot->leftEnc.GetPosition();

}
double DriveBaseSubsystem::getRightPosition() {
	return -1 * Robot::currentRobot->rightEnc.GetPosition();
}

double DriveBaseSubsystem::getLeftVelocity() {
	return Robot::currentRobot->leftEnc.GetVelocity();
}

double DriveBaseSubsystem::getRightVelocity() {
	return -1 * Robot::currentRobot->rightEnc.GetVelocity();
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
	Robot::currentRobot->imu.GetAngleZ();
}