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

#ifndef _BUILDSTRATEGIES_H
#define _BUILDSTRATEGIES_H
#include <string>
#include <map>

#include "BuildData.h"
#include "Level.h"

class Tower;
struct BuildData;

// these are hard coded now but will be modifiable
class BuildStrategyBase
{
protected:
    BaseType mType; // Office, Apt, Condo
    // subtype maybe, reception, cubes, datacente, boardroom (offices) or luxury/studio apt.
    BuildData& mBuildData;
    BuildStrategyBase(BuildData& rBuildData) : mBuildData(rBuildData) {}

public:
    static BuildStrategyBase* CreateStrategy(BuildData* pBuildData, Tower* pTower);
    BuildData& GetBuildData() { return mBuildData; }

public:
    virtual bool PlacingRoom() { return false; }
    virtual bool BuildHere(Tower* pTowwer, int x, int y);
    virtual void ShowGhostBuild(Tower* pTower);
};

// crazy2be
// changed strategy classes to a template class
// Generic template implementation for rooms
template <class T>
class BuildRoomStrategy : public BuildStrategyBase
{
public:
    BuildRoomStrategy(BuildData& rBuildData) : BuildStrategyBase(rBuildData) { mType = T::GetBaseType(); }
    bool BuildHere(Tower* pTower, int x, int y)
    {
        // we don't have multi tower support yet but this will eventually deal with that
        Level* pLevel = pTower->GetLevel(y);
        double dCash = pTower->GetAvailableFunds();
        if (dCash < mBuildData.BuildCost)
            return false;

        int xx = x * Level::mUnitSize;
        bool bAvail = pLevel->IsSpaceEmpty(xx, xx + mBuildData.UnitsWide * Level::mUnitSize);
        if (bAvail) {
            FloorBase* pRoom =
                new T(xx, y, pTower); // OnToolHit is going to set this up, when we hit the floor
            pRoom->SetRent(mBuildData.RentalCost);
            pRoom->SetSalePrice(mBuildData.PurchasePrice);
            pLevel->AddFloorSpace(pRoom);
            pTower->AdjustFunds(-mBuildData.BuildCost);
        }
        return true;
    }
    virtual bool PlacingRoom() { return true; }
    virtual void ShowGhostBuild(Tower* pTower)
    {
        GhostRoom& GR = pTower->GetGhostRoom();
        GR.SetShownType(mType);
        GR.SetWidth(mBuildData.UnitsWide);
    }
};

template <class T>
class BuildRouteStrategy : public BuildStrategyBase
{
public:
    BuildRouteStrategy(BuildData& rBuildData) : BuildStrategyBase(rBuildData) { mType = T::GetBaseType(); }
    bool BuildHere(Tower* pTower, int x, short BottomLevel, short TopLevel)
    {
        // we don't have multi tower support yet but this will eventually deal with that
        Level* pBottomLevel = pTower->GetLevel(BottomLevel);
        Level* pTopLevel = pTower->GetLevel(TopLevel);
        double dCash = pTower->GetAvailableFunds();
        if (dCash < this->mCost)
            return false;

        int xx = x * Level::mUnitSize;
        // Shouldn't we have a dedicated function for checking if transport can be placed here?
        // in the original, it's on a different "layer"
        bool bAvail = true;
        for (int i = BottomLevel; i < TopLevel; i++) {
            Level* pLevel = pTower->GetLevel(i);
            /*         if (!pBottomLevel->IsSpaceEmpty (xx, xx + mWidth * Level::mUnitSize))
                     {
                        bAvail = false;
                        break;
                     }*/
        }

        if (bAvail) {
            RouteBase* pRoom = new T(xx,
                                     BottomLevel,
                                     TopLevel,
                                     pTower); // OnToolHit is going to set this up, when we hit the floor
            //         pLevel->mRAddFloorSpace (pRoom);
        }
        return true;
    }
    virtual bool PlacingRoom() { return false; }
    virtual void ShowGhostBuild(Tower* pTower)
    {
        GhostRoom& GR = pTower->GetGhostRoom();
        GR.SetShownType(mType);
        GR.SetWidth(mBuildData.UnitsWide);
    }
};

#endif // _BUILDSTRATEGIES_H
