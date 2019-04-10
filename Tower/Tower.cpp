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

#include "../Root/Physics.h"
#include "../Graphics/Texture.h"
#include "../Graphics/Image.h"
#include "../Scene/Scene.h"
#include "Routes.h"
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
,  mGhostRoom (0,0)
{
   mPopulation = 0;
   mAvailableFunds = 0;
   mFloorWorkingOn = 0;
   int nsubs = -NoSubLevels;
   for (int sub = nsubs; sub < 0; ++sub)
   {
      Level* level = new Level (sub, 396, sub, 396, this);
      mLevels.push_back (level);
   }
   Lobby* lobby = new Lobby (396-36, 796+72, 0, this);   // 36 here is the awning width
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
   //while (index > mLevels.size())
   //   NewLevel(400,(int)mLevels.size(),724);
   if(( index >= mLevels.size() )||( index < 0))
   {
      return NULL;
   }
   return mLevels[index];
}

Level* Tower::FindLevelById(int id)
{
    for (auto pLevel : mLevels) {
        if (pLevel->GetID() == id) return pLevel;
    }
    return nullptr;
}

Level* Tower::FindLevel(int level)
{
    for (auto pLevel : mLevels) {
        if (pLevel->GetLevel() == level) return pLevel;
    }
    return nullptr;
}

void Tower::Update (float dt, int timeOfDay)
{
//   std::vector<Level *>::iterator iLevel;
//   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
//   {
//      (*iLevel)->Update( dt, timeOfDay );
//   }
   mFloorWorkingOn++;
   if( mFloorWorkingOn >= mLevels.size() )
   {
      mFloorWorkingOn = 0; // set to lowest level
   }
   else
   {
      Level* pLevel = mLevels[mFloorWorkingOn];
      pLevel->Update (dt, timeOfDay);
      this->AdjustFunds (pLevel->GetRentCollected());
   }
   mRoutes.Update( 10, timeOfDay );
   mGhostRoom.GetLevel();
   mGhostRoom.Update (this);

}

void Tower::Draw ()
{
   std::vector<Level *>::iterator iLevel;
   for (iLevel = mLevels.begin (); iLevel != mLevels.end (); ++iLevel)
   {
      (*iLevel)->Draw( );
   }
   mGhostRoom.Draw();
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
