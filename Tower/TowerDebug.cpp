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
#include <vector> // changed from list to vector so the collection can be scrolled in up and down
#include <list>

#include "../xml/tinyxml/tinyxml.h"
#include "../Animation.h"
//#include "Tiler.h"
#include "../Image.h"
#include "../Routes.h"
#include "../Physics.h"
#include "ElevatorBase.h"
#include "Elevator.h"
#include "FloorBase.h"
#include "Level.h"
#include "Lobby.h"
#include "Apartment.h"
#include "Office.h"
#include "Damage.h"
#include "Tower.h"

#include "../HighRiseException.h"
// This is a debug stub to load a building for early dev

void
Tower::DebugLoad (int x, int y, int x2)
{
   try
   {
      // persist these
      Elevator* pElevator = new Elevator( Elevator::LS_Standard, 472, -1, 6, this );
      GetRoutes().AddRoute( pElevator );
      pElevator = new Elevator( Elevator::LS_Standard, 472 + 36 + 9, 0, 5, this );
      GetRoutes().AddRoute( pElevator );
      Level* pLevel = GetLevel(0);
      pLevel->AddRouteToQueue(GetRoutes().GetRoutes()[0]);
   }
   catch (...)
   {
      throw new HighriseException ("Debug Alpha Building failed to create");
   }
}

