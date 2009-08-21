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
#include "physics.h"
#include "animation.h"
#include "tiler.h"
#include "camera.h"
#include "image.h"

#include "elevatorBase.h"
#include "elevatorMachine.h"


C_ElevatorMachine::C_ElevatorMachine (int x, int level, C_Elevator* pElevator )
:  C_ElevatorBase( x, level, pElevator )
,  m_State( LMS_Idle )
{
   C_ImageManager * image_man = C_ImageManager::get_instance ();
   m_y = (C_Camera::get_instance()->get_world_y () ) - (level * 36);
   std::cout << "New elevator machine at " << m_x << ", " << m_y << std::endl;
   m_LifterAnimation = new C_Animation ();
   m_LifterAnimation->add_frame (image_man->get_image ("liftMachine_1.png"), 1000);
   m_LifterAnimation->add_frame (image_man->get_image ("liftMachine_2.png"), 1000);
   m_LifterAnimation->add_frame (image_man->get_image ("liftMachine_3.png"), 1000);
   m_ImageFrame = 0;
   m_FirstFrame = 0;
   m_LastFrame = 2;
   m_cam = C_Camera::get_instance ();
   m_y = ( m_cam->get_world_y ()) - (level * 36);
   pos_calc();
}

C_ElevatorMachine::~C_ElevatorMachine()
{
   delete m_LifterAnimation;
}

void
C_ElevatorMachine::pos_calc ()
{
   m_LifterAnimation->set_position ((float)m_x, (float)(m_y) ); // elevator sprite is only 32x32
}

void
C_ElevatorMachine::update (float dt)
{
   switch (m_State)
   {
      case LMS_Down :
         m_Direction = -1;
      break;
      case LMS_Up :
         m_Direction = 1;
      break;
      case LMS_Idle :
         m_Direction = 0;
      break;
   }
   m_ImageFrame += m_Direction;
   if( m_ImageFrame < 0 )
      m_ImageFrame = m_LastFrame;
   if( m_ImageFrame > m_LastFrame )
      m_ImageFrame = m_FirstFrame;
   m_LifterAnimation->update (dt);
}

void
C_ElevatorMachine::draw ()
{
   this->m_cam->draw( * m_LifterAnimation );
}
