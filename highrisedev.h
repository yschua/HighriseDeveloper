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

// #DEFINES moved to resource.h until we get a platform ind resouce file.
//#define HR_VERSION "0.0.1 ULTRABETA"
#include "resources.h"

// Include libraries first
#include <utility>
#include <cstring>
#include <iostream>
#include <list>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

// Then user-defined types
#include "Types/Rect.h"
#include "Types/Vector2.h"

#include "highriseException.h"

#include "physics.h"
#include "animation.h"
#include "tiler.h"
#include "image.h"
#include "camera.h"
#include "routes.h"
#include "background.h"

#include "tower/floorBase.h"
#include "tower/routeBase.h"  // Elevators route (levels).
#include "tower/apartment.h"
#include "tower/office.h"
#include "tower/elevatorBase.h"
#include "tower/elevatorMachine.h"
#include "tower/elevatorShaft.h"
#include "tower/elevatorPit.h"
#include "tower/elevator.h"
#include "tower/level.h"
#include "tower/lobby.h"
#include "tower/tower.h"

#include "person.h"

#include "citizens.h"
#include "routeVisitor.h"  // class that will Update the elevators route request queue

#include "interface.h"
