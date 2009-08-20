/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib> 
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "animation.h"
#include "tiler.h"
#include "camera.h"
#include "image.h"

#include "elevatorBase.h"
#include "ElevatorShaft.h"

C_ElevatorShaft::C_ElevatorShaft ( int x, int level, C_Elevator* pElevator )
:  C_ElevatorBase( x, level, pElevator )
{
   m_X = x;
   m_Level = level;
   C_ImageManager * image_man = C_ImageManager::get_instance ();
}

C_ElevatorShaft::~C_ElevatorShaft()
{
};

void
C_ElevatorShaft::update (float dt)
{

}

void
C_ElevatorShaft::draw ()
{
//    C_Camera::get_instance()->draw (*m_animations[m_current_state]);
}
