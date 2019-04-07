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

#include <iostream>
#include <map>
#include "../Root/SerializerBase.h"
#include "../Window/Event.h"
#include "FloorBase.h"
#include "Tower.h"

#include "BuildData.h"
#include "BuildStrategies.h"
#include "BuildFactory.h"
#include "BuildRemoveStrategy.h"

namespace TowerObjects
{
   BuildFactory* BuildFactory::mInstance = NULL;
}

using namespace TowerObjects;

BuildFactory::BuildFactory ()
{
}

BuildFactory* BuildFactory::GetInstance ()
{
   if (mInstance == NULL)
   {
      mInstance = new BuildFactory ();
   }
   return mInstance;
}

void BuildFactory::Register(BuildData* bd)
{
   mBuildTypes.insert(std::pair<int,BuildData*>(bd->BuildType, bd));
}

BuildStrategyBase* BuildFactory::CreateStrategy( int ToolID, Tower* pTower )
{
   BuildStrategyBase* pBS = NULL;
   BuildTypeIterator itBuild = mBuildTypes.find(ToolID);
   if (itBuild == mBuildTypes.end())
   {
       if (ToolID == HR_Remove) {
           pBS = BuildStrategyBase::CreateStrategy(nullptr, pTower);
       } else {
           BuildData dummy;
           pBS = BuildStrategyBase::CreateStrategy(&dummy, pTower);
       }
   }
   else
   {
      pBS = BuildStrategyBase::CreateStrategy(itBuild->second, pTower);
   }
   return pBS;
}

void BuildFactory::Save (SerializerBase& ser)
{
   BuildTypeIterator itBuild;
   for( itBuild = mBuildTypes.begin(); itBuild != mBuildTypes.end(); itBuild++)
   {
      SerializerBase* pSer = ser.Spawn("BuildTemplate");
      BuildData *bd = itBuild->second;
      bd->Save(*pSer);
      delete pSer;
   }
}

void BuildFactory::Load (SerializerBase& ser)
{
   SerializerBase* pSer = &ser;
   SerializerBase* pOldSer = NULL;
   while (pSer != NULL)
   {
      delete pOldSer;
      BuildData* pBD = new BuildData(pSer);
      Register (pBD);
      SerializerBase* pOldSer = pSer;
      pSer = pOldSer->GetNextSibling("BuildTemplate");
   }
   // pSer will have already been deleted in the while loop
}

void BuildFactory::Default() // developers eddition
{
   BuildData* pbd;
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceOffice,8,1, 40000, 0, 100);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceApartment,8,1, 30000, 0, 50);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceCondo,14,1, 100000, 500000, 10);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceHotelSingle,6,1, 20000, 0, 10);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceHotelDouble,7,1, 25000, 0, 15);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceHotelKing,8,1, 30000, 0, 20);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceHotelSuite,9,1, 50000, 0, 30); // luxury suite *CHEAP*
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceSecurity,12,1, 250000, 0, -100);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceHouseKeeping,12,1, 125000, 0, -50);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceClinic,14,1, 500000, 0, -200);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceRestaurant,12,1, 200000, 0, 1500);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceRetail,10,1, 100000, 0, 1000);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceStairs,3,1, 0, 0, 0);//, 5000);
   Register (pbd);
   pbd = new BuildData();
   pbd->SetDefault( HR_PlaceWasteManagement,16,2, 750000, 0, -200);
   Register (pbd);
}