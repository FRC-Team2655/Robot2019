#include <Robot.h>
#include <frc/Joystick.h>
#include <iostream>
#include <team2655/joystick.hpp>
#include <LiveWindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>

using IdleMode = rev::CANSparkMax::IdleMode;

Robot *Robot::currentRobot = NULL;

using namespace team2655;

void Robot::RobotInit() {
  Robot::currentRobot = this;

  driveAxisConfig = jshelper::createAxisConfig(.1, 0, .5);
  rotateAxisConfig = jshelper::createAxisConfig(.1);

  leftSlave.Follow(leftMaster);
  rightSlave.Follow(rightMaster);

  rightMaster.SetInverted(true);

  leftPID.SetP(5e-5);
  leftPID.SetI(1e-6);
  leftPID.SetD(0);
  leftPID.SetFF(0);
  leftPID.SetIZone(0);
  leftPID.SetOutputRange(-1, 1);

  rightPID.SetP(5e-5);
  rightPID.SetI(1e-6);
  rightPID.SetD(0);
  rightPID.SetFF(0);
  rightPID.SetIZone(0);
  rightPID.SetOutputRange(-1, 1);
}

void Robot::RobotPeriodic() {
	frc::SmartDashboard::PutNumber("Right Encoder", driveBase.getRightPosition());
	frc::SmartDashboard::PutNumber("Left Encoder", driveBase.getLeftPosition());
	frc::SmartDashboard::PutNumber("Right Velocity", driveBase.getRightVelocity());
	frc::SmartDashboard::PutNumber("Left Velocity", driveBase.getLeftVelocity());

	frc::SmartDashboard::PutNumber("Left Faults: ", leftMaster.GetFaults());
	frc::SmartDashboard::PutNumber("Right Faults: ", rightMaster.GetFaults());
	frc::SmartDashboard::PutString("Left Error: ", leftMaster.GetError().GetMessage());
	frc::SmartDashboard::PutString("Right Error: ", rightMaster.GetError().GetMessage());
}

void Robot::AutonomousInit() {
	leftStartRevolutions = driveBase.getLeftPosition();

	leftMaster.SetIdleMode(IdleMode::kBrake);
	leftSlave.SetIdleMode(IdleMode::kBrake);

	rightMaster.SetIdleMode(IdleMode::kBrake);
	rightMaster.SetIdleMode(IdleMode::kBrake);
}

void Robot::AutonomousPeriodic() {
	//if (driveBase.getLeftPosition() - leftStartRevolutions < (20 * 12 * 9.47) / (6 * 3.141592)) {
		driveBase.drivePercentage(100, 0.01);
	/*}
	else {
		driveBase.drivePercentage(0, 0);
	}*/
}

void Robot::TeleopInit() {
	leftMaster.SetIdleMode(IdleMode::kCoast);
	leftSlave.SetIdleMode(IdleMode::kCoast);

	rightMaster.SetIdleMode(IdleMode::kCoast);
	rightMaster.SetIdleMode(IdleMode::kCoast);
	
	compressor.SetClosedLoopControl(false);
	compressor.SetClosedLoopControl(true);

}

void Robot::TeleopPeriodic(){
	

  double power = -1 * jshelper::getAxisValue(driveAxisConfig, js0.GetRawAxis(1));
  double rotate = .5 * jshelper::getAxisValue(rotateAxisConfig, js0.GetRawAxis(2));
  // driveBase.drivePercentage(power, rotate);
  driveBase.driveVelocity(power, rotate);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
