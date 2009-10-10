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

#include <cstring>
#include <cstdlib>
#include <map>
#include <iostream>
#include "../Root/Physics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Tiler.h"
#include "../Root/SerializerBase.h"
#include "../People/Person.h"

#include "PersonQueue.h"
#include "RouteBase.h"  // Elevators route (levels).
#include "ElevatorBase.h"
#include "ElevatorMachine.h"
#include "ElevatorShaft.h"
#include "ElevatorPit.h"
#include "Elevator.h"
#include "Level.h"
#include "Tower.h"

#include "../Root/HighRiseException.h"

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

Elevator::Elevator ( LiftStyle style, int x, short BottomLevel, short TopLevel, Tower * TowerParent)
      :  mLiftStyle( style )
      ,  mLiftOperation( LOS_Waiting )
      ,  mTowerParent (TowerParent)
      ,  Body(32, 32)
{
   mCurrentLevel = 1;
   mTopLevel = TopLevel;
   mBottomLevel = BottomLevel;
   mPosition = (mBottomLevel) * 36;
   mDirection = -1;
   mIdleTime = 10;
   mEnd2 = -1;
   mPosition = 1; // make the elevater hit the floor
   //mOffset = 0;//BottomLevel * -36;
   mOffset = mBottomLevel * 36;

   mFloorCount = TopLevel - BottomLevel;
   mRidersOnBoard = 0;
   mMaxCap = 12;
   memset( mRiders, 0, sizeof(mRiders) );
   ClearStops();
   memset( mStops, 0, sizeof(mStops) );

   mStartRoute = mBottomLevel;
   mEndRoute = mBottomLevel;

   mX = x+2;
   mY = (int)(mBottomLevel * 36);
   mZ = -0.49f; // slightly in front of the tower

   mNumber = gElevatorsNumber++; // set number;
   LoadImages();
   mRouteQueues = NULL;
   SetQueues();
}

Elevator::Elevator( SerializerBase& ser, short TopLevel, Tower * TowerParent )
:  Body(32, 32)
,  mTowerParent( TowerParent )
{
   //"type", "standard elevator"
   mNumber = ser.GetInt( "number" );
   mX = ser.GetInt( "startx" );
   mY = ser.GetInt( "starty" );
   mZ = ser.GetFloat( "startz" );
   mCurrentLevel = 0;
   mTopLevel = (short)ser.GetInt( "toplevel" );
   mBottomLevel = (short)ser.GetInt( "bottomlevel" );
   mPosition = (short)ser.GetInt( "position" );
   mDirection = (short)ser.GetInt( "direction" );
   mIdleTime = (short)ser.GetInt( "idletime" );
   mEnd2 = (short)ser.GetInt( "end2" );
   mOffset = (short)ser.GetInt( "offset" );
   mRidersOnBoard = (short)ser.GetInt( "ridersonboard" );
   mMaxCap = (short)ser.GetInt( "maxcap" );
   mOffset = mBottomLevel * 36;
   LoadImages();
   mRouteQueues = NULL;
   SetQueues();
}

Elevator::~Elevator()
{
   delete mElevatorImage;
};

void Elevator::LoadImages()
{
   ImageManager * images = ImageManager::GetInstance ();
   const char* pImageName = "elevator_u_n.png";
   switch (mLiftStyle)
   {
   case LS_Standard:
      mWidth.x = 32;
      break;
   case LS_HighCapacity:
      mWidth.x = 41;
      pImageName = "elevator_u_w.png";
      break;
   case LS_Freight:
      mWidth.x = 32;
      pImageName = "elevator_u_s.png";
      break;
   case LS_Express:
      mWidth.x = 32;
      pImageName = "elevator_o_x.png";
      break;
   }
   mElevatorImage = new AnimationSingle (images->GetTexture (pImageName, GL_RGBA), mWidth.x, mHeight.y);
   mRiderImage = new AnimationSingle (images->GetTexture ("person_e.png", GL_RGBA), 8, 16);
   mRiderImage->SetPosition ((float)mX +8, (float)(mBottomLevel-1) * -36 ); // neg 36 so it becomed positive for model view
   mLiftMachine = new ElevatorMachine( mX - 2, mTopLevel+1, mWidth.x+4, this );
   mLiftPit = new AnimationSingle (images->GetTexture ("liftpit_1.png", GL_RGBA), mWidth.x+4, 36);
   mLiftPit->SetPosition ((float)mX - 2, (float)(mBottomLevel-1) * -36 ); // neg 36 so it becomed positive for model view
   mElevatorShaft = new ElevatorShaft( mX - 2, mTopLevel, mBottomLevel-1, mWidth.x+4, this );
}

void Elevator::ClearStops()
{
   memset( mStops, 0, sizeof(mStops) );
}

