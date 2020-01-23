//
// Created by mhogan on 1/17/20.
//

#ifndef EXTENDEDKALMAN_RUNGEKUTTAO2_H
#define EXTENDEDKALMAN_RUNGEKUTTAO2_H

#include <vector>
#include "Vector2.h"

template <class T> class RungeKuttaO2;
template <class T> class RungeKuttaO2FCN;
template <class T> class UpdateEquations;

template <class T> class RungeKuttaO2 {

public:

    //default constructor
    RungeKuttaO2();

    virtual ~RungeKuttaO2()= default;

    UpdateEquations<T>* EquationsOfMotion;

    int NEquations;
};

template <class T> class RungeKuttaO2FCN {

public:

    RungeKuttaO2FCN();

    explicit RungeKuttaO2FCN(T DeltaT);

    virtual ~RungeKuttaO2FCN() = default;

    T GetTimeStep() const {return TimeStep;}

    T TimeStep;

};

template <class T> class UpdateEquations {

public:

    UpdateEquations();

    explicit UpdateEquations(T DeltaT);

    virtual ~UpdateEquations();

    bool AddEquation(RungeKuttaO2FCN<T>* eqn);

    [[nodiscard]] int GetNEquations() const {return NEquation;}

    std::vector< RungeKuttaO2FCN<T>* > Equations;

    int NEquation;

    T TimeStep;

};


#endif //EXTENDEDKALMAN_RUNGEKUTTAO2_H
