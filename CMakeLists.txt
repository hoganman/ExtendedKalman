cmake_minimum_required(VERSION 3.15)
project(ExtendedKalman)

set(CMAKE_CXX_STANDARD 17)

add_executable(ExtendedKalman main.cpp RungeKuttaO2.cpp RungeKuttaO2.h Vector2.cpp Vector2.h GravityWellPotential.cpp GravityWellPotential.h)