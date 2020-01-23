//
// Created by mhogan on 1/18/20.
//

#include "GravityWellPotential.h"

template<class T>
RocketState<T>::RocketState(T InitialMass, Vector2<T> InitialPosition, Vector2<T> InitialVelocity, T t0){
    Mass = InitialMass;
    Position = InitialPosition;
    Velocity = InitialVelocity;
    Time = t0;
}


template<class T>
RocketState<T>::RocketState(const RocketState<T>& copy){
    Mass = copy.Mass;
    Position = copy.Position;
    Velocity = copy.Velocity;
    Time = copy.Time;
}

template<class T>
T GravityWellPotentialXVel<T>::UpdateFCN(const RocketState<T> &State) {

    using namespace PhysicalConstants;
    Vector2<double> RMoon(0.0,kMoonSemiMajorAxis);
    Vector2<T> Prev_Position = State.GetPosition();
    T Acceleration_1 = kGravitation * kMoonMass * Prev_Position.X / ((Vector2<T>)(Prev_Position - RMoon)).GetMag(3);
    T Acceleration_2 = kGravitation * kEarthMass / Prev_Position.GetMag(2);
    return Acceleration_1 + Acceleration_2;

}

template<class T>
bool
GravityWellPotentialXVel<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {
    UpdatedState = new RocketState<T>(State);
    T k1 = this->TimeStep * UpdateFCN(State);
    UpdatedState->Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(*UpdatedState);
    UpdatedState->Phi += k2;
    return true;
}


template<class T>
RocketUpdateEquations<T>::RocketUpdateEquations(T DeltaT, RocketState<T> InputState) : UpdateEquations<T>(DeltaT) {

    State = InputState;

    //auto* XPosition = new GravityWellPotentialXPos<T>(DeltaT);
    auto* XVelocity = new GravityWellPotentialXVel<T>(DeltaT);
    //auto* YPosition = new GravityWellPotentialYPos<T>(DeltaT);
    //auto* YVelocity = new GravityWellPotentialYVel<T>(DeltaT);

    //AddEquation(XPosition);
    AddEquation(XVelocity);
    //AddEquation(YPosition);
    //AddEquation(YVelocity);

}
