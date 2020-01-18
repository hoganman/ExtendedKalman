//
// Created by mhogan on 1/18/20.
//

#ifndef EXTENDEDKALMAN_VECTOR2_H
#define EXTENDEDKALMAN_VECTOR2_H

#include <vector>
#include <cmath>

template <class T> class Vector2 {

public:
    Vector2() = default;

    Vector2(T x, T y);

    explicit Vector2(std::vector<T> vec) {Elements = vec;}

    explicit Vector2(T* arr);

    virtual ~Vector2();

    T GetX() const {return Elements.at(0);}

    T GetY() const {return Elements.at(1);}

    T GetMag2() const;

    T GetMag() const {return std::sqrt(GetMag2());}

    Vector2<T>& operator=(const Vector2<T>& arg);

    Vector2<T>& operator-(Vector2<T>& arg);

    Vector2<T>& operator+(Vector2<T>& arg);

protected:

    std::vector<T> Elements;

};


#endif //EXTENDEDKALMAN_VECTOR2_H
