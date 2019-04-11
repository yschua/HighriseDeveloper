#pragma once

#include <SFML/Graphics.hpp>

// typedef std::pair<float, float> Vector3;
template <class T = float>
class Vector3
{
public:
    Vector3()
    {
        x = 0;
        y = 0;
        z = 0;
    }
    Vector3(T xv, T yv, T zv)
    {
        x = xv;
        y = yv;
        z = zv;
    }
    template <class U>
    Vector3(const sf::Vector3<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        z = Other.z;
    }
    template <class U>
    Vector3(const Vector3<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        z = Other.z;
    }
    template <class U>
    Vector3& operator+(const Vector3<U>& Other)
    {
        Vector3* temp = new Vector3(x + Other.x, y + Other.y, z + Other.z);
        return *temp;
    }
    template <class U>
    Vector3& operator+(const sf::Vector3<U>& Other)
    {
        Vector3* temp = new Vector3(x + Other.x, y + Other.y);
        return *temp;
    }
    template <class U>
    Vector3& operator=(const Vector3<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        z = Other.z;
        return *this;
    }
    template <class U>
    Vector3<T>& operator=(const sf::Vector3<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        z = Other.z;
        return *this;
    }
    template <class U>
    Vector3<T>& operator-(const Vector3<U>& Other)
    {
        return *(new Vector3(-Other.x, -Other.y));
    }
    T x;
    T y;
    T z;
};

typedef Vector3<float> Vector3f; // russ
typedef Vector3<int> Vector3i;   // likes this
