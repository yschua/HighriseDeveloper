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
#include "../physics.h"
#include "../image.h"
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
#include "../highrisedev.h"
#endif
#include "../highriseException.h"

using namespace Gfx;

// this object is the elevator collection (Machines, Shaft, Pit) and the car.
// At this time there is no LiftCar class.

//Elevator* Elevator::Create( Lift_Styles style, int x, short BottomLevel, short TopLevel, Tower * TowerParent )
//{
//   return new Elevator( style, x, BottomLevel, TopLevel, TowerParent );
//}
int Elevator::gElevatorsNumber = 1; // start with 1 to keep engineers happy

const int Elevator::mStandingPositions[16] =
{
   12,20,16,4,18,22,6,24,8,10,2,5,9,13,17,21
};

Elevator::Elevator ( Lift_Styles style, int x, short BottomLevel, short TopLevel, Tower * TowerParent)
      :  mLiftStyle( style )
      ,  mLiftOperation( LOS_Waiting )
      ,  mTowerParent (TowerParent)
      ,  Body(32, 32)
{
   mTopLevel = TopLevel;
   mBottomLevel = BottomLevel-1;
   mPosition = (mBottomLevel) * 36;
   mDirection = 0;
   mIdleTime = 30;
   mEnd2 = -1;
   mOffset = BottomLevel * -36;

   mFloorCount = TopLevel - BottomLevel;
   mRidersOnBoard = 0;
   mMaxCap = 12;
   memset( mRiders, 0, sizeof(mRiders) );
   ClearStops();
   memset( mStops, 0, sizeof(mStops) );

   mStartRoute = mBottomLevel;
   mEndRoute = mBottomLevel;

   ImageManager * images = ImageManager::GetInstance ();
   mElevatorImage = new AnimationSingle (images->GetTexture ("elevator_u_n.png", GL_RGBA), 32, 32);
   mLiftPit = new AnimationSingle (images->GetTexture ("liftpit_1.png", GL_RGBA), 36, 36);

   mX = x+2;
   mY = (int)(mBottomLevel * 36);
   mZ = -0.49f; // slightly in front of the tower

   mNumber = gElevatorsNumber++; // set number;

   mLiftMachine = new ElevatorMachine( x, mTopLevel+1, this );
   mLiftPit->SetPosition ((float)x, (float)(-mY) );
   mElevatorShaft = new ElevatorShaft( x, mTopLevel, mBottomLevel, this );
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
Elevator::SetFloorButton (RouteVisitor* visitor)   // OK, take me there
{
   RoutingRequest* req = visitor->getRoute();
   mStartRoute = req->OriginLevel;
   mEndRoute = req->DestinLevel;
   std::cout << "Route: origin: " << mStartRoute << " end: " << mEndRoute << std::endl;
   if ( mEndRoute != mStartRoute )
   {
      mDirection = (mStartRoute < mEndRoute) ? 1 : -1;
      mIdleTime = 10; // pause at drop off floor;
   }
   else
   {
      mDirection = 0;
   }
}

void
Elevator::SetCallButton (RouteVisitor* visitor)    // where is an elevator when you need one, I've pushed this button 5 times already
{
   RoutingRequest* req = visitor->getRoute();
   int dirFlag = (req->DestinLevel > req->OriginLevel) ? BUTTON_UP : BUTTON_DOWN;
   int reqLevel = req->OriginLevel - mBottomLevel;
   int cur_level = mPosition / 36 - mBottomLevel;
   int align = mPosition % 36;  // zero if we are aligned with a floor (safe stop)

   if( cur_level == reqLevel && align == 0 )
   {
      SetFloorButton( visitor );
      visitor->SetBoarding();
   }
   else
   {
      if (reqLevel >= 0 && reqLevel < mFloorCount )
      {
         mStops[reqLevel].mButtonFlag |= dirFlag;
      }
      else
      {
         std::cout << "Elevator Call for wrong floor level: " << req->OriginLevel << " computed index: " << reqLevel;
      }
   }
}

int
Elevator::LoadPerson(Person* person, int destLevel) // returns space remaining
{
   if (mRidersOnBoard < mMaxCap)
   {
      mRiders[mRidersOnBoard].mDestLevel = destLevel;
      mRiders[mRidersOnBoard].mPerson = person;
      SetDestination (destLevel);
      mRidersOnBoard++;
   }
   return mMaxCap - mRidersOnBoard;
}

void
Elevator::SetDestination (int level)
{
   mEndRoute = level;
   mDirection = ( mStartRoute < mEndRoute ) ? 1 : -1;
}

void
Elevator::NextCallButton ()
{
   int nPasses = 2; // only 2 directions
   int curStop = mStartRoute - mBottomLevel;
   bool bDown = (mDirection < 1);
   while( nPasses > 0 )
   {
      if( bDown )   // search down
      {
         --nPasses;
         for( int idx=curStop-1; idx>=0; --idx )
         {
            if( mStops[idx].mButtonFlag )
            {
               nPasses = 0; // found a button lit, done with main loop but we have to check precidence
               // on the way down we stop on destination floors or floors with lit down buttons or proceed to the lowest floor with a lit up button.
               // later on the way up we will stop on floors with lit up buttons.
               if( mStops[idx].mButtonFlag&BUTTON_DOWN|DESINATION )
               {
                  SetDestination( idx + mBottomLevel );
                  break;
               }
            }
         }
         bDown = false; // search up if not found
      }
      else
      {
         --nPasses;
         for( int idx=curStop+1; idx < mFloorCount; ++idx )
         {
            if( mStops[idx].mButtonFlag )
            {
               nPasses = 0; // found a button lit, done with main loop but we have to check precidence
               // on the way up we stop on destination floors or floors with lit up buttons or proceed to the highest floor with a lit down button.
               // later on the way down we will stop on floors with lit down buttons.
               if( mStops[idx].mButtonFlag&BUTTON_UP|DESINATION )
               {
                  SetDestination( idx + mBottomLevel );
                  break;
               }
            }
         }
         bDown = (nPasses> 0); // only true if we have not looked down yet
      }
   }
}

void
Elevator::Motion ()
{
   int max = mTopLevel * 36;
   int min = mBottomLevel * 36;
   int align = mPosition % 36;  // zero if we are aligned with a floor (safe stop)
   int cur_level = (mPosition -18) / 36;
   int index = cur_level-mBottomLevel;
   if( index < 0 || index >= mFloorCount )
      throw new HighriseException( "Elevator: Error in current floor index" );

   int dest = ((mStartRoute == mEndRoute) ? mStartRoute * 36 : mEndRoute * 36);
   if (dest > max ) dest = max;
   if (dest < min ) dest = min;
   switch( mDirection )
   {
   case 0:
      // now running on call button logic
      if( align == 0 && mStops[index].mButtonFlag )
      {
         mStops[index].mButtonFlag = 0; // clear any condition
      }
      NextCallButton();
      break;
   case 1:
      if( mPosition < dest )
      {
         mPosition++;
         mLiftMachine->Update( 1 );
      }
      else
      {
         if( align == 0 && mStops[index].mButtonFlag&BUTTON_UP|DESINATION )
         {
            mStops[index].mButtonFlag & BUTTON_DOWN; // clear all but down
         }
         NextCallButton();
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         mIdleTime = 20;
      }
      break;
   case -1:
      if( mPosition > dest )
      {
         mPosition--;
         mLiftMachine->Update( -1 );
      }
      else
      {
         if( align == 0 && mStops[index].mButtonFlag&BUTTON_DOWN|DESINATION )
         {
            mStops[index].mButtonFlag & BUTTON_UP; // clear all but up
         }
         NextCallButton();
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         mIdleTime = 20;
      }
   }
   PosCalc();
}


// Elevator is either in motion or idle( doors open, loading, unloading, no calls )
// When idle do nothing. Idle times are set when the elevator arrives at a floor
// When idle cycle ends scan for destinations and calls.
void
Elevator::Update (float dt)
{
   if( mIdleTime > 0 )
   {
      mIdleTime--;
   }
   else
   {
      Motion();
   }
}

void
Elevator::Draw ()
{
   mElevatorShaft->Draw ();
   mLiftMachine->Draw ();
//   mcam->Draw (*mLiftPit );
//   mcam->Draw (*mElevatorImage);
   Render (mLiftPit);
   Render (mElevatorImage);
}
