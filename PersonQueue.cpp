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

// head and tail queue. People in and out while waiting for elevators, trams, rail and buses.
#include <iostream>
#include <vector>
#include "Person.h"
#include "Tower/elevator.h"
#include "AI/citizensAgent.h"
#include "AI/pathAgent.h"
#include "personQueue.h"

PersonQueue::PersonQueue()
{
   mHeadIndex = 0;
   mTailIndex = 0;
   mCapacity = 32;
   mpQueue = new Person*[mCapacity];
}

void PersonQueue::AddPerson (Person* person)
{
   bool bRealloc = false;
   if ( mTailIndex +1 >= mCapacity)
   {
      if( mHeadIndex == 0 )
      {
         bRealloc = true;
      }
      else
      {
         mTailIndex = 0;
      }
   }
   else if ( mHeadIndex  == mTailIndex +1)
   {
      bRealloc = true;
   }
   else
   {
   }
   if (bRealloc)
   {
      Person** newQueue = new Person*[mCapacity];
      // copy queue;
      delete mpQueue;
      mpQueue = newQueue;
   }
   person = mpQueue[mHeadIndex];
   mHeadIndex++;
   if( mHeadIndex >= mCapacity )
   {
      mHeadIndex = 0;
   }
}

void PersonQueue::AssignElevator (Elevator* pElevator)
{
   mpElevator = pElevator;
}

int PersonQueue::GetElevatorNumber ()
{
   if (mpElevator)
   {
      return mpElevator->GetNumber ();
   }
   return 0;
}


Person* PersonQueue::TakeNextPerson ()
{
   Person* person = 0;
   if (mHeadIndex != mTailIndex)
   {
      person = mpQueue[mHeadIndex];
      mHeadIndex++;
      if( mHeadIndex >= mCapacity )
      {
         mHeadIndex = 0;
      }
      mSweepIndex = 0;
   }
   return person;
}

void PersonQueue::Update()
{
   // compress the line
   if (mTailIndex > 1 && mSweepIndex < mTailIndex)
   {
      if (mSweepIndex < 0)
      {
         mSweepIndex = 0;
      }
      else if(mSweepIndex < mTailIndex)
      {
         if(mpQueue[mSweepIndex] == NULL)
         {
            mpQueue[mSweepIndex] = mpQueue[mSweepIndex+1];
         }
         mSweepIndex++;
      }
   }
}
