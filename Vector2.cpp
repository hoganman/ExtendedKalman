//
// Created by mhogan on 1/18/20.
//

#include "Vector2.h"

template<class T>
Vector2<T>::Vector2(T x, T y) {

    Elements.clear();
    T dummy[] = {x, y};
    Elements = (dummy, dummy + 2);
}

template<class T>
Vector2<T>::Vector2(T *arr) {

    Elements = (arr, arr + 2);
}

template<class T>
Vector2<T> &Vector2<T>::operator=(const Vector2<T> &arg) {
    if(this == &arg)
        return *this;
    this->Elements = arg.Elements;
    return *this;
}

template<class T>
T Vector2<T>::GetMag2() const {return GetX()*GetX() + GetY()*GetY();}

template<class T>
Vector2<T> &Vector2<T>::operator-(Vector2<T> &arg) {
    Elements[0] -= arg.GetX();
    Elements[1] -= arg.GetY();
    return *this;
}

template<class T>
Vector2<T> &Vector2<T>::operator+(Vector2<T> &arg) {
    Elements[0] += arg.GetX();
    Elements[1] += arg.GetY();
    return *this;
}

template<class T>
Vector2<T>::~Vector2() {
    Elements.clear();
}

