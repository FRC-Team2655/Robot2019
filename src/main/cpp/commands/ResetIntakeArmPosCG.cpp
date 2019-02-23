#include "commands/ResetIntakeArmPosCG.h"
#include <commands/MoveIntakeArmTimeCommand.h>
#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetIntakeArmEncoderCommand.h>
#include <Robot.h>

ResetIntakeArmPosCG::ResetIntakeArmPosCG() {
  //AddSequential(new MoveIntakeArmTimeCommand(0.1, .25));
  AddSequential(new ResetIntakeArmEncoderCommand());
  AddSequential(new MoveIntakeArmCommand(0));
}
