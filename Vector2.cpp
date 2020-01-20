//
// Created by mhogan on 1/18/20.
//

#include <iostream>
#include "Vector2.h"

template<class T>
Vector2<T>::Vector2(T x, T y) {

    X = x;
    Y = y;
}


template<class T>
Vector2<T>::Vector2(std::vector<T> vec) {

    if(vec.size() != 2)
        std::cout << "Wrong size vector!" << std::endl;
    T* arr = vec.data();
    X = arr[0];
    Y = arr[0];

}

template<class T>
Vector2<T>::Vector2(T *arr) {

    X = arr[0];
    Y = arr[0];

}

template<class T>
Vector2<T> &Vector2<T>::operator=(const Vector2<T> &arg) {
    if(this == &arg)
        return *this;
    X = arg.X;
    Y = arg.Y;
    return *this;
}

template<class T>
T Vector2<T>::GetMag2() const {return GetX()*GetX() + GetY()*GetY();}


template<class T>
Vector2<T> &Vector2<T>::operator-(Vector2<T> &arg) {
    X -= arg.X;
    Y -= arg.Y;
    return *this;
}

template<class T>
Vector2<T> &Vector2<T>::operator+(Vector2<T> &arg) {
    X += arg.X;
    Y += arg.Y;
    return *this;
}

template<class T>
T Vector2<T>::GetMag(const double &power) const {
    double mag2 = GetMag2();
    if (power == 1)
        return sqrt(mag2);
    if (power == 2)
        return mag2;
    if (power == 3)
    {
        return mag2 * sqrt(mag2);
    }
    return pow(mag2, power * 0.5);
}


