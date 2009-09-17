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
#include <vector>
#include "../routes.h"
#include "floorBase.h"
#include "tower.h"
#include "office.h"
#include "apartment.h"
#include "buildStrategies.h"

// no tool active
bool BuildStategyBase::BuildHere (Tower* pTowwer, int x, int y)
{
   return false;  // no tool selection
}

// Offices
bool BuildOfficeStategy::BuildHere (Tower* pTowwer, int x, int y)
{
   return true;
}

// Apartments
bool
BuildApartmentStategy::BuildHere (Tower* pTowwer, int x, int y)
{
   return true;
}

// Condos
bool
BuildCondoStategy::BuildHere (Tower* pTowwer, int x, int y)
{
   return true;
}

// select and drag
// build lobby
// build elevator
// build stairs

