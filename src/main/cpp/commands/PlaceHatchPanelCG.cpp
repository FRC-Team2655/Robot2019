#include "commands/PlaceHatchPanelCG.h"
#include <frc/commands/WaitCommand.h>
#include <commands/ClawExtendCommand.h>
#include <commands/DrivePercentageTimeCommand.h>
#include <commands/DirectOpenClawCommand.h>
#include <commands/DirectCloseClawCommand.h>

PlaceHatchPanelCG::PlaceHatchPanelCG() {
  AddSequential(new ClawExtendCommand(true));
  AddSequential(new DrivePercentageTimeCommand(-0.2, 0.5));
  AddSequential(new DirectOpenClawCommand());
  AddSequential(new frc::WaitCommand(2));
  AddSequential(new DrivePercentageTimeCommand(0.2, 0.8));
  AddSequential(new DirectCloseClawCommand());
}