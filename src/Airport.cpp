#include "../inc/Airport.h"


Airport::Airport(unsigned numberOfRunways, unsigned numberOfParkingStands) : 
	runways(new Airport::RunwayManager("RUNWAY", numberOfRunways)), 
	parkingStands(new Airport::ParkingStandsManager("PARKING STAND", numberOfParkingStands))
{}


std::unique_ptr<RequestToken> Airport::requestLanding(const std::string& aircraftID)
{
	std::unique_ptr<RequestToken> lrt;
	std::string reservedRunwayID, reservedParkingStandID;

	for (const auto& rw : runways->locations)
	{
		if (runways->conditionalSetState(rw.first, RunwayState::AVAILABLE, RunwayState::RESERVED))
		{
			reservedRunwayID = rw.first;
			break;
		}
	}

	if (!reservedRunwayID.empty()) // we know that an available runway was found and reserved
	{
		for (const auto& ps : parkingStands->locations)
		{
			if (parkingStands->conditionalSetState(ps.first, ParkingStandState::AVAILABLE, ParkingStandState::RESERVED))
			{
				reservedParkingStandID = ps.first;
				break;
			}
		}

		if (!reservedParkingStandID.empty()) // both runway and parkingStand successfully reserved
		{
			lrt = RequestToken::buildLandingRequestToken(aircraftID, reservedRunwayID, reservedParkingStandID, kTokenExpirationTimeSec);
		}

		else // available ParkingStand not found, make the reserved runway available again
		{
			runways->setState(reservedRunwayID, RunwayState::AVAILABLE);
		}
	}

	return lrt; // will either return a temporarily valid landingRequestToken, or a nullptr if resources were not available

}

// if perform returns nullptr, check the error code and log it
// else join the timer thread
std::unique_ptr<std::thread> Airport::performLanding(const RequestToken& lrt)
{
	// TODO change to early return
	bool freeResources = false;

	if (RequestToken::tokenExpired(lrt.expirationTime))
	{
		freeResources = true;
	}

	else if (!runways->conditionalSetState(lrt.runwayID, RunwayState::RESERVED, RunwayState::IN_OPERATION)) // attempt to set runway to inOperation, checks if properly reserved first
	{
		freeResources = true;
	}

	if (freeResources)
	{
		runways->setState(lrt.runwayID, RunwayState::AVAILABLE);
		parkingStands->setState(lrt.parkingStandID, ParkingStandState::AVAILABLE);

		return nullptr;
	}

	return std::unique_ptr<std::thread>(new std::thread(&Airport::setLandingOpTimer, this, lrt.runwayID, lrt.parkingStandID));

}

std::unique_ptr<RequestToken> Airport::requestTakeOff(const std::string& aircraftID)
{
	std::unique_ptr<RequestToken> tort;
	std::string reservedRunwayID;

	for (auto& rw : runways->locations)
	{
		if (runways->conditionalSetState(rw.first, RunwayState::AVAILABLE, RunwayState::RESERVED))
		{
			reservedRunwayID = rw.first;
			break;
		}
	}

	if (!reservedRunwayID.empty()) // we know that an available runway was found and reserved
	{
		tort = RequestToken::buildTakeOffRequestToken(aircraftID, reservedRunwayID, kTokenExpirationTimeSec);
	}

	return tort; // will either return a temporarily valid takeOffRequestToken, or a nullptr if runway was not available

}

// at this point, runway is RESERVED
std::unique_ptr<std::thread> Airport::performTakeOff(const RequestToken& tort)
{
	if (RequestToken::tokenExpired(tort.expirationTime))
	{
		//Logger::Log(tort.aircraftID, " had their take off token expire");
		runways->setState(tort.runwayID, RunwayState::AVAILABLE);
		return nullptr;
	}

	// attempt to set runway to inOperation & parkingStand to Available
	if (runways->conditionalSetState(tort.runwayID, RunwayState::RESERVED, RunwayState::IN_OPERATION))
	{
		if (parkingStands->conditionalSetState(tort.parkingStandID, ParkingStandState::OCCUPIED, ParkingStandState::AVAILABLE))
		{
			return std::unique_ptr<std::thread>(new std::thread(&Airport::setTakeOffOpTimer, this, tort.runwayID));
		}

		else
		{
			runways->setState(tort.runwayID, RunwayState::AVAILABLE);
			return nullptr;
		}
	}

	return nullptr;
}
 
//const std::unique_ptr<Airport::RunwayManager>& Airport::getRunways() const
//{
//	return runways;
//}
//
//const std::unique_ptr<Airport::ParkingStandsManager>& Airport::getParkingStands() const
//{
//	return parkingStands;
//}


void Airport::setLandingOpTimer(const std::string& runwayID, const std::string& parkingStandID)
{
	std::this_thread::sleep_for(std::chrono::seconds(kOperationDurationSec));

	runways->setState(runwayID, RunwayState::AVAILABLE);
	parkingStands->setState(parkingStandID, ParkingStandState::OCCUPIED);
	Logger::Log("Landing timer for ", runwayID, " & ", parkingStandID, " concluded");
}

void Airport::setTakeOffOpTimer(const std::string& runwayID)
{
	std::this_thread::sleep_for(std::chrono::seconds(kOperationDurationSec));

	runways->setState(runwayID, RunwayState::AVAILABLE);
	Logger::Log("Take Off timer for ", runwayID, " concluded");
}


