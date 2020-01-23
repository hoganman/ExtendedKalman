//
// Created by mhogan on 1/17/20.
//

#include <iostream>
#include "RungeKuttaO2.h"

template<class T>
RungeKuttaO2<T>::RungeKuttaO2() : EquationsOfMotion(nullptr){
}


template<class T>
RungeKuttaO2FCN<T>::RungeKuttaO2FCN() = default;


template<class T>
RungeKuttaO2FCN<T>::RungeKuttaO2FCN(T DeltaT) {
    TimeStep = DeltaT;
}




template<class T>
UpdateEquations<T>::UpdateEquations() : NEquation(0), TimeStep(0) {}

template<class T>
UpdateEquations<T>::UpdateEquations(T DeltaT) : NEquation(0) {TimeStep = DeltaT;}
