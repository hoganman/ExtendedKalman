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
bool GravityWellPotentialXDir<T>::UpdateFCN(const T& TimeStep, const RungeKuttaO2State<T> &State,
                                            RungeKuttaO2State<T>* ReturnState) {

    using namespace PhysicalConstants;
    T UpdatedPosition = State.GetPosition() + TimeStep * State.GetVelocity() \
                        - 0.5 * TimeStep * TimeStep *(kGravitation * kMoonMass);

}

