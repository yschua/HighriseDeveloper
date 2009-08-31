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
#include <cstdlib>
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "image.h"
#include "physics.h"
#include "animation.h"
#include "tiler.h"

#include "routeBase.h"
#include "elevator.h"
#include "elevatorBase.h"

using namespace Graphics;

C_ElevatorBase::C_ElevatorBase ( int x, int level, C_Elevator* pElevator )
{
   m_x = x;
   m_y = 0;
   m_Level = level;
   m_pParent = pElevator;
   C_ImageManager * image_man = C_ImageManager::GetInstance ();
}

C_ElevatorBase::~C_ElevatorBase()
{
}

void
C_ElevatorBase::Update (float dt)
{

}

void
C_ElevatorBase::Draw ()
{
//    C_Camera::GetInstance()->Draw (*m_animations[m_current_state]);
}
