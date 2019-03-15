#include "commands/ResetIntakeArmPosCG.h"
#include <commands/ResetIntakeArmEncoderCommand.h>
#include <commands/LockBallIntakeArmCommand.h>

ResetIntakeArmPosCG::ResetIntakeArmPosCG() {
  AddSequential(new ResetIntakeArmEncoderCommand());
  AddSequential(new LockBallIntakeArmCommand());
}
