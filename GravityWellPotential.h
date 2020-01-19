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

template <class T> class GravityWellPotentialXDir : public GravityWellPotential<T> {

public:

    GravityWellPotentialXDir() = default;

    explicit GravityWellPotentialXDir(T RocketMass) : GravityWellPotential<T>(RocketMass){}

    bool UpdateFCN(const T& TimeStep, const RungeKuttaO2State<T> &State, RungeKuttaO2State<T>* ReturnState);


};


namespace PhysicalConstants
{

    //Units meter^3 kg^(-1) sec^(-2)
    const double kGravitation = 6.67430E-11;

    //Units kg
    const double kMoonMass = 7.342E22;

    //Units kg
    const double kEarthMass = 5.9722E24;

}

#endif //EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
