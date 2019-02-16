/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "commands/ResetIntakeArmPosCG.h"
#include <commands/MoveIntakeArmTimeCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetIntakeArmEncoderCommand.h>
#include <Robot.h>

ResetIntakeArmPosCG::ResetIntakeArmPosCG() {
  AddSequential(new MoveIntakeArmTimeCommand(0.1, .25));
  AddSequential(new ResetIntakeArmEncoderCommand());
  AddSequential(new MoveIntakeArmCommand(0));
}
