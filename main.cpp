#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <random>
#include <memory>
#include "RunwayManager.h"

int main()
{
    std::vector<std::shared_ptr<std::thread>> tVec;
    RunwayManager rwManager{10};

    for (int i = 0; i < 30; i++)
    {
        tVec.push_back(std::make_shared<std::thread>([&]()
        {
            std::string randID = "RUNWAY " + std::to_string((rand() % 10) + 1) ;
            //std::cout << randID << '\n';
            Runway::State firstSt = rwManager.readState(randID);
            if (firstSt == Runway::State::AVAILABLE)
            {
                std::this_thread::sleep_for(std::chrono::seconds(rand() % 3));

                if ((rand() % 2) == 0)
                {
                    std::string randOtherID = "RUNWAY " + std::to_string((rand() % 10) + 1) ;
                    rwManager.conditionalSetState(randOtherID, Runway::State::AVAILABLE, Runway::State::IN_OPERATION);
                }

                if (rwManager.readState(randID) != firstSt)
                    std::cout << "NOT THE SAME WHEN FIRST READ";

                return;

            }
        }));
    }

    for (auto& t : tVec)
        t->join();

    return 0;
}
