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
#include "../physics.h"
#include "../routes.h"
#include "tower.h"
#include "../scene.h"
#include "floorBase.h"

//using namespace Gfx;
unsigned int FloorBase::NextID = 1;


void
FloorBase::Update (float dt)
{
   std::cout << "Floor base class: update function called" << std::endl;
}

void
FloorBase::Draw ()
{
   std::cout << "Floor base class: Draw function called" << std::endl;
}

FloorBase::FloorBase (int x, int x2, int level, Tower* pTowerParent)
      :  mX ((float)x)
      ,  mX2 ((float)x2)
      ,  mTowerParent (pTowerParent)
{
   mLevel = level;
   mY = (float)(mLevel * -36);
   mZ = -0.5f;
   mID = FloorBase::GetNextID();
   pTowerParent->GetScene().RegisterFloorSpace (mID, this);
}

int FloorBase::GetNextID() // static
{
   return NextID++;
}
