#include "../inc/ParkingStand.h"

ParkingStand::ParkingStand(const std::string& id) : ID(id), state(ParkingStandState::AVAILABLE)
{};
