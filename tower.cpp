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

/*
#include <vector> // changed from list to vector so the collection can be scrolled in up and down


#include "routeBase.h"
#include "routes.h"
#include "physics.h"
#include "elevatorBase.h"
#include "elevator.h"
#include "floorbase.h"
#include "level.h"
#include "lobby.h"
#include "tower.h"*/

#include "highrisedev.h"

C_Tower::C_Tower( int towerNo, int NoSubLevels )
      :  m_TowerNo( towerNo )
      ,  m_No_SubLevels( NoSubLevels )
{
   //C_level* maint = new C_level (0);
   //m_SubLevels.push_back (maint);
   int nsubs = -NoSubLevels;
   for (int sub = nsubs; sub < 0; ++sub)
   {
      C_level* level = new C_level (sub, this);
      m_Levels.push_back (level);
   }
   C_Lobby* lobby = new C_Lobby (370, 640, 0, this);
   m_Levels.push_back (lobby);
}

C_Tower::~C_Tower( )
{

}

C_level * C_Tower::NewLevel( )
{
   int level = m_Levels.size() - m_No_SubLevels;
   C_level* floor = new C_level (level, this);
   m_Levels.push_back (floor);
   return floor;
}

//C_level* C_Tower::newSubLevel( )
//{
//   int level = m_Levels.size();
//   C_level* floor = new C_level( -level);
//   m_SubLevels.push_back (floor);
//   return floor;
//}

C_level* C_Tower::GetLevel( int level ) // positive gets you a level above, negative gets you a basement level
{
   // What is the point of all this? Why not just store the levels in an std::map<int, CLevel>?
   int index = level + m_No_SubLevels;
   return m_Levels[index];
}

void C_Tower::Update (float dt)
{
   std::vector<C_level *>::iterator iLevel;
   for (iLevel = m_Levels.begin (); iLevel != m_Levels.end (); iLevel++)
   {
      (*iLevel)->Update( dt );
   }
   m_Routes.Update( dt );
}

void C_Tower::Draw ()
{
   std::vector<C_level *>::iterator iLevel;
   for (iLevel = m_Levels.begin (); iLevel != m_Levels.end (); iLevel++)
   {
      (*iLevel)->Draw( );
   }
   m_Routes.Draw();
}
