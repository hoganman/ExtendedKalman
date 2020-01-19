//
// Created by mhogan on 1/17/20.
//

#ifndef EXTENDEDKALMAN_RUNGEKUTTAO2_H
#define EXTENDEDKALMAN_RUNGEKUTTAO2_H

#include <vector>
#include "Vector2.h"

template <class T> class RungeKuttaO2;
template <class T> class RungeKuttaO2FCN;
template <class T> class RungeKuttaO2State;

template <class T> class RungeKuttaO2 {

public:

    //default constructor
    RungeKuttaO2();

    virtual ~RungeKuttaO2()= default;

    //constructor which takes the initial state, update function, and step size
    RungeKuttaO2(RungeKuttaO2State<T>* InitialState, RungeKuttaO2FCN<T>* UpdateFcn, T StepSize);

    //Progresses the state forward
    bool Update();

    bool GetState(RungeKuttaO2State<T>* ReturnState);

protected:

    //Initial state of the system
    RungeKuttaO2State<T>* State;

    RungeKuttaO2FCN<T>* UpdateFunction;

    T TimeStep;
};

template <class T> class RungeKuttaO2FCN {

public:

    RungeKuttaO2FCN();

    virtual ~RungeKuttaO2FCN() = default;

    virtual bool UpdateFCN(const T& TimeStep, const RungeKuttaO2State<T> &State, RungeKuttaO2State<T>* UpdatedState);
};


template <class T> class RungeKuttaO2State {
public:

    RungeKuttaO2State();

    RungeKuttaO2State(const RungeKuttaO2State<T>& copy);

    RungeKuttaO2State(T y0, T yprime0, T t0=0);

    virtual ~RungeKuttaO2State() = default;

    T GetTime() const {return Time;}

    Vector2<T> GetPosition() const {return Position;}

    Vector2<T> GetVelocity() const {return Velocity;}
protected:

    T Time;

    Vector2<T> Position;

    Vector2<T> Velocity;
};


#endif //EXTENDEDKALMAN_RUNGEKUTTAO2_H
