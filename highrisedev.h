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

#include <cstring>
#include <iostream>
#include <list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

#include "highriseException.h"

#include "physics.h"
#include "animation.h"
#include "tiler.h"
#include "image.h"
#include "camera.h"

#include "floorBase.h"
#include "routeBase.h"
#include "office.h"
#include "apartment.h"
#include "level.h"
#include "lobby.h"
#include "elevator.h"
#include "routes.h"
#include "background.h"
#include "person.h"
#include "tower.h"

#include "person.h"
#include "citizens.h"

#include "routeBase.h"  // Elevators route (levels).
#include "routeVisitor.h"  // class that will update the elevators route request queue
#include "elevatorBase.h"
#include "elevatorMachine.h"
#include "elevatorShaft.h"
#include "elevatorPit.h"
#include "elevator.h"
