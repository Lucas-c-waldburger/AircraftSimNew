cmake_minimum_required(VERSION 3.24)
project(AircraftSimNew)

set(CMAKE_CXX_STANDARD 11)

add_executable(AircraftSimNew main.cpp RunwayManager.cpp RunwayManager.h Runway.cpp Runway.h Airport.cpp Airport.h)
