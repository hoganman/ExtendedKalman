//
// Created by mhogan on 1/18/20.
//

#ifndef EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
#define EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H

#include "RungeKuttaO2.h"
#include "Vector2.h"

template <class T> class RocketState {

    RocketState(T InitialMass, Vector2<T> InitialPosition, Vector2<T> InitialVelocity, T t0=0);

    RocketState(const RocketState<T>& copy);

    Vector2<T> GetPosition() const {return Position;}

    Vector2<T> GetVelocity() const {return Velocity;}

    Vector2<T> Position;

    Vector2<T> Velocity;

    T Time;

    T Mass;

};

template <class T> class GravityWellPotentialXVel : public RungeKuttaO2FCN<T> {

public:

    GravityWellPotentialXVel() = default;

    explicit GravityWellPotentialXVel(T DeltaT) : RungeKuttaO2FCN<T>(DeltaT){}

    virtual ~GravityWellPotentialXVel() = default;

    bool Update(const RocketState<T> &State, RocketState<T>* UpdatedState);

    T UpdateFCN(const RocketState<T> &State);

};

/*
template <class T> class GravityWellPotentialXPos : public RungeKuttaO2FCN<T> {

public:

    GravityWellPotentialXPos() = default;

    virtual ~GravityWellPotentialXPos() = default;

};

template <class T> class GravityWellPotentialYPos : public RungeKuttaO2FCN<T> {

public:

    GravityWellPotentialYPos() = default;

    virtual ~GravityWellPotentialYPos() = default;

};

template <class T> class GravityWellPotentialYVel : public RungeKuttaO2FCN<T> {

public:

    GravityWellPotentialYVel() = default;

    virtual ~GravityWellPotentialYVel() = default;

};
*/

template <class T> class RocketUpdateEquations : public UpdateEquations<T> {
public:

    RocketUpdateEquations() = default;

    RocketUpdateEquations(T DeltaT, RocketState<T> InputState);

    RocketState<T> State;

    enum KinematicId {
        XPosition = 0,
        XVelocity,
        YPosition,
        YVelocity,
        NEquations
    };

};


template <class T> class RocketInEarthMoonSystem : public RungeKuttaO2<T> {

public:

    RocketInEarthMoonSystem() = default;

    //RocketInEarthMoonSystem(RocketState<T> rocket);
};

namespace PhysicalConstants
{

    //Units meter^3 kg^(-1) sec^(-2)
    const double kGravitation = 6.67430E-11;

    //Units kg
    const double kMoonMass = 7.342E22;

    //Units kg
    const double kEarthMass = 5.9722E24;

    //Units km
    const double kMoonSemiMajorAxis = 384399;

}

#endif //EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
