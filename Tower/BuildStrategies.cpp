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
#include "Security.h"
#include "Apartment.h"
#include "HotelRoom.h"
#include "Housekeeping.h"
#include "SingleStair.h"
#include "MedicalClinic.h"
#include "BuildStrategies.h"

using namespace TowerObjects;

// no tool active
bool BuildStrategyBase::BuildHere (Tower* pTower, int x, int level)
{
   return false;  // no tool selection
}
void BuildStrategyBase::ShowGhostBuild(Tower* pTower)
{
}

// Offices
bool BuildOfficeStrategy::BuildHere (Tower* pTower, int x, int level)
{
   // we don't have multi tower support yet but this will eventually deal with that
   Level* pLevel = pTower->GetLevel(level);

   int xx = x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new Office(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildOfficeStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseOffice);
   GR.SetWidth (8);
}

// Apartments
bool
BuildApartmentStrategy::BuildHere (Tower* pTower, int x, int level)
{
//         Apartment* new_apt = new Apartment (x, level, this);
   Level* pLevel = pTower->GetLevel(level);

   int xx = x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new Apartment(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildApartmentStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (8);
}


// Hotel
bool BuildHotelStrategy::BuildHere (Tower* pTower, int x, int level)
{
   Level* pLevel = pTower->GetLevel(level);

   int xx = x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new HotelRoom(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildHotelStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseHotel);
   GR.SetWidth (6);
}

bool BuildStairStrategy::BuildHere (Tower* pTower, int x, int level)
{
   Level* pLevel = pTower->GetLevel(level);
   int xx = x * Level::mUnitSize; // not complete

   SingleStair* pStair = new SingleStair( xx, level, level+1, pTower );
   pTower->GetRouteList().push_back( pStair );
   return true;
}

void BuildStairStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseStair);
   GR.SetWidth (3);
}

// Condos

bool BuildCondoStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildCondoStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (12);
}

bool BuildHousekeepingStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildHousekeepingStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (12);
}

bool BuildServiceStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildServiceStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (10);
}

bool BuildSecurityStrategy::BuildHere (Tower* pTower, int x, int level)
{
   Level* pLevel = pTower->GetLevel(level);

   int xx = x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new Security(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}

void BuildSecurityStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseSecurity);
   GR.SetWidth (14);
}

bool BuildClinicStrategy::BuildHere (Tower* pTower, int x, int level)
{
   Level* pLevel = pTower->GetLevel(level);

   int xx = x * Level::mUnitSize;
   bool bAvail = pLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize);
   if (bAvail)
   {
      FloorBase* pRoom = new MedicalClinic(xx, level, pTower); //OnToolHit is going to set this up, when we hit the floor
      pLevel->AddFloorSpace (pRoom);
   }
   return true;
}
void BuildClinicStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseClinic);
   GR.SetWidth (16);
}

bool BuildWasteManagementStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildWasteManagementStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (18);
}
bool BuildRetailStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildRetailStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (10);
}
 
bool BuildRestaurantStrategy::BuildHere (Tower* pTower, int x, int level)
{
   return true;
}

void BuildRestaurantStrategy::ShowGhostBuild (Tower* pTower)
{
   GhostRoom& GR = pTower->GetGhostRoom();
   GR.SetShownType( BaseResidence);
   GR.SetWidth (14);
}

// select and drag
// build lobby
// build elevator