void Elevator::SetStopLevels ()
{
   int levels = mTopLevel - mBottomLevel;
   int level = mBottomLevel;
   int stop = 0;
   switch(mLiftStyle)
   {
   case LS_Standard:
      for( int idx = 0; idx < levels; ++idx)
      {
         mStops[idx].mLevel = level++;
      }
      break;
   case LS_HighCapacity:
      for( int idx = 0; idx < levels; ++idx)
      {
         Level* pLevel = mTowerParent->GetLevel(level);
         if( pLevel->HasLobby() )
         {
            mStops[stop++].mLevel = level;
         }
         level++;
      }
      break;
   case LS_Freight:
   case LS_Express:
      break;
   }
}

void Elevator::PosCalc ()
{
   mElevatorImage->SetPosition ((float)mX, (float)(mY - (mOffset + mPosition) + 4) ); // elevator sprite is only 32x32
   mRiderImage->SetPosition ((float)mX, (float)(mY - (mOffset + mPosition) + 18) ); // people
}

void Elevator::SetFloorButton (RoutingRequest& req)   // OK, take me there
{
   //mStartRoute = req.OriginLevel;
   //mEndRoute = req.DestinLevel;
   std::cout << "Route: origin: " << mStartRoute << " end: " << mEndRoute << std::endl;
   int reqLevel = req.DestinLevel - mBottomLevel;
   mStops[reqLevel].mButtonFlag |= DESTINATION;
   //if ( mEndRoute != mStartRoute )
   //{
   //   mDirection = (mStartRoute < mEndRoute) ? 1 : -1;
   //   mIdleTime = 10; // pause at drop off floor;
   //}
   //else
   //{
   //   mDirection = 0;
   //}
}

bool Elevator::SetCallButton (RoutingRequest& req)    // where is an elevator when you need one, I've pushed this button 5 times already
{
   bool bIsOnFloor = false;
   int dirFlag = (req.DestinLevel > req.OriginLevel) ? BUTTON_UP : BUTTON_DOWN;
   int reqLevel = req.OriginLevel - mBottomLevel;
   int cur_level = (mPosition - 18 )/ 36 - mBottomLevel;
   int align = mPosition % 36;  // zero if we are aligned with a floor (safe stop)

   if( cur_level == reqLevel && align == 0 )
   {
      SetFloorButton( req );
      bIsOnFloor = true;
   }
   else
   {
      if (reqLevel >= 0 && reqLevel < mFloorCount )
      {
         mStops[reqLevel].mButtonFlag |= dirFlag;
      }
      else
      {
         std::cout << "Elevator Call for wrong floor level: " << req.OriginLevel << " computed index: " << reqLevel;
      }
   }
   return bIsOnFloor;
}

int Elevator::LoadPerson(Person* person, RoutingRequest& req) // returns space remaining
{
   if (mRidersOnBoard < mMaxCap)
   {
      mRiders[mRidersOnBoard].mDestLevel = req.DestinLevel - mBottomLevel;
      mRiders[mRidersOnBoard].mPerson = person;
      mRidersOnBoard++;
      this->SetFloorButton( req );
   }
   return mMaxCap - mRidersOnBoard;
}

Person* Elevator::UnloadPerson( ) // returns space remaining
{
   Person* person = NULL;
   int idx = 0;
   for ( ; idx < mRidersOnBoard; ++idx)
   {
      if(mRiders[idx].mDestLevel == mCurrentLevel)
      {
         person = mRiders[idx].mPerson;
         mRiders[idx].mPerson = 0;
         mRidersOnBoard--;
         break;
      }
   }
   for ( ; idx < mRidersOnBoard; ++idx)
   {
      mRiders[idx].mDestLevel = mRiders[idx+1].mDestLevel;
      mRiders[idx].mPerson = mRiders[idx+1].mPerson;
   }
   return person;
}

void Elevator::SetDestination (int level)
{
   mEndRoute = level;
   mStartRoute = mCurrentLevel;
   mDirection = ( mStartRoute < mEndRoute ) ? 1 : -1;
}

void Elevator::NextCallButton ()
{
   int nPasses = 2; // only 2 directions
   int curStop = mCurrentLevel;
   bool bDown = (mDirection < 1 && curStop > 0);
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
               if( mStops[idx].mButtonFlag&BUTTON_DOWN|DESTINATION )
               {
                  SetDestination( idx + mBottomLevel );
                  break;
               }
            }
         }
         if (nPasses> 0) // only true if we have not looked down yet
         {
            if (mDirection =- 1)
            {
               mDirection = 0;
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
               if( mStops[idx].mButtonFlag&BUTTON_UP|DESTINATION )
               {
                  SetDestination( idx );
                  break;
               }
            }
         }
         if (nPasses> 0) // only true if we have not looked down yet
         {
            if (mDirection == 1)
            {
               mDirection = 0;
            }
            bDown = true;
         }
      }
   }
}

