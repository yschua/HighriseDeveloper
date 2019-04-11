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

// When a new floor space object is added, it needs to be built, detailed and rented or sold.
// This code will also have to release spaces when tenants move out.

#include <vector>
#include <list>
#include <algorithm>

#include "../Tower/Level.h"
#include "../Tower/FloorBase.h"
#include "../Tower/Office.h"
#include "../Tower/Tower.h"
#include "../People/Person.h"
#include "FloorAgent.h"

FloorAgent::FloorAgent(Tower& tower) : mTower(tower) {}

FloorAgent::~FloorAgent() {}

bool FloorAgent::AddFloorSpace(FloorBase* pFS, int x, int x2, int y)
{
    Level* pLevel = mTower.GetLevel(y);
    if (pLevel->TestForEmptySpace(x, x2)) {
        pFS->SetX((float)x);
        pFS->SetX2((float)x2);
        pLevel->AddFloorSpace(pFS);
    }
    return true;
}

FloorBase* FloorAgent::FindWork(int preferences)
{
    Level::FloorIterType fit;
    Tower::LevelIterator lit;
    Tower::LevelVector& levels = mTower.GetLevels();
    for (lit = levels.begin(); lit != levels.end(); lit++) {
        Level* pLevel = (*lit);
        Level::FloorMap& rooms = pLevel->GetFloorSpaces();
        for (fit = rooms.begin(); fit != rooms.end(); fit++) {
            FloorBase* pRoom = (*fit).second;
            if (pRoom->GetType() ==
                BaseOffice) //&& !pRoom->IsVacant()) employers will move in ans open the office for hire
            {
                Office* pOffice = reinterpret_cast<Office*>(
                    pRoom); // Base class is really and office so rinterpret it as Office
                if (pOffice->PeopleApply()) {
                    return pRoom;
                }
            }
        }
    }
    return NULL;
}

FloorBase* FloorAgent::FindAHome(int preferences)
{
    Level::FloorIterType fit;
    Tower::LevelIterator lit;
    Tower::LevelVector& levels = mTower.GetLevels();
    for (lit = levels.begin(); lit != levels.end(); lit++) {
        Level* pLevel = (*lit);
        Level::FloorMap& rooms = pLevel->GetFloorSpaces();
        for (fit = rooms.begin(); fit != rooms.end(); fit++) {
            FloorBase* pRoom = (*fit).second;
            if (preferences == 1) {
                if (pRoom->GetType() == BaseCondo && pRoom->IsVacant()) {
                    return pRoom;
                }
            } else {
                if (pRoom->GetType() == BaseApartment && pRoom->IsVacant()) {
                    return pRoom;
                }
            }
        }
    }
    return NULL;
}

FloorBase* FloorAgent::FindAHotel(int preferences)
{
    FloorBase* pRoom = NULL;
    return pRoom;
}
