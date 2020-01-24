//
// Created by mhogan on 1/18/20.
//

#include <iostream>
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
T GravityWellPotentialXPos<T>::UpdateFCN(const RocketState<T> &State) {

    return State.GetVelocity().X;

}

template<class T>
bool
GravityWellPotentialXPos<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {

    RocketState<T> dummy(State);
    T k1 = this->TimeStep * UpdateFCN(dummy);
    dummy.Position.X += 0.5 * k1;
    dummy.Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(dummy);
    UpdatedState->Position.X += k2;
    return true;
}


template<class T>
T GravityWellPotentialXVel<T>::UpdateFCN(const RocketState<T> &State) {

    using namespace PhysicalConstants;
    Vector2<T> RMoon(0.0,kMoonSemiMajorAxis);
    Vector2<T> Prev_Position = State.GetPosition();
    Vector2<T> Delta_R = Prev_Position - RMoon;
    T Acceleration_1 = kGravitation * kMoonMass * Delta_R.X / Delta_R.GetMag(3);
    T Acceleration_2 = kGravitation * kEarthMass * Prev_Position.X / Prev_Position.GetMag(3);
    std::cout << "kGravitation * kMoonMass * Prev_Position.X = " << kGravitation * kMoonMass * Delta_R.X << std::endl;
    std::cout << "Acceleration_2 = " << Acceleration_2 << std::endl;
    T Acceleration = -1.0 * (Acceleration_1 + Acceleration_2);
    return Acceleration;

}

template<class T>
bool
GravityWellPotentialXVel<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {
    RocketState<T> dummy(State);
    T k1 = this->TimeStep * UpdateFCN(dummy);
    std::cout << "k1 = " << k1 << std::endl;
    dummy.Velocity.X += 0.5 * k1;
    dummy.Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(dummy);
    std::cout << "k2 = " << k2 << std::endl;
    UpdatedState->Velocity.X += k2;
    std::cout << State.Velocity.X << " ||| " << UpdatedState->Velocity.X << std::endl;
    return true;
}

template<class T>
T GravityWellPotentialYPos<T>::UpdateFCN(const RocketState<T> &State) {

    return State.GetVelocity().Y;

}

template<class T>
bool
GravityWellPotentialYPos<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {

    RocketState<T> dummy(State);
    T k1 = this->TimeStep * UpdateFCN(dummy);
    dummy.Position.Y += 0.5 * k1;
    dummy.Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(dummy);
    UpdatedState->Position.Y += k2;
    return true;
}

template<class T>
T GravityWellPotentialYVel<T>::UpdateFCN(const RocketState<T> &State) {

    using namespace PhysicalConstants;
    Vector2<T> RMoon(0.0,kMoonSemiMajorAxis);
    Vector2<T> Prev_Position = State.GetPosition();
    Vector2<T> Delta_R = Prev_Position - RMoon;
    T Acceleration_1 = kGravitation * kMoonMass * Delta_R.Y / Delta_R.GetMag(3);
    T Acceleration_2 = kGravitation * kEarthMass * Prev_Position.Y / Prev_Position.GetMag(3);
    T Acceleration = -1 * (Acceleration_1 + Acceleration_2);
    return Acceleration;
}

template<class T>
bool
GravityWellPotentialYVel<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {
    RocketState<T> dummy(State);
    T k1 = this->TimeStep * UpdateFCN(dummy);
    dummy.Velocity.Y += 0.5 * k1;
    dummy.Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(dummy);
    UpdatedState->Velocity.Y += k2;
    return true;
}

template<class T>
RocketUpdateEquations<T>::~RocketUpdateEquations() {

    delete XPosODE;
    delete XVelODE;
    delete YPosODE;
    delete YVelODE;

}

template<class T>
RocketUpdateEquations<T>::RocketUpdateEquations(T DeltaT, RocketState<T> InputState) : UpdateEquations<T>(DeltaT) {

    State = InputState;
    XPosODE = new GravityWellPotentialXPos<T>(DeltaT);
    XVelODE = new GravityWellPotentialXVel<T>(DeltaT);
    YPosODE = new GravityWellPotentialYPos<T>(DeltaT);
    YVelODE = new GravityWellPotentialYVel<T>(DeltaT);

}

template<class T>
RocketInEarthMoonSystem<T>::RocketInEarthMoonSystem(T DeltaT, RocketState<T> rocket) {

    CoupledODEs = RocketUpdateEquations<T>(DeltaT, rocket);

}

template<class T>
bool RocketInEarthMoonSystem<T>::Update() {

    auto* UpdatedState = new RocketState<T>(CoupledODEs.State);
    RocketState<T> InitialState(CoupledODEs.State);

    CoupledODEs.XVelODE->Update(InitialState, UpdatedState);
    //std::cout << InitialState.Velocity.X << " | " << UpdatedState->Velocity.X << std::endl;
    CoupledODEs.YVelODE->Update(InitialState, UpdatedState);
    CoupledODEs.XPosODE->Update(InitialState, UpdatedState);
    CoupledODEs.YPosODE->Update(InitialState, UpdatedState);

    CoupledODEs.State = RocketState<T>(*UpdatedState);
    delete UpdatedState;
    CoupledODEs.State.Time += CoupledODEs.TimeStep;
    return true;
}
