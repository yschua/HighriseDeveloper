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

#include "highrisedev.h"

Body::Body ()
{
   ms.x = 0;
   ms.y = 0;
   mv.x = 0;
   mv.y = 0;
   ma.x = 0;
   ma.y = 0;
}

Body::Body (float x, float y)
{
   ms.x = x;
   ms.y = y;
   mv.x = 0;
   mv.y = 0;
   ma.x = 0;
   ma.y = 0;
}

float
Body::GetPositionX ()
{
   return ms.x;
}

float
Body::GetPositionY ()
{
   return ms.y;
}

float
Body::GetVelocityX ()
{
   return mv.x;
}

float
Body::GetVelocityY ()
{
   return mv.y;
}

float
Body::GetAccelerationX ()
{
   return ma.x;
}

float
Body::GetAccelerationY ()
{
   return ma.y;
}

void
Body::DebugPrint ()
{
   std::cout << "Body: Position " << ms.x << " , " << ms.y << std::endl
             << "Velocity " << mv.x << " , " << mv.y << std::endl
             << "Acceleration " << ma.x << " , " << ma.y << std::endl;
}

void
Body::SetPosition (float x, float y)
{
   ms.x = x;
   ms.y = y;
}

void
Body::SetVelocity (float x, float y)
{
   mv.x = x;
   mv.y = y;
}

void
Body::MoveTo (float x, float y, float time)
{
   mIsMoving = true;
   mTime = 0.0;
   mTimeTotal += time;
   mMoveDest.x = x;
   mMoveDest.y = y;
   float dist_x = x - ms.x;
   float dist_y = y - ms.y;
   if (dist_x == 0)
   {
      mv.x = 0;
      ma.x = 0;
   }
   else
   {
      mv.x = (2 * dist_x) / time;
      ma.x = -(mv.x * mv.x) / (2 * dist_x);
   }
   if (dist_y == 0)
   {
      mv.y = 0;
      ma.y = 0;
   }
   else
   {
      mv.y = (2 * dist_y) / time;
      ma.y = -(mv.y * mv.y) / (2 * dist_y);
   }
}

void
Body::SetAcceleration (float x, float y)
{
   ma.x = x;
   ma.y = y;
}

void
Body::Integrate (float dt)
{
   float dt_secs = dt / 1000;
   ms.x += mv.x * dt_secs;
   ms.y += mv.y * dt_secs;
   mv.x += ma.x * dt_secs;
   mv.y += ma.y * dt_secs;
   if ((mv.x > -10) && (mv.x < 10))
   {
      mv.x = 0;
      ma.x = 0;
   }
   if ((mv.y > -10) && (mv.y < 10))
   {
      mv.y = 0;
      ma.y = 0;
   }
   if (mIsMoving)
   {
      mTime += dt;
      if (mTime >= mTimeTotal)
      {
         ms = mMoveDest;
         mIsMoving = false;
         mv.x = 0;
         mv.y = 0;
         ma.x = 0;
         ma.y = 0;
      }
   }
}
