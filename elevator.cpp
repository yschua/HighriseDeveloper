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
#ifdef WIN32
#include <cstring>
#include <cstdlib>
#include <map> 
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "camera.h"
#include "animation.h"
#include "tiler.h"

#include "routeBase.h"  // Elevators route (levels).
#include "routeVisitor.h"  // class that will Update the elevators route request queue
#include "elevatorBase.h"
#include "elevatorMachine.h"
#include "elevatorShaft.h"
#include "elevatorPit.h"
#include "elevator.h"

#else
#include "highrisedev.h"
#endif

using namespace Graphics;

// this object is the elevator collection (Machines, Shaft, Pit) and the car.
// At this time there is no LiftCar class.

//C_Elevator* C_Elevator::Create( Lift_Styles style, int x, short BottomLevel, short TopLevel, C_Tower * TowerParent )
//{
//   return new C_Elevator( style, x, BottomLevel, TopLevel, TowerParent );
//}

C_Elevator::C_Elevator ( Lift_Styles style, int x, short BottomLevel, short TopLevel, C_Tower * TowerParent)
      :  m_LiftStyle( style )
      ,  m_LiftOperation( LOS_Waiting )
      ,  m_TowerParent (TowerParent)
{
   m_TopLevel = (TopLevel);
   m_BottomLevel = (BottomLevel);
   m_Position = (m_BottomLevel + 1) * 36;
   m_Direction = 0;
   m_IdleTime = 30;
   m_End2 = -1;
   m_Offset = BottomLevel * -36;

   m_FloorCount = TopLevel - BottomLevel;
   m_RidersOnBoard = 0;
   memset( m_Riders, 0, sizeof(m_Riders) );
   ClearStops();
   memset( m_Stops, 0, sizeof(m_Stops) );


   // test code
   m_StartRoute = m_BottomLevel;
   m_EndRoute = m_TopLevel;

   C_ImageManager * images = C_ImageManager::GetInstance ();
   m_ElevatorImage = new C_AnimationSingle (images->GetImg ("elevator_u_s.png"));
   m_LiftPit = new C_AnimationSingle (images->GetImg ("liftpit_1.png"));

   m_cam = C_Camera::i();
   m_X = x;
   m_Y = ( m_cam->GetWorldY ()) - (m_BottomLevel * 36);
   m_LiftMachine = new C_ElevatorMachine( x, m_TopLevel+1, this );
   m_LiftPit->SetPosition ((float)m_X, (float)(m_Y + 36) );
   m_ElevatorShaft = new C_ElevatorShaft( m_X, m_TopLevel, m_BottomLevel, this );
}

C_Elevator::~C_Elevator()
{
   delete m_ElevatorImage;
};

void
C_Elevator::ClearStops()
{
   memset( m_Stops, 0, sizeof(m_Stops) );
}

void
C_Elevator::PosCalc ()
{
   m_ElevatorImage->SetPosition ((float)m_X, (float)(m_Y - (m_Offset + m_Position) + 4) ); // elevator sprite is only 32x32
}

void
C_Elevator::SetRoute( C_RouteVisitor* visitor )
{
   if ( m_StartRoute == m_EndRoute )
   {
      // more plugging until the routing is done
      RoutingRequest* req = visitor->getRoute();
      m_StartRoute = req->OriginLevel;// + 11;
      m_EndRoute = req->DestinLevel;// + 11;
      int cur_level = m_Position/36;
      std::cout << "Route: origin: " << m_StartRoute << " end: " << m_EndRoute << " Current level " << cur_level << std::endl;
      if ( cur_level == m_StartRoute )
      {
         m_Direction = (cur_level < m_EndRoute) ? 1 : -1;
         m_StartRoute = m_EndRoute; // this stops the elevator at the destination to wait for a request.
         // in the real code we will pull this request when it ends
         m_IdleTime = 10; // pause at drop off floor;
      }
      else
      {
         m_Direction = (cur_level < m_StartRoute) ? 1 : -1;
      }
   }
}

