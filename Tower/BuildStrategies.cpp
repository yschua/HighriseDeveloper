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

#include "BuildStrategies.h"

#include "../Window/Event.h"
#include "Apartment.h"
#include "BuildData.h"
#include "BuildRemoveStrategy.h"
#include "Condo.h"
#include "FloorBase.h"
#include "HotelRoom.h"
#include "Housekeeping.h"
#include "Level.h"
#include "MedicalClinic.h"
#include "Office.h"
#include "RetailShop.h"
#include "Routes.h"
#include "Security.h"
#include "SingleStair.h"
#include "Tower.h"
#include "WasteManagement.h"

#include <iostream>
#include <list>
#include <map>
#include <vector>

using namespace TowerObjects;

// no tool active
bool BuildStrategyBase::BuildHere(Tower* pTower, int x, int level)
{
    return false; // no tool selection
}
void BuildStrategyBase::ShowGhostBuild(Tower* pTower) {}

BuildStrategyBase* BuildStrategyBase::CreateStrategy(BuildData* pBuildData, Tower* pTower)
{
    BuildStrategyBase* pBuildStrategy = NULL;

    if (pBuildData == nullptr) {
        BuildData dummy;
        pBuildStrategy = new BuildRemoveStrategy(dummy);
        pBuildStrategy->ShowGhostBuild(pTower);
        return pBuildStrategy;
    }

    int iUnits = pBuildData->UnitsWide;
    int iLevels = pBuildData->LevelsHigh;
    double dCost = pBuildData->BuildCost;

    switch (pBuildData->BuildType) {
    case HR_PlaceOffice:
        pBuildStrategy = new BuildRoomStrategy<Office>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceApartment:
        pBuildStrategy = new BuildRoomStrategy<Apartment>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;
    case HR_PlaceCondo:
        pBuildStrategy = new BuildRoomStrategy<Condo>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;
    case HR_PlaceHotelSingle:
        pBuildStrategy = new BuildRoomStrategy<HotelRoom>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceHotelDouble:
        pBuildStrategy = new BuildRoomStrategy<HotelRoom>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceHotelKing:
        pBuildStrategy = new BuildRoomStrategy<HotelRoom>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceHotelSuite:
        pBuildStrategy = new BuildRoomStrategy<HotelRoom>(*pBuildData); // luxury suite
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceSecurity:
        pBuildStrategy = new BuildRoomStrategy<Security>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceHouseKeeping:
        pBuildStrategy = new BuildRoomStrategy<Housekeeping>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceClinic:
        pBuildStrategy = new BuildRoomStrategy<MedicalClinic>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceRestaurant:
        // pBuildStrategy = new BuildRoomStrategy<Restaurant>(*pBuildData);
        // pBuildStrategy->ShowGhostBuild (pTower);
        break;

    case HR_PlaceRetail:
        pBuildStrategy = new BuildRoomStrategy<RetailShop>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceStairs:
        pBuildStrategy = new BuildRouteStrategy<SingleStair>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;

    case HR_PlaceWasteManagement:
        pBuildStrategy = new BuildRoomStrategy<WasteManagement>(*pBuildData);
        pBuildStrategy->ShowGhostBuild(pTower);
        break;
    }
    // case HR_PlaceServices:
    //   pBuildStrategy = new BuildRoomStrategy<Housekeeping>(12,1, 650000);
    //   pBuildStrategy->ShowGhostBuild (pTower);
    //   bResult = true;
    //   break;

    // case HR_PlaceTheater:
    //   pBuildStrategy = new BuildRoomStrategy<Clinic>(0,1, 1500000); /// 1.5mil
    //   pBuildStrategy->ShowGhostBuild (pTower);
    //   bResult = true;
    //   break;

    return pBuildStrategy;
}
