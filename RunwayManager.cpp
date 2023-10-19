//
// Created by Lower School Music on 10/19/23.
//

#include "RunwayManager.h"

RunwayManager::RunwayManager(int numRunways)
{
    for (int i = 1; i < numRunways + 1; i++)
    {
        std::string rwId = "RUNWAY " + std::to_string(i);

        if (rwMap.count(rwId))
            throw std::invalid_argument("Runway ID already exists within Map");

        rwMap.insert({ rwId, Runway(rwId) });
        lockMap.insert({ rwId, std::unique_ptr<std::mutex>(new std::mutex) });
    }

}

const Runway::State RunwayManager::readState(const std::string& rwId)
{
    std::lock_guard<std::mutex> lg(*lockMap.at(rwId));

    return rwMap.at(rwId).state;
//    try { rwMap.at(rwId).state; }
//    catch (std::out_of_range& ex) { std::cout << ex.what() << '\n'; }
//    return Runway::State::IN_OPERATION;
}

void RunwayManager::setState(const std::string& rwId, Runway::State newSt)
{
    std::lock_guard<std::mutex> lg(*lockMap.at(rwId));

    rwMap.at(rwId).state = newSt;
}

bool RunwayManager::conditionalSetState(const std::string& rwId, Runway::State ifThisSt, Runway::State thenSetSt)
{
    std::lock_guard<std::mutex> lg(*lockMap.at(rwId));

    if (rwMap.at(rwId).state == ifThisSt)
    {
        rwMap.at(rwId).state = thenSetSt;
        return true;
    }

    return false;
}

