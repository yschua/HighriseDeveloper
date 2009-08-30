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
#include "elevatorPit.h"

class C_Elevator;

C_ElevatorPit::C_ElevatorPit ( int x, int level, C_Elevator* pElevator )
      :  C_ElevatorBase( x, level, pElevator )
{
   m_x = x;
   m_Level = level;
   //C_ImageManager * image_man = C_ImageManager::GetInstance ();
   m_y = (C_Camera::GetInstance()->GetWorldY () ) - (level * 36);
   // std::cout << "New elevator pit at " << m_x << ", " << m_y << std::endl;
   // m_animations[s_occupied_day] = new C_AnimationSingle ();
   // m_animations[s_occupied_day]->AddFrame (image_man->GetImg ("liftpit.png"), 1000);
}

C_ElevatorPit::~C_ElevatorPit()
{
}

void
C_ElevatorPit::Update (float dt)
{

}

void
C_ElevatorPit::Draw ()
{
//    C_Camera::GetInstance()->Draw (*m_animations[m_current_state]);
}
