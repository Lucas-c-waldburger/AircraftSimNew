
#ifndef AIRCRAFTSIMNEW_RUNWAY_H
#define AIRCRAFTSIMNEW_RUNWAY_H
#include <string>

enum class RunwayState
{
    AVAILABLE,
    RESERVED,
    IN_OPERATION
};

class Runway
{
public:
    explicit Runway(const std::string& id);

    std::string ID;
    RunwayState state;
    int length; // implement this



};




#endif 
