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

#include "highrisedev.h"

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

FloorBase::FloorBase (int x, int x2, int level, Tower * TowerParent)
      :  mX (x)
      ,  mX2 (x2)
      ,  mTowerParent (TowerParent)
{
   mLevel = level;
   mY = (Camera::GetInstance()->GetWorldY () ) - (mLevel * 36);
}
