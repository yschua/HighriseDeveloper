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

#include "routeBase.h"
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
   m_Level = level;
   m_TopLevel = 3;
   m_BottomLevel = 0;
   m_Position = 0;
   m_Direction = 0;
   m_IdleTime = 30;

   C_ImageManager * images = C_ImageManager::get_instance ();
   m_ElevatorImage = new C_AnimationSingle (images->get_image ("elevator_u_s.png"));
   m_LiftPit = new C_AnimationSingle (images->get_image ("liftpit_1.png"));

   m_cam = C_Camera::get_instance ();
   m_X = x;
   m_Y = ( m_cam->get_world_y ()) - (level * 36);
   m_LiftMachine = new C_ElevatorMachine( x, m_TopLevel+1, this );
   m_LiftPit->set_position ((float)m_X, (float)(m_Y + 36) );
}

C_Elevator::~C_Elevator()
{
   delete m_ElevatorImage;
};

void
C_Elevator::pos_calc ()
{
   m_ElevatorImage->set_position ((float)m_X, (float)(m_Y - m_Position + 4) ); // elevator sprite is only 32x32
}

void
C_Elevator::update (float dt)
{
   int max = m_TopLevel * 36;
   int min = m_BottomLevel * 36;

   // test plug
   switch( m_Direction )
   {
   case 0:
      if( m_IdleTime > 0 )
      {
         m_IdleTime--;
      }
      else
      {
         if( m_Position > m_BottomLevel+9 )
         {
            m_Direction = -1;
         }
         else
         {
            m_Direction = 1;
         }
      }
      break;
   case 1:
      if( m_Position < max )
      {
         m_Position++;
         m_LiftMachine->update( dt );
      }
      else
      {
         m_Direction = 0;
         m_IdleTime = 30;
      }
      break;
   case -1:
      if( m_Position > min )
      {
         m_Position--;
         m_LiftMachine->update( dt );
      }
      else
      {
         m_Direction = 0;
         m_IdleTime = 30;
      }
   }
   pos_calc();
}

void
C_Elevator::draw ()
{
   m_LiftMachine->draw();
   m_cam->draw (*m_LiftPit );
   m_cam->draw (*m_ElevatorImage);
}
