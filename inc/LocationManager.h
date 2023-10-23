#ifndef AIRCRAFTSIMNEW_LOCATIONMANAGER_H
#define AIRCRAFTSIMNEW_LOCATIONMANAGER_H
#include <string>
#include <unordered_map>

/* LocationManager:
   Holds a map of runway or parkingStand objects with another map of mutex pointers
   corresponding to each object
*/

template <class T, class U>
class LocationManager
{
public:

    LocationManager(const std::string& locName, int numLocs);

    const U readState(const std::string& locId);
    void setState(const std::string& locId, U newSt);
    bool conditionalSetState(const std::string& locId, U ifThisSt, U thenSetSt);

    using LocationMap = std::unordered_map<std::string, T>;
    using MutexMap = std::unordered_map<std::string, std::unique_ptr<std::mutex>>;

    LocationMap locations; 
private:
    MutexMap mutexes;
};



template<class T, class U>
inline LocationManager<T, U>::LocationManager(const std::string& locName, int numLocs)
{
    for (int i = 1; i <= numLocs; i++)
    {
        std::string locId = locName + ' ' + std::to_string(i);

        if (locations.count(locId))
            throw std::invalid_argument("ID already exists within Map");

        locations.insert({ locId, T(locId) });
        mutexes.insert({ locId, std::unique_ptr<std::mutex>(new std::mutex) });
    }
}

template<class T, class U>
inline const U LocationManager<T, U>::readState(const std::string& locId)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    return locations.at(locId).state;
}

// write only operation
template<class T, class U>
inline void LocationManager<T, U>::setState(const std::string& locId, U newSt)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    locations.at(locId).state = newSt;
}

// combined read/write operation 
template<class T, class U>
inline bool LocationManager<T, U>::conditionalSetState(const std::string& locId, U ifThisSt, U thenSetSt)
{
    std::lock_guard<std::mutex> lg(*mutexes.at(locId));

    if (locations.at(locId).state == ifThisSt)
    {
        locations.at(locId).state = thenSetSt;
        return true;
    }
    return false;
}

#endif