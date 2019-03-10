#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/DriveTimeCommand.h>
#include <commands/ExecutePathCommand.h>
#include <commands/MoveIntakeArmCommand.h>

#include <commands/ResetIntakeArmPosCG.h>
#include <commands/ClimbCommandGroup.h>
#include <commands/WaitAutoCommand.h>
#include <commands/ExtendClawCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/UnlockClawCommand.h>
#include <commands/DriveDistanceCommand.h>

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;
BallIntakeArmSubsystem Robot::ballIntakeArm;
BallShooterSubsystem Robot::ballShooter;
HatchPanelClawSubsystem Robot::hatchPanelClaw;
bool Robot::hasEverResetBallIntakeArm = false;

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<ExecutePathCommand>, false, "PATH");
    autoManager.registerCommand(team2655::CommandCreator<WaitAutoCommand>, false, "WAIT");
    autoManager.registerCommand(team2655::CommandCreator<ExtendClawCommand>, false, "EXTEND_CLAW");
    autoManager.registerCommand(team2655::CommandCreator<ExtendClawCommand>, false, "RETRACT_CLAW");
    autoManager.registerCommand(team2655::CommandCreator<CloseClawCommand>, false, "OPEN_CLAW");
    autoManager.registerCommand(team2655::CommandCreator<CloseClawCommand>, false, "CLOSE_CLAW");
    autoManager.registerCommand(team2655::CommandCreator<UnlockClawCommand>, false, "UNLOCK_CLAW");
    frc::SmartDashboard::PutBoolean("ABCDEFG", false);

    frc::SmartDashboard::PutNumber("P: ", BallIntake_kpDown);
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber(LeftVelocity, driveBase.getLeftVelocity());
    frc::SmartDashboard::PutNumber(RightVelocity, driveBase.getRightVelocity());
    frc::SmartDashboard::PutNumber(ArmPosition, ballIntakeArm.getArmPosition());
    frc::SmartDashboard::PutBoolean("LimitSwitchPressed", ballIntakeArm.isTopLimitSwitchPressed());
    frc::SmartDashboard::PutNumber("Intake Arm Vecolity: ", ballIntakeArm.getArmVelocity());
    frc::SmartDashboard::PutNumber("IMU Angle: ", driveBase.getIMUAngle());
}

void Robot::DisabledInit() {
    driveBase.setBrakeMode(); 
    ballIntakeArm.setBrakeMode();
}

void Robot::DisabledPeriodic() { frc::Scheduler::GetInstance()->Run(); }

void Robot::AutonomousInit() {

    compressor.SetClosedLoopControl(false);
    compressor.SetClosedLoopControl(true);

    driveBase.resetIMUReverse();

    wasPressed = false; // Make sure lock will reengage if limit switch is held when enabled
    DefaultSolonoidState();
    driveBase.setBrakeMode();
    ballIntakeArm.setCoastMode();

    /*autoManager.clearCommands();
    autoManager.loadScript("/auto-scripts/RightFront.csv");
    autoCommandPtr = autoManager.getScriptCommand();
    autoCommandPtr.get()->Start();*/

    frc::Command *cmd = new DriveDistanceCommand(12);
    cmd->Start();
}

void Robot::AutonomousPeriodic() { 
    // Giant button kills auto
    if(oi.js0->GetRawButton(14) && autoCommandPtr.get() != nullptr)
        autoCommandPtr->Cancel();
    LimitSwitchReset();
    frc::Scheduler::GetInstance()->Run(); 
}


void Robot::TeleopInit() {

    if (hatchPanelClaw.isExtended()) {
        hatchPanelClaw.lock();
    }

    wasPressed = false; // Make sure lock will reengage if limit switch is held when enabled
    DefaultSolonoidState();

    driveBase.setCoastMode();
    ballIntakeArm.setCoastMode();

    compressor.SetClosedLoopControl(false);
    compressor.SetClosedLoopControl(true);
}

void Robot::TeleopPeriodic() {

    frc::Scheduler::GetInstance()->Run();
    
    LimitSwitchReset();

    /*if (oi.js0->GetRawAxis(10)) {
        driveBase.setBrakeMode();
    }else{
        driveBase.setCoastMode();
    }*/

    int value = oi.js0->GetPOV();
    if(value == 180 && previousPovValue != 180){
        //frc::Command *cmd = new ClimbCommandGroup();
        //cmd->Start();
    }
    previousPovValue = value;
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

void Robot::LimitSwitchReset(){
    bool isPressed = ballIntakeArm.isTopLimitSwitchPressed();
    if (isPressed && !wasPressed) {
        hasEverResetBallIntakeArm = true;
        frc::Command *cmd = new ResetIntakeArmPosCG();
        cmd->Start();
    }
    wasPressed = isPressed;
}

void Robot::DefaultSolonoidState(){
    static bool hasBeenReset = false;

    if (hasBeenReset) {
        return;
    }

    ballShooter.retractPiston();
    hatchPanelClaw.retractClaw();
    hatchPanelClaw.closeClaw();
    hatchPanelClaw.unlock();
    hasBeenReset = true;
}