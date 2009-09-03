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
#include "../physics.h"
#include "../image.h"
#include "../camera.h"
#include "../animation.h"
#include "../tiler.h"
#include "../routeVisitor.h"  // class that will Update the elevators route request queue

#include "routeBase.h"  // Elevators route (levels).
#include "elevatorBase.h"
#include "elevatorMachine.h"
#include "elevatorShaft.h"
#include "elevatorPit.h"
#include "elevator.h"

#else
#include "highrisedev.h"
#endif

using namespace Gfx;

// this object is the elevator collection (Machines, Shaft, Pit) and the car.
// At this time there is no LiftCar class.

//Elevator* Elevator::Create( Lift_Styles style, int x, short BottomLevel, short TopLevel, Tower * TowerParent )
//{
//   return new Elevator( style, x, BottomLevel, TopLevel, TowerParent );
//}
int Elevator::gElevatorsNumber = 1; // start with 1 to keep engineers happy

Elevator::Elevator ( Lift_Styles style, int x, short BottomLevel, short TopLevel, Tower * TowerParent)
      :  mLiftStyle( style )
      ,  mLiftOperation( LOS_Waiting )
      ,  mTowerParent (TowerParent)
{
   mTopLevel = (TopLevel);
   mBottomLevel = (BottomLevel);
   mPosition = (mBottomLevel + 1) * 36;
   mDirection = 0;
   mIdleTime = 30;
   mEnd2 = -1;
   mOffset = BottomLevel * -36;

   mFloorCount = TopLevel - BottomLevel;
   mRidersOnBoard = 0;
   memset( mRiders, 0, sizeof(mRiders) );
   ClearStops();
   memset( mStops, 0, sizeof(mStops) );


   // test code
   mStartRoute = mBottomLevel;
   mEndRoute = mTopLevel;

   ImageManager * images = ImageManager::GetInstance ();
   mElevatorImage = new AnimationSingle (images->GetImg ("elevator_u_s.png"));
   mLiftPit = new AnimationSingle (images->GetImg ("liftpit_1.png"));

   mcam = Camera::i();
   mX = x;
   mY = ( mcam->GetWorldRect ().Top) - (mBottomLevel * 36);
   mZ = -0.2; // slightly in front of the tower

   mNumber = gElevatorsNumber++; // set number;

   mLiftMachine = new ElevatorMachine( x, mTopLevel+1, this );
   mLiftPit->SetPosition ((float)mX, (float)(mY + 36) );
   mElevatorShaft = new ElevatorShaft( mX, mTopLevel, mBottomLevel, this );
}

Elevator::~Elevator()
{
   delete mElevatorImage;
};

void
Elevator::ClearStops()
{
   memset( mStops, 0, sizeof(mStops) );
}

void
Elevator::PosCalc ()
{
   mElevatorImage->SetPosition ((float)mX, (float)(mY - (mOffset + mPosition) + 4) ); // elevator sprite is only 32x32
}

void
Elevator::SetRoute( RouteVisitor* visitor )
{
   if ( mStartRoute == mEndRoute )
   {
      // more plugging until the routing is done
      RoutingRequest* req = visitor->getRoute();
      mStartRoute = req->OriginLevel;// + 11;
      mEndRoute = req->DestinLevel;// + 11;
      int cur_level = mPosition/36;
      std::cout << "Route: origin: " << mStartRoute << " end: " << mEndRoute << " Current level " << cur_level << std::endl;
      if ( cur_level == mStartRoute )
      {
         mDirection = (cur_level < mEndRoute) ? 1 : -1;
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         // in the real code we will pull this request when it ends
         mIdleTime = 10; // pause at drop off floor;
      }
      else
      {
         mDirection = (cur_level < mStartRoute) ? 1 : -1;
      }
   }
}

void
Elevator::SetSetCallButton (int level, int dir)
{
   int reqLevel = level - mBottomLevel;
   if (reqLevel >= 0 && reqLevel < mFloorCount )
   {
      if (level == mStops[reqLevel].mLevel)
      {
         if( dir < 0 )
         {
            mStops[reqLevel].mButtonFlag |= BUTTON_DOWN;
            if( mDirection == 0 )
            {
               mDirection = -1;
            }
         }
         else
         {
            mStops[reqLevel].mButtonFlag |= BUTTON_UP;
            if( mDirection == 0 )
            {
               mDirection = 1;
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
Elevator::Update (float dt)
{
   int max = mTopLevel * 36;
   int min = mBottomLevel * 36;
   int dest = ((mStartRoute == mEndRoute) ? mEndRoute : mStartRoute) * 36;
   if (dest > max ) dest = max;
   if (dest < min ) dest = min;

   // test plug
   switch( mDirection )
   {
   case 0:
      if( mIdleTime > 0 )
      {
         mIdleTime--;
      }
      else
      {
         if( mStartRoute == mEndRoute )
         {
            // if express down else start from mFLoorCount down.
            for (int idx = 0; idx < mFloorCount; ++idx )
            {
               if (mStops[idx].mButtonFlag&BUTTON_UP > 0 || mStops[idx].mButtonFlag & BUTTON_DOWN > 0)
               {
                  if( idx < mStartRoute )
                  {
                     mDirection = -1;
                  }
                  else if( idx > mStartRoute )
                  {
                     mDirection = +1;
                  }
                  mEndRoute = mStops[idx].mLevel;
                  break;
               }
            }

            // BS CODE
            //int start = (rand() % (mTopLevel - mBottomLevel)) + mBottomLevel; // this will work if start level is zero.
            //int end = (rand() % (mTopLevel - mBottomLevel)) + mBottomLevel; // this will work if end level is zero.
            //if (end == start )
            //{
            //   mIdleTime = 10;
            //}
            //else
            //{
            //   // this will be done by the path finder and rousing manager code
            //   //RoutingRequest req;
            //   //req.OriginLevel = start;
            //   //req.DestinLevel = end;
            //   //RouteVisitor visitor( &req );  // while this seems an extra load to create a class to pass a struct
            //   //                                 // the class will be managing the elevators operations (somewhat an agent).
            //   //                                 // for now, we hotwire this in.
            //   //setRoute( &visitor );
            //   mIdleTime = 10; // pause at pickup floor;
            //}
         }
         else
         {
            mDirection = (mStartRoute > mEndRoute) ? 1 : -1;
       // in the real code we will pull this request when it ends
         }
         // End BS code
         //if( mPosition > mBottomLevel+9 )
         //{
         //   mDirection = -1;
         //}
         //else
         //{
         //   mDirection = 1;
         //}
      }
      break;
   case 1:
      if( mPosition < dest )
      {
         mPosition++;
         mLiftMachine->Update( dt );
      }
      else
      {
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         mDirection = 0;
         mIdleTime = 90;
      }
      break;
   case -1:
      if( mPosition > dest )
      {
         mPosition--;
         mLiftMachine->Update( dt );
      }
      else
      {
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         mDirection = 0;
         mIdleTime = 90;
      }
   }
   PosCalc();
}

void
Elevator::Draw ()
{
   mElevatorShaft->Draw ();
   mLiftMachine->Draw ();
   mcam->Draw (*mLiftPit );
   mcam->Draw (*mElevatorImage);
}
