

#include "Runway.h"

Runway::Runway(const std::string& id) : ID(id), state(Runway::State::AVAILABLE)
{};