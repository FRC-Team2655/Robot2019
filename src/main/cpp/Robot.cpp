#include <Robot.h>
#include <frc/Joystick.h>
#include <iostream>
#include <team2655/joystick.hpp>

#include <frc/smartdashboard/SmartDashboard.h>

Robot *Robot::currentRobot = NULL;

using namespace team2655;

void Robot::RobotInit() {
  Robot::currentRobot = this;

  driveAxisConfig = jshelper::createAxisConfig(.1, 0, .5);
  rotateAxisConfig = jshelper::createAxisConfig(.1);

  Robot::currentRobot->leftSlave1.Follow(Robot::currentRobot->leftMaster);
  Robot::currentRobot->leftSlave2.Follow(Robot::currentRobot->leftMaster);
  Robot::currentRobot->rightSlave1.Follow(Robot::currentRobot->rightMaster);
  Robot::currentRobot->rightSlave2.Follow(Robot::currentRobot->rightMaster);

  Robot::currentRobot->leftMaster.SetInverted(true);
  Robot::currentRobot->leftSlave1.SetInverted(true);
  Robot::currentRobot->leftSlave2.SetInverted(true);
}

void Robot::TestInit(){
  Robot::currentRobot->leftMaster.SetNeutralMode(NeutralMode::Brake);
  Robot::currentRobot->leftSlave1.SetNeutralMode(NeutralMode::Brake);
  Robot::currentRobot->leftSlave2.SetNeutralMode(NeutralMode::Brake);
  Robot::currentRobot->rightMaster.SetNeutralMode(NeutralMode::Brake);
  Robot::currentRobot->rightSlave1.SetNeutralMode(NeutralMode::Brake);
  Robot::currentRobot->rightSlave2.SetNeutralMode(NeutralMode::Brake);

}

void Robot::RobotPeriodic() {}

void Robot::AutonomousInit() {
  
}

void Robot::AutonomousPeriodic() {
  
}

void Robot::TeleopInit() {
  Robot::currentRobot->leftMaster.SetNeutralMode(NeutralMode::Coast);
  Robot::currentRobot->leftSlave1.SetNeutralMode(NeutralMode::Coast);
  Robot::currentRobot->leftSlave2.SetNeutralMode(NeutralMode::Coast);
  Robot::currentRobot->rightMaster.SetNeutralMode(NeutralMode::Coast);
  Robot::currentRobot->rightSlave1.SetNeutralMode(NeutralMode::Coast);
  Robot::currentRobot->rightSlave2.SetNeutralMode(NeutralMode::Coast);
}

void Robot::TeleopPeriodic() {
  double power = jshelper::getAxisValue(driveAxisConfig, js0.GetRawAxis(1));
  double rotate = -.5 * jshelper::getAxisValue(rotateAxisConfig, js0.GetRawAxis(2));
  driveBase.drivePercentage(power, rotate);
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif
