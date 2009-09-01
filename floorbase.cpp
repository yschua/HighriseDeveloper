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
C_FloorBase::Update (float dt)
{
   std::cout << "Floor base class: update function called" << std::endl;
}

void
C_FloorBase::Draw ()
{
   std::cout << "Floor base class: Draw function called" << std::endl;
}

C_FloorBase::C_FloorBase (int x, int x2, int level, C_Tower * TowerParent)
      :  m_x (x)
      ,  m_x2 (x2)
      ,  m_TowerParent (TowerParent)
{
   m_level = level;
   m_y = (Camera::GetInstance()->GetWorldY () ) - (m_level * 36);
}
