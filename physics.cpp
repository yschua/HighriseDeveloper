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

C_Body::C_Body ()
{
   m_s.x = 0;
   m_s.y = 0;
   m_v.x = 0;
   m_v.y = 0;
   m_a.x = 0;
   m_a.y = 0;
}

C_Body::C_Body (float x, float y)
{
   m_s.x = x;
   m_s.y = y;
   m_v.x = 0;
   m_v.y = 0;
   m_a.x = 0;
   m_a.y = 0;
}

float
C_Body::GetPositionX ()
{
   return m_s.x;
}

float
C_Body::GetPositionY ()
{
   return m_s.y;
}

float
C_Body::GetVelocityX ()
{
   return m_v.x;
}

float
C_Body::GetVelocityY ()
{
   return m_v.y;
}

float
C_Body::GetAccelerationX ()
{
   return m_a.x;
}

float
C_Body::GetAccelerationY ()
{
   return m_a.y;
}

void
C_Body::DebugPrint ()
{
   std::cout << "Body: Position " << m_s.x << " , " << m_s.y << std::endl
             << "Velocity " << m_v.x << " , " << m_v.y << std::endl
             << "Acceleration " << m_a.x << " , " << m_a.y << std::endl;
}

void
C_Body::SetPosition (float x, float y)
{
   m_s.x = x;
   m_s.y = y;
}

void
C_Body::SetVelocity (float x, float y)
{
   m_v.x = x;
   m_v.y = y;
}

void
C_Body::MoveTo (float x, float y, float time)
{
   m_IsMoving = true;
   m_Time = 0.0;
   m_TimeTotal += time;
   m_MoveDest.x = x;
   m_MoveDest.y = y;
   float dist_x = x - m_s.x;
   float dist_y = y - m_s.y;
   if (dist_x == 0)
   {
      m_v.x = 0;
      m_a.x = 0;
   }
   else
   {
      m_v.x = (2 * dist_x) / time;
      m_a.x = -(m_v.x * m_v.x) / (2 * dist_x);
   }
   if (dist_y == 0)
   {
      m_v.y = 0;
      m_a.y = 0;
   }
   else
   {
      m_v.y = (2 * dist_y) / time;
      m_a.y = -(m_v.y * m_v.y) / (2 * dist_y);
   }
}

void
C_Body::SetAcceleration (float x, float y)
{
   m_a.x = x;
   m_a.y = y;
}

void
C_Body::Integrate (float dt)
{
   float dt_secs = dt / 1000;
   m_s.x += m_v.x * dt_secs;
   m_s.y += m_v.y * dt_secs;
   m_v.x += m_a.x * dt_secs;
   m_v.y += m_a.y * dt_secs;
   if ((m_v.x > -10) && (m_v.x < 10))
   {
      m_v.x = 0;
      m_a.x = 0;
   }
   if ((m_v.y > -10) && (m_v.y < 10))
   {
      m_v.y = 0;
      m_a.y = 0;
   }
   if (m_IsMoving)
   {
      m_Time += dt;
      if (m_Time >= m_TimeTotal)
      {
         m_s = m_MoveDest;
         m_IsMoving = false;
         m_v.x = 0;
         m_v.y = 0;
         m_a.x = 0;
         m_a.y = 0;
      }
   }
}
