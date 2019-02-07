#include "OI.h"
#include <frc/WPILib.h>

#include <commands/MoveIntakeArmCommand.h>

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  frc::JoystickButton *xBtn = new frc::JoystickButton(js0, 2);

  xBtn->WhenPressed(new MoveIntakeArmCommand(500));
}
