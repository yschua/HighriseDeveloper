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

// People that make the tower thrive.

#include <cstdlib>
#include <iostream>
#include "person.h"

Person::Person (Location& loc)
{
   mHealth = HS_Well;
   mMood = MS_Content;
   mActivity = AS_JobHunting; // noob, starts out looking for home, job etc.
   mOccupation = 0;
   mHome = 1;          // have a home (Test code)
   mCurrentState = CS_Idle;
   mLocation = loc;    // copy
}

Person::~Person (void)
{
}

void Person::Update (float dt)
{
   // check time of day, what activity should we be doing.
   if (mOccupation < 1) // && age > 16 )
   {
      mActivity = AS_JobHunting;
   }
   else if (mHome < 1)
   {
      mActivity = AS_CondoHunting; // if income < $n AS_ApartmentHunting.
   }
   switch (mActivity)
   {
      case AS_GoingToWork:
         if (mWorkPath.index < mWorkPath.size)
         {
            Location& cur = mWorkPath.mPathList[mWorkPath.index];
            // TODO: check building first but for now we only have 1
            if (cur.mLevel == mLocation.mLevel)
            {
               mLocation.mX = cur.mX; // TODO: Move peep in animator
               mWorkPath.index++;
            }
            else
            {
               // waiting or on an elevator
            }
         }
         if (mWorkPath.index >= mWorkPath.size) // this can be handled better and also need to check times
         {
            mLocation.mLevel = mWorkPath.mPathList[mWorkPath.index-1].mLevel; // this will bring the car to the office level at days end
            set_Activity( AS_Working ); // offices and businesses show employees at work.
         }
         break;
      case AS_Working:
         if (rand() % 100 == 50 )
         {
            set_Activity( AS_GoingHome );
            set_CurrentState( Person::CS_Walking );

            int home_level = (rand() % 1) + 4;   // test code, give them a home
            Location& cur = mWorkPath.mPathList[0];
            cur.mLevel = home_level;
            cur.mX = 2;
            mWorkPath.index--;  // this is the return trip home
         }
         break;
      case AS_GoingHome:
         if (mWorkPath.index > 0)
         {
            Location& cur = mWorkPath.mPathList[mWorkPath.index];
            // TODO: check building first but for now we only have 1
            if (cur.mLevel == mLocation.mLevel)
            {
               mLocation.mX = cur.mX; // TODO: Move peep in animator
               mWorkPath.index--;
            }
            else
            {
               // waiting or on an elevator
            }
         }
         else
         {
            set_Activity( AS_Relaxing ); // offices and businesses show employees at work.
         }
         break;
   }
}

void Person::Draw( )
{
}
