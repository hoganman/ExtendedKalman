//
// Created by mhogan on 1/17/20.
//

#include <iostream>
#include "RungeKuttaO2.h"

template<class T>
RungeKuttaO2<T>::RungeKuttaO2() : TimeStep(0), UpdateFunction(nullptr){
    State = std::vector<T>(0);
}

template<class T>
RungeKuttaO2<T>::RungeKuttaO2(RungeKuttaO2State* InitialState, RungeKuttaO2FCN *UpdateFcn, T StepSize) {

    State = InitialState;
    UpdateFunction = UpdateFcn;
    TimeStep = StepSize;

}

template<class T>
bool RungeKuttaO2<T>::Update() {

    //T k1, k2;
    //k1 = TimeStep * UpdateFunction(State);
    return false;
}

template<class T>
bool RungeKuttaO2<T>::GetState(RungeKuttaO2State<T> *ReturnState) {
    ReturnState = new RungeKuttaO2State<T> (State);
    (void*)ReturnState;
    return true;
}

template<class T>
RungeKuttaO2FCN<T>::RungeKuttaO2FCN() = default;


template<class T>
T RungeKuttaO2FCN<T>::UpdateFCN(T TimeStep, RungeKuttaO2State<T> State) {
    (void)TimeStep;
    (void)State;
    std::cout << "WARNING: No update function have been declared for the Runge-Kutta integrator!" << std::endl;
    std::cout << "Please implement a RungeKuttaOFFCN instance!" << std::endl;
    exit(1);
    //return RungeKuttaO2State<T>();
}

template<class T>
RungeKuttaO2State<T>::RungeKuttaO2State() : Time(0), Position(0), Velocity(0){

}

template<class T>
RungeKuttaO2State<T>::RungeKuttaO2State(T y0, T yprime0, T t0) {

    Position = y0;
    Velocity = yprime0;
    Time = t0;

}

template<class T>
RungeKuttaO2State<T>::RungeKuttaO2State(const RungeKuttaO2State<T> &copy) {
   copy.Time = Time;
   copy.Velocity = Velocity;
   copy.Position = Position;
}
