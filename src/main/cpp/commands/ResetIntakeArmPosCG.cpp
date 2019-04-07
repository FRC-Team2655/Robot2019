#include "commands/ResetIntakeArmPosCG.h"
#include <commands/ResetIntakeArmEncoderCommand.h>
#include <commands/LockBallIntakeArmCommand.h>
#include <commands/MoveIntakeArmPercentageCmd.h>

ResetIntakeArmPosCG::ResetIntakeArmPosCG() {
  AddSequential(new ResetIntakeArmEncoderCommand());
  AddSequential(new MoveIntakeArmPercentageCmd(0.1, 0.1));
  AddSequential(new LockBallIntakeArmCommand());
}
