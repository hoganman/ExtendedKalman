#include <iostream>
#include "GravityWellPotential.h"
#include "Vector2.h"


int main() {

    double TimeStep = 0.1 * PhysicalConstants::second;
    double InitialMass = 1E5 * PhysicalConstants::kilogram;
    //Analytical Earth orbit
    const double Position = 410 * PhysicalConstants::kilometer + PhysicalConstants::kEarthRadius;
    const double Velocity = sqrt( PhysicalConstants::kGravitation * PhysicalConstants::kEarthMass / Position);
    const double Period = 2 * 3.14159 * sqrt(pow(Position, 3) / ( PhysicalConstants::kGravitation * (PhysicalConstants::kEarthMass)));
    const double N_STEPS = 2 * PhysicalConstants::second / TimeStep;
    std::cout << "Velocity = " << Velocity << std::endl;
    //ISS Orbit
    //const double Position = 410 * PhysicalConstants::kilometer + PhysicalConstants::kEarthRadius;
    //const double Velocity = 7.66696 * PhysicalConstants::kilometer / PhysicalConstants::second;
    //Low Moon orbit
    //const double Position = PhysicalConstants::kMoonSemiMajorAxis + 114.0832 * PhysicalConstants::kilometer;
    //const double Velocity = 1627.11384 * PhysicalConstants::meter / PhysicalConstants::second;
    //Far earth-moon orbit
    //const double Position = 3 * PhysicalConstants::kMoonSemiMajorAxis + 1E-5;
    //const double Velocity = sqrt( PhysicalConstants::kGravitation * (PhysicalConstants::kMoonMass + PhysicalConstants::kEarthMass) / Position);
    Vector2<double> InitialPosition(Position, 1E-10);
    Vector2<double> InitialVelocity(-1E-10, -Velocity);
    auto* RocketInitialState = new RocketState<double>(InitialMass, InitialPosition, InitialVelocity);
    auto* RocketInOrbit = new RocketInEarthMoonSystem<double>(TimeStep, *RocketInitialState);
    std::cout <<  "X | V_X | Y | V_Y " <<  std::endl;
    for(int step = 0; step < N_STEPS; ++step)
    {
        if(step % 10 == 0) std::cout << RocketInOrbit->GetState().Position.X / Position
                  << " | " << RocketInOrbit->GetState().Velocity.X / Velocity
                  << " | " << RocketInOrbit->GetState().Position.Y / Position
                  << " | " <<  RocketInOrbit->GetState().Velocity.Y / Velocity
                  << std::endl;
        RocketInOrbit->Update();
    }
    return 0;
}
