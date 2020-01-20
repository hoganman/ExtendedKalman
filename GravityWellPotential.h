//
// Created by mhogan on 1/18/20.
//

#ifndef EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
#define EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H

#include "RungeKuttaO2.h"
#include "Vector2.h"

template <class T> class GravityWellPotential : public RungeKuttaO2FCN<T>{

public:

    GravityWellPotential();

    explicit GravityWellPotential(T RocketMass);

protected:

    T Mass;

};


template <class T> class RocketState : public RungeKuttaO2State<T> {

    RocketState();

    RocketState(RungeKuttaO2State<T> State, Vector2<T> RocketDir);

    RocketState(Vector2<T> y0, Vector2<T> yprime0, Vector2<T> RocketDir);

    Vector2<T> GetRocketDirection() const {return RocketDirection;}

protected:

    Vector2<T> RocketDirection;

    //T ExhaustVelocity;

};

template <class T> class GravityWellPotentialXDir : public GravityWellPotential<T> {

public:

    GravityWellPotentialXDir() = default;

    explicit GravityWellPotentialXDir(T RocketMass) : GravityWellPotential<T>(RocketMass){}

    bool UpdateFCN(const T& TimeStep, const RocketState<T> &State, RocketState<T>* ReturnState);

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
