#pragma once

// SmartDashboard keys
#define LeftVelocity "LeftVelocity"
#define RightVelocity "RightVelocity"

#define MINVAL(x, y) (((x) > (y)) ? (x) : (y)) // Get the minimum of two values (macro)

#define RMaxVelocity 5800.0 //5950.0      // motor revolutions / min
#define LMaxVelocity 5700.0 //5580.0      
#define GearRatio 9.47 / 1       // 9.47 motor revolutions to 1 output revolution
#define WheelDiameter .1524      // wheel diameter in meters (6")
#define MaxVelocity MINVAL(LMaxVelocity, RMaxVelocity)
#define PathfinderMaxVelocity MaxVelocity / GearRatio / 60 * WheelDiameter * 3.141592

#define LMaster 1
#define LSlave 2
#define RMaster 3
#define RSlave 4