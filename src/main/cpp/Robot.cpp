#include "Robot.h"

#include <frc/commands/Scheduler.h>
#include <frc/smartdashboard/SmartDashboard.h>

#include <team2655/autonomous.hpp>
#include <commands/ExecutePathCommand.h>
#include <commands/MoveIntakeArmCommand.h>

#include <commands/ResetIntakeArmPosCG.h>
#include <commands/WaitAutoCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/UnlockClawCommand.h>
#include <commands/RunPlaceHatchCommand.h>
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/DrivePercentageTimeCommand.h>
#include <commands/ClawExtendCommand.h>
#include <commands/DriveDistanceCommand.h>
#include <commands/ResetIMUCommand.h>
#include <commands/JoystickBallIntakeDriveCommand.h>

#include <ctime>

#define DisableBrakeKey "Disable Brake Mode"

OI Robot::oi;
DriveBaseSubsystem Robot::driveBase;
BallIntakeArmSubsystem Robot::ballIntakeArm;
BallShooterSubsystem Robot::ballShooter;
HatchPanelClawSubsystem Robot::hatchPanelClaw;
bool Robot::hasEverResetBallIntakeArm = false;

std::vector<AutoOption> Robot::autoOptions{
  {"No Auto", ""},
  {"Pos1 - Left CS 1", "/auto-scripts/Pos1-LeftCS1.csv"},
  {"Pos1 - Front Left CS", "/auto-scripts/Pos1-FrontLeftCS.csv"},
  {"Pos1 - Rocket", "/auto-scripts/Pos1-Rocket.csv"},
  {"Pos2 - Front Left CS", "/auto-scripts/Pos2-FrontLeftCS.csv"},
  {"Pos2 - Front Right CS", "/auto-scripts/Pos2-FrontRightCS.csv"},
  {"Pos3 - Right CS 1", "/auto-scripts/Pos3-RightCS1.csv"},
  {"Pos3 - Front Right CS", "/auto-scripts/Pos3-FrontRightCS.csv"},
  {"Pos3 - Rocket", "/auto-scripts/Pos3-Rocket.csv"},
  {"Test Mode - DO NOT RUN ON FIELD", "/auto-scripts/Test.csv"}
};

void Robot::RobotInit() {
    // Register auto commands
    autoManager.registerCommand(team2655::CommandCreator<ExecutePathCommand>, false, "PATH");
    autoManager.registerCommand(team2655::CommandCreator<WaitAutoCommand>, false, "WAIT");
    autoManager.registerCommand(team2655::CommandCreator<CloseClawCommand>, false, std::vector<std::string>{"OPEN_CLAW", "CLOSE_CLAW"});
    autoManager.registerCommand(team2655::CommandCreator<ClawExtendCommand>, false, std::vector<std::string>{"EXTEND_CLAW", "RETRACT_CLAW"});
    autoManager.registerCommand(team2655::CommandCreator<DriveDistanceCommand>, false, "DRIVE");
    autoManager.registerCommand(team2655::CommandCreator<ResetIMUCommand>, false, std::vector<std::string>{"RESET_FORWARD", "RESET_REVERSE"});

    frc::SmartDashboard::PutBoolean(DisableBrakeKey, brakeModeOverridePrevious);

    for(size_t i = 0; i < autoOptions.size(); ++i){
        autoSelector.AddOption(autoOptions[i].displayName, i);
    }
    autoSelector.SetDefaultOption(autoOptions[0].displayName, 0);
}

void Robot::RobotPeriodic() {
    frc::SmartDashboard::PutNumber(LeftVelocity, driveBase.getLeftVelocity());
    frc::SmartDashboard::PutNumber(RightVelocity, driveBase.getRightVelocity());
    frc::SmartDashboard::PutNumber(ArmPosition, ballIntakeArm.getArmPosition());
    frc::SmartDashboard::PutBoolean("LimitSwitchPressed", ballIntakeArm.isTopLimitSwitchPressed());
    frc::SmartDashboard::PutNumber("Intake Arm Vecolity: ", ballIntakeArm.getArmVelocity());
    frc::SmartDashboard::PutNumber("IMU Angle: ", driveBase.getIMUAngle());
    frc::SmartDashboard::PutData("Auto Routine", &autoSelector);
}

void Robot::DisabledInit() {
    bool overrideBrake = frc::SmartDashboard::GetBoolean(DisableBrakeKey, false);
    if (!overrideBrake) {
        driveBase.setBrakeMode();
    }else{
        driveBase.setCoastMode();
    }
    
    ballIntakeArm.setBrakeMode();
}

void Robot::DisabledPeriodic() { 
    bool overrideBrake = frc::SmartDashboard::GetBoolean(DisableBrakeKey, false);
    if(overrideBrake != brakeModeOverridePrevious){
        if (!overrideBrake) {
            driveBase.setBrakeMode();
        }else{
            driveBase.setCoastMode();
        }
    }

    brakeModeOverridePrevious = overrideBrake;
    
    frc::Scheduler::GetInstance()->Run(); 
}

void Robot::AutonomousInit() {

    compressor.SetClosedLoopControl(false);
    compressor.SetClosedLoopControl(true);

    wasPressed = false; // Make sure lock will reengage if limit switch is held when enabled
    DefaultSolonoidState();
    driveBase.setBrakeMode();
    ballIntakeArm.setCoastMode();

    autoManager.clearCommands();
    std::string scriptName = autoOptions[autoSelector.GetSelected()].scriptName;
    if(scriptName != ""){
        autoManager.loadScript(scriptName);
        autoCommandPtr = autoManager.getScriptCommand();
        autoCommandPtr.get()->Start();
    }
}

void Robot::intakeOverride(){
    int dpad = oi.js0->GetPOV();
    if(!ballIntakeArm.isTopLimitSwitchPressed() && ((dpad == 0 || dpad == 45 || dpad == 315) && !(previousDpad != 0 || previousDpad == 45 || previousDpad == 315))){
        frc::Command *cmd = new JoystickBallIntakeDriveCommand();
        cmd->Start();
    }
    previousDpad = dpad;
}

void Robot::AutonomousPeriodic() { 
    // Giant button kills auto
    if(oi.js0->GetRawButton(14) && autoCommandPtr.get() != nullptr)
        autoCommandPtr->Cancel();
    LimitSwitchReset();
    intakeOverride();
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

    intakeOverride();

    int value = oi.js0->GetPOV();

    /*if (value == 0 && slowIntakeCmd == nullptr) {
        slowIntakeCmd = new MoveShooterWheelsCommand(0.2, false);
        slowIntakeCmd->Start();

    }else if (slowIntakeCmd != nullptr){
        slowIntakeCmd->Cancel();
        slowIntakeCmd = nullptr;
    }*/
}

void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif

void Robot::LimitSwitchReset(){
    bool isPressed = ballIntakeArm.isTopLimitSwitchPressed();
    double now = time(NULL);
    if (isPressed && !wasPressed) {
        hasEverResetBallIntakeArm = true;
        frc::Command *cmd = new ResetIntakeArmPosCG();
        cmd->Start();
    }

    // Debounced wasPressed
    if(isPressed){
        lastPressedTime = now;
        wasPressed = true;
    }
    if(now - lastPressedTime >= debounce){
        wasPressed = false; // Only set if not pressed for debounce time
    }
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