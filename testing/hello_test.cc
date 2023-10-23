#include <gtest/gtest.h>
#include "../inc/Airport.h"
#include <vector>
#include <algorithm>
#include <sstream>



//struct RequestTokenTest : testing::Test
//{
//	RequestTokenTest() : mReqToken(nullptr) {};
//	virtual ~RequestTokenTest() {};
//
//	void SetUp(RequestToken::RequestType reqType)
//	{
//		switch (reqType)
//		{
//		case RequestToken::RequestType::LANDING:
//			mReqToken = RequestToken::buildLandingRequestToken()
//		}
//
//	}
//	void TearDown() override
//	{
//		delete mAirport;
//	}
//
//	RequestToken* mReqToken
//};

//std::ostream& operator<<(std::ostream& out, const std::vector<std::string, std::allocator<std::string>>& vec)
//{
//	out << "{";
//
//	if (!vec.empty())
//	{
//		out << vec[0];
//	}
//
//	for (int i = 1; i < vec.size(); i++)
//	{
//		out << ", " << vec[i];
//	}
//
//	out << "}";
//
//	return out;
//}

//class AirportFriend : public Airport
//{
//public:
//	friend class AirportTest;
//	AirportFriend(unsigned numRw, unsigned numPs) : Airport(numRw, numPs) {};
//};

struct AirportTest : testing::Test
{
protected:
	AirportTest() : mAirport(nullptr) {};
	virtual ~AirportTest() {};
	
	void SetUp(unsigned numRw, unsigned numPs) 
	{ 
		mAirport = new Airport(numRw, numPs);
	}
	void TearDown() override 
	{ 
		delete mAirport; 
	}

	Airport* mAirport;
};


//template <class T, class U>
//struct LocationManagerTest : testing::Test
//{
//protected:
//	LocationManagerTest() : mLocManager(nullptr) {};
//	virtual ~LocationManagerTest() {};
//
//	void SetUp() override 
//	{ 
//		mLocManager = new LocationManager<T, U>{}; 
//	}
//	void TearDown() override
//	{ 
//		delete mLocManager; 
//	}
//
//	LocationManager<T, U>* mLocManager;
//};


//TEST_F(AirportTest, validLandingToken)
//{
//	SetUp(1, 1);
//	std::unique_ptr<RequestToken> landingReqToken = mAirport->requestLanding("AIRCRAFT 1");
//	EXPECT_NE(landingReqToken, nullptr);
//}

//TEST_F(AirportTest, eachRunwayHasMatchingMutex)
//{
//	std::ostringstream runwayIds, mutexIds;
//	std::vector<std::string> rwIds;
//
//	for (const auto& locs : mAirport->getRunways()->getLocations())
//	{
//		rwIds.push_back(locs.first);
//	}
//
//	//mutexIds << AirportTest::getKeys<std::unique_ptr<std::mutex>>(mAirport->getRunways()->getMutexes());
//
//	//ASSERT_EQ(runwayIds.str(), mutexIds.str());
//} 

//TEST(ThreadSuite, TestThreadCount)
//{
//	std::vector<std::thread> threads;
//	for (int i = 0; i < 3; i++)
//		threads.push_back(std::thread([]() 
//		{ 
//				std::this_thread::sleep_for(std::chrono::seconds{5});
//				return; 
//	}));
//
//	ASSERT_GE(testing::internal::GetThreadCount(), 1);
//
//	for (auto& t : threads)
//		t.join();
//}


//TEST_F(AirportTest, isTakeOffToken)
//{
//	IsEmpty()
//}

int main(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);



	return RUN_ALL_TESTS();
}