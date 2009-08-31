/*   This file is part of Highrise Developer.
 *
 *   Highrise Developer is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _PHYSICS_H
#define _PHYSICS_H

//typedef std::pair<float, float> vector2;
template <class T = float>
class Vector2
{
    public:
    Vector2()
    {
        x = 0; y = 0;
    }
    Vector2(T xv, T yv)
    {
        x = xv; y = yv;
    }
    template <class U>
    Vector2(const sf::Vector2<U>& Other)
    {
        x = Other.x; y = Other.y;
    }
    template <class U>
    Vector2(const Vector2<U>& Other)
    {
        x = Other.x; y = Other.y;
    }
    template <class U>
    Vector2& operator+(const Vector2<U>& Other)
    {
        Vector2* temp = new Vector2(x+Other.x, y+Other.y);
        return *temp;
    }
    template <class U>
    Vector2& operator+(const sf::Vector2<U>& Other)
    {
        Vector2* temp = new Vector2(x+Other.x, y+Other.y);
        return *temp;
    }
    template <class U>
    Vector2& operator=(const Vector2<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        return *this;
    }
    template <class U>
    sf::Vector2<T>& operator=(const Vector2<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        return *this;
    }
    template <class U>
    Vector2<T>& operator=(const sf::Vector2<U>& Other)
    {
        x = Other.x;
        y = Other.y;
        return *this;
    }
    T x;
    T y;
};

typedef Vector2 <float> Vector2f; // russ 
typedef Vector2 <int> Vector2i;   // likes this

class C_Body
{
private:
   bool m_IsMoving;
   float m_Time;
   float m_TimeTotal;
   Vector2f m_MoveDest;

public:
   Vector2f m_s, m_v, m_a;
   C_Body (float x, float y);
   C_Body ();
   float GetPositionX ();
   float GetPositionY ();
   float GetVelocityX ();
   float GetVelocityY ();
   float GetAccelerationX ();
   float GetAccelerationY ();
   Vector2f GetPosition ();
   Vector2f GetVelocity ();
   Vector2f GetAcceleration ();
   void DebugPrint ();
   void SetPosition (float x, float y);
   void SetVelocity (float x, float y);
   void SetAcceleration (float x, float y);
   void Integrate (float dt);
   void MoveTo (float x, float y, float time);
};

#endif
