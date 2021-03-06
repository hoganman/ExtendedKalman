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

    explicit Vector2(std::vector<T> vec);

    explicit Vector2(T* arr);

    virtual ~Vector2() = default;

    T GetX() const {return X;}

    T GetY() const {return Y;}

    T GetMag2() const;

    T GetMag(const double &power=1) const;

    T GetTheta() const {return atan2(Y, X);}

    T GetInnerProduct(const Vector2<T>& vec) const {return X * vec.X + Y * vec.Y;}

    T GetAngle(const Vector2<T>& vec);

    Vector2<T>& operator=(const Vector2<T>& arg);

    Vector2<T>& operator-(Vector2<T>& arg);

    Vector2<T>& operator+(Vector2<T>& arg);

    T X;

    T Y;

};

template class Vector2<double>;
template class Vector2<float>;

#endif //EXTENDEDKALMAN_VECTOR2_H
