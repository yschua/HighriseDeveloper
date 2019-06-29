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

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "../Root/HighRiseException.h"
#include "../Root/Physics.h"
#include "Apartment.h"
#include "Damage.h"
#include "../Routes/Elevator.h"
#include "../Routes/ElevatorBase.h"
#include "FloorBase.h"
#include "Level.h"
#include "Lobby.h"
#include "Office.h"
#include "../Routes/Routes.h"
#include "Tower.h"
#include "../AI/PathFinding.h"

#include <iostream>
#include <list>
#include <vector> // changed from list to vector so the collection can be scrolled in up and down
// This is a debug stub to load a building for early dev

void Tower::DebugLoad(int x, int y, int x2)
{
    try {
        // persist these
        Elevator* pElevator = new Elevator(Elevator::LS_Standard, 472, -1, 14, this);
        GetRoutes().AddRoute(pElevator);
        pElevator = new Elevator(Elevator::LS_Standard, 472 + 36 + 9, 15, 19, this);
        GetRoutes().AddRoute(pElevator);
        Level* pLevel = GetLevel(0);
        pElevator = new Elevator(Elevator::LS_HighCapacity, 472 + 144, 0, 15, this);
        GetRoutes().AddRoute(pElevator);
        m_pathFinding.ConstructGraph();
    } catch (...) {
        throw new HighriseException("Debug Alpha Building failed to create");
    }
}
