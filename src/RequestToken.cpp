#include "../inc/RequestToken.h"


RequestToken::RequestToken(RequestType reqType, const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp) :
	aircraftID(acId), runwayID(rwId), parkingStandID(psId), expirationTime(RequestToken::makeExpiration(secsTillExp))
{}


std::unique_ptr<RequestToken> RequestToken::buildLandingRequestToken(const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned secsTillExp)
{
	return std::unique_ptr<RequestToken>(new RequestToken(RequestType::LANDING, acId, rwId, psId, secsTillExp));
}


std::unique_ptr<RequestToken> RequestToken::buildTakeOffRequestToken(const std::string& acId, const std::string& rwId, const unsigned secsTillExp)
{
	return std::unique_ptr<RequestToken>(new RequestToken(RequestType::TAKEOFF, acId, rwId, "", secsTillExp));

}

// TODO make expiration a time point member var
const uint64_t RequestToken::makeExpiration(const unsigned secsTillExp)
{
	auto expiration = std::chrono::steady_clock::now() + std::chrono::seconds(secsTillExp);

	return expiration.time_since_epoch().count();
}

const bool RequestToken::tokenExpired(const uint64_t expirationTime)
{
	auto now = std::chrono::steady_clock::now().time_since_epoch().count();
	return now >= expirationTime;
}
















//const std::chrono::time_point<std::chrono::steady_clock> RequestToken::makeExpiration(const unsigned secs)
//{
//	return std::chrono::steady_clock::now() + std::chrono::seconds(secs);
//}
//
//const bool RequestToken::tokenExpired(const std::chrono::time_point<std::chrono::steady_clock> expirationTime)
//{
//	return std::chrono::steady_clock::now() >= expirationTime;
//}
//
//
//RequestToken::LandingRequestToken::LandingRequestToken(const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned expirationTime) :
//	aircraftID(acId), runwayID(rwId), parkingStandID(psId), expirationTime(RequestToken::makeExpiration(expirationTime))
//{}
//
//std::unique_ptr<RequestToken::LandingRequestToken> RequestToken::LandingRequestToken::build(const std::string& acId, const std::string& rwId, const std::string& psId, const unsigned expirationTime)
//{
//	return std::unique_ptr<LandingRequestToken>(new LandingRequestToken(acId, rwId, psId, expirationTime));
//}
//
//
//RequestToken::TakeOffRequestToken::TakeOffRequestToken(const std::string& acId, const std::string& rwId, const unsigned expirationTime) :
//	aircraftID(acId), runwayID(rwId), expirationTime(RequestToken::makeExpiration(expirationTime))
//{}
//
//std::unique_ptr<RequestToken::TakeOffRequestToken> RequestToken::TakeOffRequestToken::build(const std::string& acId, const std::string& rwId, const unsigned expirationTime)
//{
//	return std::unique_ptr<TakeOffRequestToken>(new TakeOffRequestToken(acId, rwId, expirationTime));
//}





