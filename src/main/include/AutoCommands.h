#pragma once

#include <team2655/autonomous.hpp>
#include <DriveBaseSubsystem.h>

class DriveCommand : public team2655::AutoCommand{
public:
    void start(std::string cmdName, std::vector<std::string> args) override;
    void process() override;
    void handleComplete() override;
};