void
C_Elevator::SetSetCallButton (int level, int dir)
{
   int reqLevel = level - m_BottomLevel;
   if (reqLevel >= 0 && reqLevel < m_FloorCount )
   {
      if (level == m_Stops[reqLevel].m_Level)
      {
         if( dir < 0 )
         {
            m_Stops[reqLevel].m_ButtonFlag |= BUTTON_DOWN;
            if( m_Direction == 0 )
            {
               m_Direction = -1;
            }
         }
         else
         {
            m_Stops[reqLevel].m_ButtonFlag |= BUTTON_UP;
            if( m_Direction == 0 )
            {
               m_Direction = 1;
            }
         }
      }
      else
      {
         std::cout << "Elevator Call Error for level: " << level << " computed index: " << reqLevel;
      }
   }
   else
   {
      std::cout << "Elevator Call for wrong floor level: " << level << " computed index: " << reqLevel;
   }
}

void
C_Elevator::Update (float dt)
{
   int max = m_TopLevel * 36;
   int min = m_BottomLevel * 36;
   int dest = ((m_StartRoute == m_EndRoute) ? m_EndRoute : m_StartRoute) * 36;
   if (dest > max ) dest = max;
   if (dest < min ) dest = min;

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
         if( m_StartRoute == m_EndRoute )
         {
            // if express down else start from m_FLoorCount down.
            for (int idx = 0; idx < m_FloorCount; ++idx )
            {
               if (m_Stops[idx].m_ButtonFlag&BUTTON_UP > 0 || m_Stops[idx].m_ButtonFlag & BUTTON_DOWN > 0)
               {
                  if( idx < m_StartRoute )
                  {
                     m_Direction = -1;
                  }
                  else if( idx > m_StartRoute )
                  {
                     m_Direction = +1;
                  }
                  m_EndRoute = m_Stops[idx].m_Level;
                  break;
               }
            }

            // BS CODE
            //int start = (rand() % (m_TopLevel - m_BottomLevel)) + m_BottomLevel; // this will work if start level is zero.
            //int end = (rand() % (m_TopLevel - m_BottomLevel)) + m_BottomLevel; // this will work if end level is zero.
            //if (end == start )
            //{
            //   m_IdleTime = 10;
            //}
            //else
            //{
            //   // this will be done by the path finder and rousing manager code
            //   //RoutingRequest req;
            //   //req.OriginLevel = start;
            //   //req.DestinLevel = end;
            //   //C_RouteVisitor visitor( &req );  // while this seems an extra load to create a class to pass a struct
            //   //                                 // the class will be managing the elevators operations (somewhat an agent).
            //   //                                 // for now, we hotwire this in.
            //   //setRoute( &visitor );
            //   m_IdleTime = 10; // pause at pickup floor;
            //}
         }
         else
         {
            m_Direction = (m_StartRoute > m_EndRoute) ? 1 : -1;
       // in the real code we will pull this request when it ends
         }
         // End BS code
         //if( m_Position > m_BottomLevel+9 )
         //{
         //   m_Direction = -1;
         //}
         //else
         //{
         //   m_Direction = 1;
         //}
      }
      break;
   case 1:
      if( m_Position < dest )
      {
         m_Position++;
         m_LiftMachine->Update( dt );
      }
      else
      {
         m_StartRoute = m_EndRoute; // this stops the elevator at the destination to wait for a request.
         m_Direction = 0;
         m_IdleTime = 90;
      }
      break;
   case -1:
      if( m_Position > dest )
      {
         m_Position--;
         m_LiftMachine->Update( dt );
      }
      else
      {
         m_StartRoute = m_EndRoute; // this stops the elevator at the destination to wait for a request.
         m_Direction = 0;
         m_IdleTime = 90;
      }
   }
   PosCalc();
}

void
C_Elevator::Draw ()
{
   m_ElevatorShaft->Draw ();
   m_LiftMachine->Draw ();
   m_cam->Draw (*m_LiftPit );
   m_cam->Draw (*m_ElevatorImage);
}
