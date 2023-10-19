
#ifndef AIRCRAFTSIMNEW_RUNWAYMANAGER_H
#define AIRCRAFTSIMNEW_RUNWAYMANAGER_H

#include "Runway.h"
#include <mutex>
#include <unordered_map>

class RunwayManager
{
public:
    RunwayManager(int numRunways);

    const Runway::State readState(const std::string& rwId);
    void setState(const std::string& rwId, Runway::State newSt);
    bool conditionalSetState(const std::string& rwId, Runway::State ifThisSt, Runway::State thenSetSt);

private:
    std::unordered_map<std::string, Runway> rwMap;
    std::unordered_map<std::string, std::unique_ptr<std::mutex>> lockMap;
};


#endif //AIRCRAFTSIMNEW_RUNWAYMANAGER_H
