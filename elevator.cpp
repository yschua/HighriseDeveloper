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
#include "elevatorMachine.h"
#include "elevatorShaft.h"
#include "elevatorPit.h"
#include "elevator.h"

// this object is the elevator collection (Machines, Shaft, Pit) and the car.
// At this time there is no LiftCar class.

C_Elevator* C_Elevator::Create( Lift_Styles style, int x, int level )
{
   return new C_Elevator( style, x, level );
}

C_Elevator::C_Elevator ( Lift_Styles style, int x, int level)
:  m_LiftStyle( style )
,  m_LiftOperation( LOS_Waiting )
{
   m_X = x;
   m_Level = level;
   C_ImageManager * image_man = C_ImageManager::get_instance ();
}

C_Elevator::~C_Elevator()
{
};

void
C_Elevator::update (float dt)
{

}

void
C_Elevator::draw ()
{
//    C_Camera::get_instance()->draw (*m_animations[m_current_state]);
}
