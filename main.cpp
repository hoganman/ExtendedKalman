#include <iostream>
#include "GravityWellPotential.h"
#include "Vector2.h"


int main() {
    std::cout << "Hello, World!" << std::endl;

    double TimeStep = 10.0; //seconds
    double InitialMass = 1E5;
    const double N_STEPS = 100.0 / TimeStep;
    Vector2<double> InitialPosition(PhysicalConstants::kEarthRadius/sqrt(2.), PhysicalConstants::kEarthRadius/sqrt(2.));
    Vector2<double> InitialVelocity(1000.0, 0.0);
    auto* RocketInitialState = new RocketState<double>(InitialMass, InitialPosition, InitialVelocity);
    auto* RocketInOrbit = new RocketInEarthMoonSystem<double>(TimeStep, *RocketInitialState);
    std::cout <<  "X (m) | Y (m)" <<  std::endl;
    for(int step = 0; step < N_STEPS; ++step)
    {
        RocketInOrbit->Update();
        std::cout << RocketInOrbit->GetState().Position.X/PhysicalConstants::kEarthRadius
                  << " | " <<  RocketInOrbit->GetState().Position.Y/PhysicalConstants::kEarthRadius << std::endl;
    }

    return 0;
}