void Elevator::Motion ()
{
   int max = mTopLevel * 36;
   int min = mBottomLevel * 36;
   int align = mPosition % 36;  // zero if we are aligned with a floor (safe stop)
   mCurrentLevel = (mPosition ) / 36 - mBottomLevel;
   int index = mCurrentLevel;// - mBottomLevel;
   if( index < 0 || index >= mFloorCount )
      throw new HighriseException( "Elevator: Error in current floor index" );

   int dest = ((mStartRoute == mEndRoute) ? (mStartRoute+mBottomLevel) * 36 : (mEndRoute+mBottomLevel) * 36);
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
      if( mDirection == 0)
      {
         mIdleTime = 20;
      }
      break;
   case 1:
      if( mPosition < dest )
      {
         mPosition++;
         mLiftMachine->Update( 1 );
      }
      else
      {
         NextCallButton();
         if( align == 0 && mStops[index].mButtonFlag&(BUTTON_UP|DESTINATION) )
         {
            mStops[index].mButtonFlag &= BUTTON_DOWN; // clear all but down
         }
         if (mDirection != 1) // no longer up
         {
            mStops[index].mButtonFlag = 0;
         }
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
         if( align == 0 && mStops[index].mButtonFlag&(BUTTON_DOWN|DESTINATION) )
         {
            mStops[index].mButtonFlag &= BUTTON_UP; // clear all but up
         }
         if (mDirection != -1) // no longer up
         {
            mStops[index].mButtonFlag = 0;
         }
         NextCallButton();
         mStartRoute = mEndRoute; // this stops the elevator at the destination to wait for a request.
         mIdleTime = 20;
      }
   }
   PosCalc();
}

void Elevator::Update (float dt)
{
   std::cout << "Elevator update without time called: " << std::endl;
}

// Elevator is either in motion or idle( doors open, loading, unloading, no calls )
// When idle do nothing. Idle times are set when the elevator arrives at a floor
// When idle cycle ends scan for destinations and calls.
void Elevator::Update (float dt, int tod)
{
   if( mIdleTime > 0 )
   {
      Person* person = UnloadPerson();
      PersonQueue* pQ = (*mRouteQueues)[mCurrentLevel];
      Person* personOn = pQ->TakeNextPerson();
      pQ->Update();

      if( person == NULL && personOn == NULL)
      {
         mIdleTime--;
      }
      else
      {
         if( person != NULL ) person->SetCurrentState( Person::CS_Disembarking );
         if( personOn != NULL )
         {
            int curLevel = personOn->get_Location().mLevel;
            int idx = personOn->get_WorkPath().index;
            if( idx < 0 ) idx = 0; // bug patch

            //personOn->SetCurrentState( Person::CS_Boarding );
            RoutingRequest req;     // routing code needs to queue this person
            req.OriginLevel = curLevel;
            req.DestinLevel = personOn->get_WorkPath().mPathList[idx].mLevel;
            personOn->SetCurrentState( Person::CS_Riding );
            LoadPerson (personOn, req);
         }
         mIdleTime = 10;
      }
   }
   else
   {
      Motion();
   }
}

void Elevator::Draw ()
{
   mElevatorShaft->Draw ();
   mLiftMachine->Draw ();
//   mcam->Draw (*mLiftPit );
//   mcam->Draw (*mElevatorImage);
   Render (mLiftPit);
   Render (mElevatorImage);
   for( int idx =0; idx < mRidersOnBoard && idx < 16; ++idx )
   {
      Render( mRiderImage, (float)(mX + mStandingPositions[idx]), (float)(mX + mStandingPositions[idx] + 8));
   }
   QueueIterType it;
   int il = mBottomLevel;
   for (it=mRouteQueues->begin(); it!=mRouteQueues->end(); ++it)
   {
      PersonQueue* pQ = (*it);
      pQ->Draw (mX+18, il++);
   }
}

void Elevator::Save( SerializerBase& ser )
{
   ser.Add( "type", "standard elevator" );
   ser.Add( "number", mNumber );
   ser.Add( "startx", mX );
   ser.Add( "starty", mY );
   ser.Add( "startz", mZ );
   ser.Add( "toplevel", mTopLevel );
   ser.Add( "bottomlevel", mBottomLevel );
   ser.Add( "position", mPosition );
   ser.Add( "direction", mDirection );
   ser.Add( "idletime", mIdleTime );
   ser.Add( "end2", mEnd2 );
   ser.Add( "offset", mOffset );
   ser.Add( "ridersonboard", mRidersOnBoard );
   ser.Add( "maxcap", mMaxCap );
//   ser.Add( "riders", mRiders, sizeof(mRiders) );
//   ser.Add( "stops", mStops, sizeof(mStops) );
}

void Elevator::SetQueues ()
{
   if (mRouteQueues == NULL)
   {
      mRouteQueues = new QueueType();
   }
   QueueIterType it;
   int count = mTopLevel - mBottomLevel;
   for (int idx = 0; idx < count; ++idx)
   {
      PersonQueue* pQ = new PersonQueue();
      mRouteQueues->push_back(pQ);
   }
}

PersonQueue* Elevator::FindQueue (int Level)
{
   unsigned int index = Level - mBottomLevel;
   if (index >= 0 && index < mRouteQueues->size())
   {
      PersonQueue* pQ = (*mRouteQueues)[index];
      return pQ;
   }
   return NULL;
}
