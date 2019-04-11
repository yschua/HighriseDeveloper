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

#include "BuildRemoveStrategy.h"
#include <iostream>
#include "Tower.h"

BuildRemoveStrategy::BuildRemoveStrategy(BuildData& rBuildData) : BuildStrategyBase(rBuildData)
{
    mType = BaseEmpty;
}

BuildRemoveStrategy::~BuildRemoveStrategy() {}

bool BuildRemoveStrategy::PlacingRoom()
{
    return false;
}

bool BuildRemoveStrategy::BuildHere(Tower* pTower, int x, int y)
{
    auto pLevel = pTower->GetLevel(y);
    auto pRoom = pLevel->FindSpace(x * Level::mUnitSize);

    if (pRoom == nullptr)
        return false;

    pLevel->RemoveFloorSpace(pRoom);
    return true;
}

void BuildRemoveStrategy::ShowGhostBuild(Tower* pTower)
{
    auto& ghostRoom = pTower->GetGhostRoom();
    ghostRoom.SetShownType(BaseEmpty);
    ghostRoom.SetWidth(1);
}
