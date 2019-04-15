#pragma once

#include <networktables/NetworkTableInstance.h>
#include <networktables/NetworkTable.h>

#include <memory>
#include <functional>

class VisionManager {
public:
    VisionManager(std::function<double()> getAngleFunc = nullptr);

    /**
     * Set the function used to get the robot's current angle
     * @param getAngleFunc The function (std::function) to get the robot's angle
     */
    void setGetAngleFunc(std::function<double()> getAngleFunc);

    /**
     * Enable tape target detection
     */
    void enableTape();

    /**
     * Enable driver only mode (disable all detection and just allow streaming)
     */
    void enableDriverOnly();

    /**
     * Check if the tape was detected during the last call to update
     * @return True/False - Was tape detected
     */
    bool isTapeDetected();

    /**
     * Get the heading from the current position to the tape (heading error)
     * @returns The angle between the front of the robot and the tape
     */
    double getRelativeTapeHeading();

    /**
     * Get the heading of the tape relative to the current heading of the robot as reported by the gyro
     * @returns The gyro angle for facing the tape
     */
    double getAbsoluteTapeHeading();

private:
    // Vision mode settings
    bool driverVisionOnly = false;
    bool tapeVision = true;

    // Network tables
    nt::NetworkTableInstance ntInstance;
    std::shared_ptr<nt::NetworkTable> chickenVisionTable;
    nt::NetworkTableEntry tapeDetectedEntry, tapeYawEntry, videoTimestampEntry, driveWantedEntry, tapeWantedEntry;

    std::function<double()> getAngleFunc;
};
