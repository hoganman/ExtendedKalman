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

};

template class RungeKuttaO2<double>;
template class RungeKuttaO2<float>;

template <class T> class RungeKuttaO2FCN {

public:

    RungeKuttaO2FCN();

    explicit RungeKuttaO2FCN(T DeltaT);

    virtual ~RungeKuttaO2FCN() = default;

    T GetTimeStep() const {return TimeStep;}

    T TimeStep;

};

template class RungeKuttaO2FCN<float>;
template class RungeKuttaO2FCN<double>;

template <class T> class UpdateEquations {

public:

    UpdateEquations();

    explicit UpdateEquations(T DeltaT);

    virtual ~UpdateEquations() = default;

    [[nodiscard]] int GetNEquations() const {return NEquation;}

    int NEquation;

    T TimeStep;

};

template class UpdateEquations<double>;
template class UpdateEquations<float>;

#endif //EXTENDEDKALMAN_RUNGEKUTTAO2_H
