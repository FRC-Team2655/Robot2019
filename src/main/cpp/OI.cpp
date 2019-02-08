#include "OI.h"
#include <frc/WPILib.h>

#include <commands/MoveIntakeArmCommand.h>
#include <commands/ResetAllCommand.h>

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  frc::JoystickButton *xBtn = new frc::JoystickButton(js0, 2);
  frc::JoystickButton *optionBtn = new frc::JoystickButton(js0, 10);
  
  xBtn->WhenPressed(new MoveIntakeArmCommand(-0.25));
  optionBtn->WhenPressed(new ResetAllCommand());
}
