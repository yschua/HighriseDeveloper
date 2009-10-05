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

#include <map>
#include <list>
#include <vector>
#include <iostream>
#include "Routes.h"
#include "FloorBase.h"
#include "Level.h"
#include "Tower.h"
#include "Office.h"
#include "Apartment.h"
#include "SingleStair.h"
#include "BuildStrategies.h"

using namespace TowerObjects;

// no tool active
bool BuildStategyBase::BuildHere (Tower* pTower, int x, int level)
{
   return false;  // no tool selection
}
void BuildStategyBase::ShowGhostBuild(Tower* pTower)
{
}


// Offices
bool BuildOfficeStategy::BuildHere (Tower* pTower, int x, int level)
{
   // we don't have multi tower support yet but this will eventually deal with that
   Level* pLevel = pTower->GetLevel(level);

   // test code until the snap to grid alligns the rooms
   int lx = 0;//pLevel->GetX();
   int xx = lx + x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new Office(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildOfficeStategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseOffice);
   GR.SetWidth (8);
}


// Apartments
bool
BuildApartmentStategy::BuildHere (Tower* pTower, int x, int level)
{
//         Apartment* new_apt = new Apartment (x, level, this);
   Level* pLevel = pTower->GetLevel(level);

   // test code until the snap to grid alligns the rooms
   int lx = 0;//pLevel->GetX();
   int xx = lx + x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new Apartment(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildApartmentStategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (8);
}


bool BuildStairStategy::BuildHere (Tower* pTower, int x, int level)
{
   Level* pLevel = pTower->GetLevel(level);
   int lx = 0;//pLevel->GetX();
   int xx = lx + x * Level::mUnitSize; // not complete

   SingleStair* pStair = new SingleStair( xx, level, level+1, pTower );
   pTower->GetRouteList().push_back( pStair );
   return true;
}

void BuildStairStategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseStair);
   GR.SetWidth (3);
}

// Condos

bool BuildCondoStategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildCondoStategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (12);
}


// select and drag
// build lobby
// build elevator
// build stairs

