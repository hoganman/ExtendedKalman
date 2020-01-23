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
bool GravityWellPotential<T>::Update(const RocketState<T> &State, RocketState<T> *UpdatedState) {
    (void)State;
    (void*)UpdatedState;
    std::cout << "ERROR: No Update function has been defined!" << std::endl;
    std::cout << "Implement an Update function" << std::endl;
    exit(1);
}

template<class T>
T GravityWellPotential<T>::UpdateFCN(const RocketState<T> &State) {
    (void)State;
    std::cout << "ERROR: No Update function has been defined!" << std::endl;
    std::cout << "Implement an Update function" << std::endl;
    exit(1);
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
    T Acceleration = -1 * (Acceleration_1 + Acceleration_2);
    return Acceleration;

}

template<class T>
bool
GravityWellPotentialXVel<T>::Update(const RocketState<T> &State, RocketState<T>* UpdatedState) {
    RocketState<T> dummy(State);
    T k1 = this->TimeStep * UpdateFCN(dummy);
    dummy.Velocity.X += 0.5 * k1;
    dummy.Time += 0.5 * this->TimeStep;
    T k2 = this->TimeStep * UpdateFCN(dummy);
    UpdatedState->Velocity.X += k2;
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

    for(unsigned int i = 0; i < Equations.size(); ++i){
        if (Equations.at(i))
            delete Equations.at(i);
    }
    Equations.clear();

}

template<class T>
bool RocketUpdateEquations<T>::AddEquation(GravityWellPotential<T>* eqn) {
    if( !eqn )
        return false;
    Equations.push_back(eqn);
    this->NEquation = Equations.size();
    return true;
}

template<class T>
RocketUpdateEquations<T>::RocketUpdateEquations(T DeltaT, RocketState<T> InputState) : UpdateEquations<T>(DeltaT) {

    State = InputState;

    auto* XPosition = new GravityWellPotentialXPos<T>(DeltaT);
    auto* XVelocity = new GravityWellPotentialXVel<T>(DeltaT);
    auto* YPosition = new GravityWellPotentialYPos<T>(DeltaT);
    auto* YVelocity = new GravityWellPotentialYVel<T>(DeltaT);

    AddEquation(XPosition);
    AddEquation(XVelocity);
    AddEquation(YPosition);
    AddEquation(YVelocity);

}

template<class T>
RocketInEarthMoonSystem<T>::RocketInEarthMoonSystem(T DeltaT, RocketState<T> rocket) {

    CoupledODEs = RocketUpdateEquations<T>(DeltaT, rocket);

}

template<class T>
bool RocketInEarthMoonSystem<T>::Update() {

    auto* UpdatedState = new RocketState<T>(CoupledODEs.State);
    for(int index = 0; index < CoupledODEs.NEquations; ++index){
        GravityWellPotential<T>* ode = static_cast< GravityWellPotential<T>* >(CoupledODEs.Equations.at(index));
        ode->Update(CoupledODEs.State, UpdatedState);
    }
    CoupledODEs.State = RocketState<T>(*UpdatedState);
    return true;
}
