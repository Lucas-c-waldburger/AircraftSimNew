
#ifndef AIRCRAFTSIMNEW_RUNWAY_H
#define AIRCRAFTSIMNEW_RUNWAY_H
#include <iostream>

class Runway
{
public:
    enum State
    {
        AVAILABLE,
        RESERVED,
        IN_OPERATION
    };

    explicit Runway(const std::string& id);

    std::string ID;
    State state;
};


#endif //AIRCRAFTSIMNEW_RUNWAY_H
