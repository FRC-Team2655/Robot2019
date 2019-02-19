/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ClimbCommandGroup.h"
#include <commands/DriveTrainBrakeMode.h>
#include <commands/ClimbBallIntakePositionCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/MoveIntakeArmPercentageCommand.h>
#include <commands/MoveIntakeArmTimeCommand.h>
#include <commands/MoveLandingGearTimeCommand.h>
#include <frc/commands/WaitCommand.h>
#include <commands/StopIntakeArmCommand.h>

ClimbCommandGroup::ClimbCommandGroup() {
  AddSequential(new DriveTrainBrakeMode(true));
  AddSequential(new MoveIntakeArmTimeCommand(-0.2, 0.5));
  AddParallel(new MoveIntakeArmPercentageCommand(-0.3));
  AddSequential(new frc::WaitCommand(1));
  AddSequential(new StopIntakeArmCommand());
  AddSequential(new MoveLandingGearTimeCommand(0.5, 1.5));
  //AddParallel(new MoveIntakeArmPercentageCommand(-0.2));
  //AddSequential(new MoveLandingGearTimeCommand(0.5, 999999999999));
}
