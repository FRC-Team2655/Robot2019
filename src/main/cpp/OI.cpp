#include "OI.h"

#include <commands/MoveIntakeArmCommand.h>
#include <commands/CloseClawCommand.h>
#include <commands/MoveShooterWheelsCommand.h>
#include <commands/ToggleClawExtensionCommand.h>
#include <commands/JoystickBallIntakeDriveCommand.h>
#include <commands/SetAtRocketHeightCommand.h>
#include <commands/PositionBasedShootCommand.h>
#include <commands/DropCommandGroup.h>
#include <RobotMap.h>
#include <frc/buttons/JoystickButton.h>
#include <commands/MoveIntakeArmPercentageCmd.h>
#include <commands/RotateCommand.h>

using namespace team2655;

OI::OI() {
  js0 = new frc::Joystick(0);
  frc::JoystickButton *xBtn = new frc::JoystickButton(js0, 2);
  frc::JoystickButton *squareBtn = new frc::JoystickButton(js0, 1);
  frc::JoystickButton *optionBtn = new frc::JoystickButton(js0, 10);
  frc::JoystickButton *r2Btn = new frc::JoystickButton(js0, 8);
  frc::JoystickButton *l1Btn = new frc::JoystickButton(js0, 5);
  frc::JoystickButton *r1Btn = new frc::JoystickButton(js0, 6);
  frc::JoystickButton *triangleBtn = new frc::JoystickButton(js0, 4);
  frc::JoystickButton *circleBtn = new frc::JoystickButton(js0, 3);
  frc::JoystickButton *shareBtn = new frc::JoystickButton(js0, 9);
  frc::JoystickButton *l2Btn = new frc::JoystickButton(js0, 7);

  squareBtn->WhenPressed(new ToggleClawExtensionCommand());
  r2Btn->WhenPressed(new CloseClawCommand(false));
  r2Btn->WhenReleased(new CloseClawCommand(true));
  //optionBtn->WhenPressed(new ResetAllCommand());
  r1Btn->WhileHeld(new MoveShooterWheelsCommand(.4, true));
  l1Btn->WhileHeld(new PositionBasedShootCommand());


  /////////////////////////////////////////////
  /// Ball Intake arm control
  /////////////////////////////////////////////

  //xBtn->WhenPressed(new MoveIntakeArmCommand(BallIntakeUpPos));
  xBtn->WhenPressed(new MoveIntakeArmPercentageCmd(-1 * BallIntakeDownDirection * 0.3, 10));
  l2Btn->WhenPressed(new JoystickBallIntakeDriveCommand());
#if COMPBOT
  triangleBtn->WhenPressed(new MoveIntakeArmCommand(-0.12));
  circleBtn->WhenPressed(new MoveIntakeArmCommand(-0.255));
#else
  triangleBtn->WhenPressed(new MoveIntakeArmCommand(-0.12));
  circleBtn->WhenPressed(new MoveIntakeArmCommand(-0.27));
#endif

  // Track if at rocket height
  triangleBtn->WhenPressed(new SetAtRocketHeightCommand(true));
  circleBtn->WhenPressed(new SetAtRocketHeightCommand(false));
  l2Btn->WhenPressed(new SetAtRocketHeightCommand(false));
  xBtn->WhenPressed(new SetAtRocketHeightCommand(false));

}