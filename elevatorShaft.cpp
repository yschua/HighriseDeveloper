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

C_ElevatorShaft::C_ElevatorShaft ( int x, int topLevel, int bottomLevel, C_Elevator* pElevator )
:  C_ElevatorBase( x, bottomLevel, pElevator )
{
   m_X = x;
   m_TopLevel = topLevel;
   m_BottomLevel = bottomLevel;
   C_ImageManager * images = C_ImageManager::get_instance ();
   m_cam = C_Camera::get_instance ();
   m_ShaftTiler = new C_Tiler (images->get_image ("liftshaft.png"), C_Tiler::Vertical, 
                              m_cam->get_world_y () - (m_TopLevel * 36), 
                              m_cam->get_world_y () - ((m_BottomLevel - 1) * 36), m_X );
}

C_ElevatorShaft::~C_ElevatorShaft()
{
}

void
C_ElevatorShaft::update (float dt)
{

}

void
C_ElevatorShaft::draw ()
{
   m_cam->draw (*m_ShaftTiler);
}
