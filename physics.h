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

// Is there a way to avoid this include?
#include "Types/Vector2.h"

class Body
{
private:
   bool mIsMoving;
   float mTime;
   float mTimeTotal;
   Vector2f mMoveDest;

public:  // protect these memvars and add gets
   Vector2f ms;
   Vector2f mv;
   Vector2f ma;

public:
   // CTOR
   Body ();
   Body (float x, float y);
   Body (Vector2f Pos);

   //Properties
   float GetPositionX () { return ms.x; }
   float GetPositionY () { return ms.y; }
   Vector2f GetPosition() { return ms; }
   float GetVelocityX () { return mv.x; }
   float GetVelocityY () { return mv.y; }
   Vector2f GetVelocity() { return mv; }
   float GetAccelerationX () { return ma.x; }
   float GetAccelerationY () { return ma.y; }
   Vector2f GetAcceleration() { return ma; }

   // Mothods
   void DebugPrint ();
   // Depreciated!
   void SetPosition (float x, float y);
   void SetVelocity (float x, float y);
   void SetAcceleration (float x, float y);

   void SetPosition (const Vector2f& NewPos) { ms = NewPos; }
   void SetVelocity (const Vector2f& NewV) { mv = NewV; }
   void SetAcceleration (const Vector2f& NewA) { ma = NewA; }

   void Integrate (float dt);
   void MoveTo (float x, float y, float time);
};

#endif
