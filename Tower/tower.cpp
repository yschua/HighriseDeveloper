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

#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include <list>

#include "../routes.h"
#include "../physics.h"
#include "elevatorBase.h"
#include "elevator.h"
#include "floorBase.h"
#include "level.h"
#include "lobby.h"
#include "tower.h"

Tower::Tower (int towerNo, int NoSubLevels)
      :  mTowerNo (towerNo)
      ,  mNo_SubLevels (NoSubLevels)
{
   //level* maint = new level (0);
   //mSubLevels.push_back (maint);
   mPopulation = 0;
   int nsubs = -NoSubLevels;
   for (int sub = nsubs; sub < 0; ++sub)
   {
      Level* level = new Level (sub, 400, sub, 472, this);
      mLevels.push_back (level);
   }
   Lobby* lobby = new Lobby (370, 640, 0, this);
   mLevels.push_back (lobby);
}

Tower::~Tower( )
{

}

Level* Tower::NewLevel (int x, int y, int x2)
{
   int level = (int)mLevels.size() - mNo_SubLevels;
   Level* floor = new Level (level, x, y, x2,this);
   mLevels.push_back (floor);
   return floor;
}

//level* Tower::newSubLevel( )
//{
//   int level = mLevels.size();
//   level* floor = new level( -level);
//   mSubLevels.push_back (floor);
//   return floor;
//}
//void Tower::DebugLoad(int x, int y, int z) {
//   // Do something//
//}

Level* Tower::GetLevel( int level ) // positive gets you a level above, negative gets you a basement level
{
   // What is the point of all this? Why not just store the levels in an std::map<int, CLevel>?
   int index = level + mNo_SubLevels;
   return mLevels[index];
}

void Tower::Update (float dt)
{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      (*iLevel)->Update( dt );
   }
   mRoutes.Update( dt );
}

void Tower::Draw ()
{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      (*iLevel)->Draw( );
   }
   mRoutes.Draw();
}

// AI interface
void Tower::EnterTower (Person* pPerson)
{
   //when implemented, this funcition will place people into a queue, for an elevator, at the checkin desk etc.
   mPopulation++;
}

// AI interface
void Tower::LeaveTower (Person* pPerson)
{
   // when implemented, this function will take people out of the building, walking, bus, train etc.
   mPopulation--;
   if (mPopulation < 0 )
      mPopulation = 0;
}
