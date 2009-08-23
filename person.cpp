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

// People that make the tower thrive.

#include "person.h"

C_Person::C_Person (Location& loc)
{
   m_Health = HS_Well;
   m_Mood = MS_Content;
   m_Activity = AS_JobHunting; // noob, starts out looking for home, job etc.
   m_Occupation = 0;
   m_Home = 1;          // have a home (Test code)
   m_Location = loc;    // copy
}

C_Person::~C_Person (void)
{
}

void C_Person::update (float dt)
{
   // check time of day, what activity should we be doing.
   if (m_Occupation < 1) // && age > 16 )
   {
      m_Activity = AS_JobHunting;
   }
   else if (m_Home < 1)
   {
      m_Activity = AS_CondoHunting; // if income < $n AS_ApartmentHunting.
   }
   if (m_Activity == AS_GoingToWork)
   {
      if (m_WorkPath.index < m_WorkPath.size)
      {
         Location& cur = m_WorkPath.m_PathList[m_WorkPath.index];
         // TODO: check building first but for now we only have 1
         if (cur.m_Level == m_Location.m_Level)
         {
            m_Location.m_X = cur.m_X; // TODO: Move peep in animator
            m_WorkPath.index++;
         }
         else
         {
            // waiting or on an elevator
         }
      }
      if (m_WorkPath.index >= m_WorkPath.size) // this can be handled better and also need to check times
      {
         set_Activity( AS_Working ); // offices and businesses show employees at work.
      }
   }
}

void C_Person::draw( )
{
}
