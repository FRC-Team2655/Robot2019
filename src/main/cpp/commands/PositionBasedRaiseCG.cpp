/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/PositionBasedRaiseCG.h"
#include <commands/MoveIntakeArmPercentageCmd.h>
#include <commands/SetAtRocketHeightCommand.h>
#include <commands/PositionBasedRaisedCommand.h>
#include <Robot.h>
#include <RobotMap.h>

PositionBasedRaiseCG::PositionBasedRaiseCG() {
  AddSequential(new PositionBasedRaisedCommand());
  AddSequential(new SetAtRocketHeightCommand(false));
}