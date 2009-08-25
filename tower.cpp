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

#include <list>

#include "routeBase.h"
#include "routes.h"
#include "physics.h"
#include "elevatorBase.h"
#include "elevator.h"
#include "floorbase.h"
#include "level.h"
#include "lobby.h"
#include "tower.h"

C_Tower::C_Tower( int towerNo )
:  m_TowerNo( towerNo )
{
   C_level* maint = new C_level (0);
   m_SubLevels.push_back (maint);
   C_Lobby* lobby = new C_Lobby (370, 640, 0);
   m_Levels.push_back (lobby);
}

C_Tower::~C_Tower( )
{
}

C_level* C_Tower::newLevel( )
{
   int level = m_Levels.size();
   C_level* floor = new C_level( level);   
   m_Levels.push_back (floor);
   return floor;
}

C_level* C_Tower::newSubLevel( )
{
   int level = m_Levels.size();
   C_level* floor = new C_level( -level);
   m_SubLevels.push_back (floor);
   return floor;
}

C_level* C_Tower::getLevel( int level ) // positive gets you a level above, negative gets you a basement level
{
   C_level* floor = 0;
   if( level < 0 )
   {
      unsigned int ul = abs(level);
      if( ul <= this->m_Levels.size() )
      {
//         pLevel = m_Levels[ul];
      }
   }
   else
   {
      unsigned int ul = abs(level);
      if( ul <= this->m_Levels.size() )
      {
//         pLevel = m_Levels[ul];
      }
   }
   return floor;
}

void C_Tower::update (float dt)
{
   std::list<C_level *>::iterator iLevel;
   for (iLevel = m_Levels.begin (); iLevel != m_Levels.end (); iLevel++)
   {
      (*iLevel)->update( dt );
   }
   std::list<C_level *>::iterator iSub;
   for (iSub = m_SubLevels.begin (); iSub != m_SubLevels.end (); iSub++)
   {
      (*iSub)->update( dt );
   }
}

void C_Tower::draw ()
{
   std::list<C_level *>::iterator iLevel;
   for (iLevel = m_Levels.begin (); iLevel != m_Levels.end (); iLevel++)
   {
      (*iLevel)->draw( );
   }
   std::list<C_level *>::iterator iSub;
   for (iSub = m_SubLevels.begin (); iSub != m_SubLevels.end (); iSub++)
   {
      (*iSub)->draw( );
   }
}