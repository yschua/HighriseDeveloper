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
#include "BuildStrategies.h"

// no tool active
bool BuildStategyBase::BuildHere (Tower* pTower, int x, int level)
{
   return false;  // no tool selection
}

// Offices
bool BuildOfficeStategy::BuildHere (Tower* pTower, int x, int level)
{
   // we don't have multi tower support yet but this will eventually deal with that
   Level* pLevel = pTower->GetLevel(level);

   // test code until the snap to grid alligns the rooms
   int lx = pLevel->GetX();
   for (int ix = -3; ix < 4; ++ix )
   {
      int xx = lx + (ix + x) * 9;
      bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * 9);
      if (bAvail)
      {
         FloorBase* pRoom = new Office(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
         //pRoom->SetX (x + (lx * 9));
         //pRoom->SetX2 (x + (lx + mWidth * 9));
         pLevel->AddFloorSpace (pRoom);
         //int* blah = NULL;
         //int some = *blah;
         //std::cout << "stshfkjdhflkfjhsdlkfs\n";
         break;
      }
   }
   return true;
}

// Apartments
bool
BuildApartmentStategy::BuildHere (Tower* pTower, int x, int level)
{
//         Apartment* new_apt = new Apartment (x, level, this);
   Level* pLevel = pTower->GetLevel(level);

   // test code until the snap to grid alligns the rooms
   int lx = pLevel->GetX();
   for (int ix = -3; ix < 4; ++ix )
   {
      int xx = lx + (ix + x) * 9;
      bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * 9);
      if (bAvail)
      {
         FloorBase* pRoom = new Apartment(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
         //pRoom->SetX (x + (lx * 9));
         //pRoom->SetX2 (x + (lx + mWidth * 9));
         pLevel->AddFloorSpace (pRoom);
         break;
      }
   }
   return true;
}

// Condos
bool
BuildCondoStategy::BuildHere (Tower* pTowwer, int x, int y)
{
   return true;
}

// select and drag
// build lobby
// build elevator
// build stairs

