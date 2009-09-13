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

#include "../Tower/level.h"
#include "../Tower/floorBase.h"
#include "floorAgent.h"

FloorAgent::FloorAgent ( Level* level )
      :  mLevel( level )
{

}

FloorAgent::~FloorAgent ()
{

}

bool FloorAgent::AddFloorSpace (FloorBase* pFS, int x, int x2 )
{
   if (mLevel->TestForEmptySpace (x, x2))
   {
      pFS->SetX ((float)x);
      pFS->SetX2 ((float)x2);
      mLevel->AddFloor (pFS);
   }
   return true;
}
