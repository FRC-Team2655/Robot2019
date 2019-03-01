#include "commands/ResetIntakeArmPosCG.h"
#include <commands/MoveIntakeArmTimeCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetIntakeArmEncoderCommand.h>
#include <commands/MoveIntakeArmPercentageCommand.h>
#include <Robot.h>
#include <RobotMap.h>

ResetIntakeArmPosCG::ResetIntakeArmPosCG() {
  AddSequential(new MoveIntakeArmTimeCommand(0.1, 0.25));
  AddSequential(new ResetIntakeArmEncoderCommand());
  //AddSequential(new MoveIntakeArmCommand(BallIntakeUpPos));
  AddSequential(new MoveIntakeArmPercentageCommand(-1 * BallIntakeDownDirection * 0.02));
}
