//
// Created by mhogan on 1/17/20.
//

#include <iostream>
#include "RungeKuttaO2.h"

template<class T>
RungeKuttaO2<T>::RungeKuttaO2() : EquationsOfMotion(nullptr), NEquations(0){
}


template<class T>
RungeKuttaO2FCN<T>::RungeKuttaO2FCN() = default;


template<class T>
RungeKuttaO2FCN<T>::RungeKuttaO2FCN(T DeltaT) {
    TimeStep = DeltaT;
}


template<class T>
bool UpdateEquations<T>::AddEquation(RungeKuttaO2FCN<T>* eqn) {
    if( !eqn )
        return false;
    Equations.push_back(eqn);
    NEquation = Equations.size();
    return true;
}

template<class T>
UpdateEquations<T>::~UpdateEquations() {

    for(unsigned int i = 0; i < Equations.size(); ++i){
        if (Equations.at(i))
            delete Equations.at(i);
    }
    Equations.clear();

}

template<class T>
UpdateEquations<T>::UpdateEquations() : NEquation(0), TimeStep(0) {}

template<class T>
UpdateEquations<T>::UpdateEquations(T DeltaT) : NEquation(0) {TimeStep = DeltaT;}
