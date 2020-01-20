//
// Created by mhogan on 1/18/20.
//

#include "GravityWellPotential.h"

template<class T>
GravityWellPotential<T>::GravityWellPotential() {
    Mass = 0;
}

template<class T>
GravityWellPotential<T>::GravityWellPotential(T RocketMass) {
    Mass = RocketMass;
}


template<class T>
RocketState<T>::RocketState() : RungeKuttaO2State<T>() {

}

template<class T>
RocketState<T>::RocketState(RungeKuttaO2State<T> State, Vector2<T> RocketDir) : RungeKuttaO2State<T>(State) {

    RocketDirection = RocketDir;

}

template<class T>
RocketState<T>::RocketState(Vector2<T> y0, Vector2<T> yprime0, Vector2<T> RocketDir)
  : RungeKuttaO2State<T>(y0, yprime0){

    RocketDirection = RocketDir;
}

template<class T>
bool GravityWellPotentialXDir<T>::UpdateFCN(const T& TimeStep, const RocketState<T> &State,
                                            RocketState<T>* ReturnState) {

    using namespace PhysicalConstants;
    Vector2<double> RMoon(0,kMoonSemiMajorAxis);
    Vector2<T> Prev_Position = State.GetPosition();
    T Velocity_Update = TimeStep * State.GetVelocity().X;
    //T TimeStep2 = TimeStep * TimeStep2;
    T Acceleration_Update_1 = (kGravitation * kMoonMass * Prev_Position.X) / (Prev_Position - RMoon).GetMag(3);
    T Acceleration_Update_2 = (kGravitation * kEarthMass * Prev_Position.X) / Prev_Position.GetMag(3);

    //Avoid warning for now
    (void*)ReturnState;

}

