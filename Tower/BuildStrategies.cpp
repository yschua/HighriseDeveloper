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

#include "../Window/Event.h"
#include "Routes.h"
#include "FloorBase.h"
#include "Level.h"
#include "Tower.h"
#include "Condo.h"
#include "Office.h"
#include "Security.h"
#include "Apartment.h"
#include "HotelRoom.h"
#include "Housekeeping.h"
#include "RetailShop.h"
#include "SingleStair.h"
#include "MedicalClinic.h"
#include "WasteManagement.h"
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

BuildStrategyBase* BuildStrategyBase::CreateStrategy(int toolID, Tower* pTower)
{
   BuildStrategyBase* pBuildStrategy = NULL;
   switch (toolID)
   {
   case HR_PlaceOffice:
      pBuildStrategy = new BuildRoomStrategy<Office>(8,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceApartment:
      pBuildStrategy = new BuildRoomStrategy<Apartment>(8,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;
   case HR_PlaceCondo:
      pBuildStrategy = new BuildRoomStrategy<Condo>(14,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;
   case HR_PlaceHotelSingle:
      pBuildStrategy = new BuildRoomStrategy<HotelRoom>(6,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceHotelDouble:
      pBuildStrategy = new BuildRoomStrategy<HotelRoom>(7,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceHotelKing:
      pBuildStrategy = new BuildRoomStrategy<HotelRoom>(8,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceHotelSuite:
      pBuildStrategy = new BuildRoomStrategy<HotelRoom>(9,1); // luxury suite
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceSecurity:
      pBuildStrategy = new BuildRoomStrategy<Security>(12,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceHouseKeeping:
      pBuildStrategy = new BuildRoomStrategy<Housekeeping>(12,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceClinic:
      pBuildStrategy = new BuildRoomStrategy<MedicalClinic>(14,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceRestaurant:
      //pBuildStrategy = new BuildRoomStrategy<Restaurant>(12,1);
      //pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceRetail:
      pBuildStrategy = new BuildRoomStrategy<RetailShop>(10,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceStairs:
      pBuildStrategy = new BuildRouteStrategy<SingleStair>(3,1);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;

   case HR_PlaceWasteManagement:
      pBuildStrategy = new BuildRoomStrategy<WasteManagement>(16,2);
      pBuildStrategy->ShowGhostBuild (pTower);
      break;
   }
   //case HR_PlaceServices:
   //   pBuildStrategy = new BuildRoomStrategy<Housekeeping>(12,1);
   //   pBuildStrategy->ShowGhostBuild (pTower);
   //   bResult = true;
   //   break;

   //case HR_PlaceTheater:
   //   pBuildStrategy = new BuildRoomStrategy<Clinic>(0,1);
   //   pBuildStrategy->ShowGhostBuild (pTower);
   //   bResult = true;
   //   break;

   return pBuildStrategy;
}
