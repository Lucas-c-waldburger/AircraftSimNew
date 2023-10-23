#ifndef AIRCRAFTSIMNEW_AIRPORT_H
#define AIRCRAFTSIMNEW_AIRPORT_H

#include "Runway.h"
#include "ParkingStand.h"
#include "RequestToken.h"
#include "LocationManager.h"
#include <thread>
#include <memory>
#include <vector>



class Airport 
{
public:

	static constexpr const int kOperationDurationSec = 5;
	static constexpr const int kTokenExpirationTimeSec = 2;

	Airport(unsigned numberOfRunways, unsigned numberOfParkingStands);
	
	std::unique_ptr<RequestToken> requestLanding(const std::string& aircraftID);
	std::unique_ptr<std::thread> performLanding(const RequestToken& lrt);
	std::unique_ptr<RequestToken> requestTakeOff(const std::string& aircraftID);
	std::unique_ptr<std::thread> performTakeOff(const RequestToken& tort);

	using RunwayManager = LocationManager<Runway, RunwayState>;
	using ParkingStandsManager = LocationManager<ParkingStand, ParkingStandState>;

private:
	std::unique_ptr<RunwayManager> runways;
	std::unique_ptr<ParkingStandsManager> parkingStands;

	void setLandingOpTimer(const std::string& runwayID, const std::string& parkingStandID);
	void setTakeOffOpTimer(const std::string& runwayID);
};


#endif //AIRCRAFTSIMNEW_AIRPORT_H
