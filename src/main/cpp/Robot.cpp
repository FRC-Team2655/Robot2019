#include <Robot.h>
#include <frc/Joystick.h>
#include <iostream>
#include <team2655/joystick.hpp>
#include <frc/livewindow/LiveWindow.h>
#include <frc/smartdashboard/SmartDashboard.h>
#include <AutoCommands.h>

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
	rightSlave.SetInverted(true);

	leftPID.SetP(0);
	leftPID.SetI(0);
	leftPID.SetD(0);
	leftPID.SetFF(1.0/LMaxVelocity);
	leftPID.SetIZone(0);
	leftPID.SetOutputRange(-1, 1);

	rightPID.SetP(0);
	rightPID.SetI(0);
	rightPID.SetD(0);
	rightPID.SetFF(1.0/RMaxVelocity);
	rightPID.SetIZone(0);
	rightPID.SetOutputRange(-1, 1);

	mgr.registerCommand(team2655::CommandCreator<DriveCommand>, "Drive");
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

	mgr.clearCommands();
	mgr.addCommand("Drive", { "0.5", "1" });
}

void Robot::AutonomousPeriodic() {
	mgr.process();
}

void Robot::TeleopInit() {
	leftMaster.SetIdleMode(IdleMode::kCoast);
	leftSlave.SetIdleMode(IdleMode::kCoast);

	rightMaster.SetIdleMode(IdleMode::kCoast);
	rightMaster.SetIdleMode(IdleMode::kCoast);

	//compressor.SetClosedLoopControl(false);
	//compressor.SetClosedLoopControl(true);

}

void Robot::TeleopPeriodic() {


	double power = -1 * jshelper::getAxisValue(driveAxisConfig, js0.GetRawAxis(1));
	double rotate = .5 * jshelper::getAxisValue(rotateAxisConfig, js0.GetRawAxis(2));
	// driveBase.drivePercentage(power, rotate);
	driveBase.driveVelocity(power, rotate);
}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
