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

#include "../Routes.h"
#include "../Physics.h"
#include "../Graphics/Texture.h"
#include "../Image.h"
#include "../Scene.h"
#include "ElevatorBase.h"
#include "Elevator.h"
#include "FloorBase.h"
#include "Level.h"
#include "Lobby.h"
#include "Tower.h"

Tower::Tower (int towerNo, int NoSubLevels, Scene& rScene )
:  mTowerNo (towerNo)
,  mNo_SubLevels (NoSubLevels)
,  mScene(rScene)
{
   mPopulation = 0;
   int nsubs = -NoSubLevels;
   for (int sub = nsubs; sub < 0; ++sub)
   {
      Level* level = new Level (sub, 400, sub, 400, this);
      mLevels.push_back (level);
   }
   Lobby* lobby = new Lobby (370, 796+72, 0, this);
   mLevels.push_back (lobby);
}

Tower::~Tower( )
{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      Level *pLevel = (*iLevel);
      delete pLevel;
   }
   mLevels.clear();
}

Level* Tower::NewLevel (int x, int y, int x2)
{
   int level = (int)mLevels.size() - mNo_SubLevels;
   Level* floor = new Level (level, x, y, x2,this);
   mLevels.push_back (floor);
   floor->ScanFloorSpace();   // get the floor space grid setup.
   return floor;
}

Level* Tower::GetLevel( int level ) // positive gets you a level above, negative gets you a basement level
{
   // What is the point of all this? Why not just store the levels in an std::map<int, CLevel>?
   std::vector<Level*>::size_type index = level + mNo_SubLevels;
   while (index > mLevels.size())
      NewLevel(400,(int)mLevels.size(),724);
   return mLevels[index];
}

Level* Tower::FindLevel(int id)
{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      if ((*iLevel)->GetID() == id )
      {
         return *iLevel;// = (*iLevel);
      }
   }
   return NULL;
}


void Tower::Update (float dt, int timeOfDay)
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

void Tower::DrawFramework (bool bLevelsOnly)

{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      (*iLevel)->DrawFramework (bLevelsOnly);
   }
//   mRoutes.RenderFramework(); do these later
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
