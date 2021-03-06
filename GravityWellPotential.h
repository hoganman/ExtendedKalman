#ifndef EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
#define EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H

#include "RungeKuttaO2.h"
#include "Vector2.h"
#include <math.h>

template <class T> class RocketState {

public:
    RocketState() = default;

    RocketState(T InitialMass, Vector2<T> InitialPosition, Vector2<T> InitialVelocity, T t0=0);

    RocketState(const RocketState<T>& copy);

    [[nodiscard]] Vector2<T> GetPosition() const {return Position;}

    [[nodiscard]] Vector2<T> GetVelocity() const {return Velocity;}

    Vector2<T> Position;

    Vector2<T> Velocity;

    T Time;

    T Mass;

};

template class RocketState<double>;
template class RocketState<float>;

template <class T> class GravityWellPotential : public RungeKuttaO2FCN<T> {

public:

    GravityWellPotential() : RungeKuttaO2FCN<T>(){}

    ~GravityWellPotential<T>() override = default;

    explicit GravityWellPotential(T DeltaT) : RungeKuttaO2FCN<T>(DeltaT){}

};

template class GravityWellPotential<double>;
template class GravityWellPotential<float>;

template <class T> class GravityWellPotentialXPos : public GravityWellPotential<T> {

public:

    GravityWellPotentialXPos() = default;

    explicit GravityWellPotentialXPos(T DeltaT) : GravityWellPotential<T>(DeltaT){}

    ~GravityWellPotentialXPos() override = default;

    bool Update(const RocketState<T> &State, RocketState<T>* UpdatedState);

    T UpdateFCN(const RocketState<T> &State);
};

template class GravityWellPotentialXPos<double>;
template class GravityWellPotentialXPos<float>;

template <class T> class GravityWellPotentialXVel : public GravityWellPotential<T> {

public:

    GravityWellPotentialXVel() = default;

    explicit GravityWellPotentialXVel(T DeltaT) : GravityWellPotential<T>(DeltaT){}

    ~GravityWellPotentialXVel() override = default;

    bool Update(const RocketState<T> &State, RocketState<T>* UpdatedState);

    T UpdateFCN(const RocketState<T> &State);

};

template class GravityWellPotentialXVel<double>;
template class GravityWellPotentialXVel<float>;

template <class T> class GravityWellPotentialYPos : public GravityWellPotential<T> {

public:

    GravityWellPotentialYPos() = default;

    explicit GravityWellPotentialYPos(T DeltaT) : GravityWellPotential<T>(DeltaT){}

    ~GravityWellPotentialYPos() override = default;

    bool Update(const RocketState<T> &State, RocketState<T>* UpdatedState);

    T UpdateFCN(const RocketState<T> &State);
};

template class GravityWellPotentialYPos<double>;
template class GravityWellPotentialYPos<float>;

template <class T> class GravityWellPotentialYVel : public GravityWellPotential<T> {

public:

    GravityWellPotentialYVel() = default;

    explicit GravityWellPotentialYVel(T DeltaT) : GravityWellPotential<T>(DeltaT){}

    ~GravityWellPotentialYVel() override = default;

    bool Update(const RocketState<T> &State, RocketState<T>* UpdatedState);

    T UpdateFCN(const RocketState<T> &State);
};

template class GravityWellPotentialYVel<double>;
template class GravityWellPotentialYVel<float>;

template <class T> class RocketUpdateEquations : public UpdateEquations<T> {
public:

    RocketUpdateEquations() = default;

    RocketUpdateEquations(T DeltaT, RocketState<T> InputState);

    ~RocketUpdateEquations() override;

    RocketState<T> State;

    GravityWellPotentialXPos<T>* XPosODE;

    GravityWellPotentialYPos<T>* YPosODE;

    GravityWellPotentialXVel<T>* XVelODE;

    GravityWellPotentialYVel<T>* YVelODE;

    enum KinematicId {
        XPosition = 0,
        XVelocity,
        YPosition,
        YVelocity,
        NEquations
    };

};

template class RocketUpdateEquations<double>;
template class RocketUpdateEquations<float>;

template <class T> class RocketInEarthMoonSystem : public RungeKuttaO2<T> {

public:

    RocketInEarthMoonSystem() = default;

    RocketInEarthMoonSystem(T DeltaT, RocketState<T> rocket);

    bool Update();

    [[nodiscard]] RocketState<T> GetState() const {return CoupledODEs.State;}

    RocketUpdateEquations<T> CoupledODEs;
};

template class RocketInEarthMoonSystem<double>;
template class RocketInEarthMoonSystem<float>;

namespace PhysicalConstants
{

    const double meter = 1.0;

    const double kilo = 1E3;

    const double gram = 1E-3;

    const double second = 1.0;

    const double minute = 60 * second;

    const double hour = 60 * minute;

    const double day = 24 * hour;

    const double year = 365.24 * day;

    const double kilogram = kilo * gram;

    const double kilometer = kilo * meter;

    const double kGravitation = 6.67430E-11 * meter * meter * meter / kilogram / second / second;

    const double kMoonMass = 7.342E22 * kilogram;

    const double kEarthMass = 5.9722E24 * kilogram;

    const double kEarthRadius = 6371.0 * kilometer;

    const double kMoonSemiMajorAxis = 384399 * kilometer;

    const double kMoonRadius = 1737.4 * kilometer;

}

#endif //EXTENDEDKALMAN_GRAVITYWELLPOTENTIAL_H
