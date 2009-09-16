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

#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include "../physics.h"
#include "../image.h"
#include "../animation.h"
#include "../person.h"
#include "../personQueue.h"

#include "floorBase.h"
#include "level.h"

#include "../highriseException.h"

using namespace Gfx;


const int Level::mUnitSize = 9;  // used as he minimum pixels that any level or empty floor space can be. Snap-To-Grid


Level::Level (int level, int x, int y, int x2, Tower * TowerParent)
:  mTowerParent (TowerParent)
{
   mLevel = level;
                 // The levels origin and vectors (partial implementation for 3D)
   // mX, ,X2 are set in SetFloorPosiitons (x,x2)
   mY = y*-36;   //(int)(Camera::GetInstance()->GetWorldRect ().Top ) - (mLevel * 36);
   mZ = -0.4f;   // Face is always at zero for now
                 // missing are the Y (up) and Z (foward) vectors.

   if (level < 0)
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetTexture("foundation.png", GL_RGBA), 9, 36);
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetTexture("foundation.png", GL_RGBA), 9, 36);
   }
   else if (level > 0)
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetTexture("fire_escape_l.png", GL_RGBA), 24, 36);
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetTexture("fire_escape_r.png", GL_RGBA), 24, 36);
   }
   else
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetTexture("awn_left.png", GL_RGBA), 56, 36);
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetTexture("awn_right.png", GL_RGBA), 56, 36);
   }
   mEmptyFLoor = new AnimationSingle (ImageManager::GetInstance()->GetTexture("emptyfloor_d_1.png", GL_RGBA), 56, 36);
   // proto code

   mpFloorSpaceGrid = NULL;
   mFloorSpaceGridSize = 0;
   SetFloorPositions( x, x2 );
}

Level::~Level()
{
      if (mpFloorSpaceGrid!=NULL)
      {
         delete mpFloorSpaceGrid;
      }
}

void
Level::AddFloor (FloorBase * floor)
{
   mFloorSpaces.push_back (floor);
   if (floor->mX < mX)
      mX = (int)floor->mX;
   if (floor->mX2 > mX2)
      mX2 = (int)floor->mX2;
   ScanFloorSpace();
}

void
Level::SetFloorPositions( int x, int x2 )
{
                 // The levels origin and vectors (partial implementation for 3D)
   mX = x;       //(int)Camera::GetInstance()->GetWorldRect ().Left;
   mX2 = x2;     // simple xvector defaults to a minimum floor size
   if ( mLevel < 0 )
   {
      nFireEscapeLeft->SetPosition ((float)mX - 9.0f, (float)mY); // pour some concrete, replaces stairs underground
      nFireEscapeRight->SetPosition ((float)mX2, (float)mY);
   }
   else
   {
      nFireEscapeLeft->SetPosition ((float)mX - 24.0f, (float)mY);
      nFireEscapeRight->SetPosition ((float)mX2, (float)mY);
   }
   mEmptyFLoor->SetPosition ((float)mX, (float)mY);  // x is irrelivant
   ResizeFloorSpaceGrid();
}

void
Level::Update (float dt)
{
   std::vector<FloorBase *>::iterator i;
   for (i = mFloorSpaces.begin (); i != mFloorSpaces.end (); i++)
      (*i)->Update (dt);
}

// Function that calls the OpenGL rendering in the subclass.
void
Level::Draw ()
{
   std::vector<FloorBase *>::iterator i;
   for (i = mFloorSpaces.begin (); i != mFloorSpaces.end (); i++)
      (*i)->Draw ();
   //Camera::GetInstance()->Draw (*nFireEscapeLeft);
   //Camera::GetInstance()->Draw (*nFireEscapeRight);
   DrawEmptySpace();
   if( mX2 > mX )
   {
      Render (nFireEscapeLeft);
      Render (nFireEscapeRight);
   }
}

// Possible Deprecation
FloorBase*
Level::FindSpace (int x)
{
   Level::FloorIterType it;
   for (mFloorSpaces.begin(); it<mFloorSpaces.end(); ++it)
   {
      FloorBase* pFB = (*it);
      if( x >= pFB->GetX() && x<= pFB->GetX2() )
      {
         return pFB;
      }
   }
   return NULL;
}

// Possible Deprecation
bool
Level::TestForEmptySpace (int x, int x2 )
{
   Level::FloorIterType it;
   for (it=mFloorSpaces.begin(); it<mFloorSpaces.end(); ++it)
   {
      FloorBase* pFB = (*it);
      if( (x >= pFB->GetX() && x<= pFB->GetX2()) || (x >= pFB->GetX() && x2<= pFB->GetX2()) )
      {
         return false;
      }
   }
   return true;
}

void
Level::AddElevatorToQueue (Elevator* pElevator)
{
   // may wand to check for dups
   PersonQueue* pQ = new PersonQueue();
   pQ->AssignElevator(pElevator);
   mElevatorQueues.push_back (pQ);
}

void
Level::RemoveElevatorFromQueue (Elevator* pElevator)
{
   // won't compile ARRG!

   //Level::QueueIterType it;
   //for (it=mElevatorQueues.begin(); it<mElevatorQueues.end(); ++it)
   //{
   //   PersonQueue* pQ = (*it);
   //   if( pLift == pElevator )
   //   {
   //      mElevatorQueues.remove (pQ);
   //      break;
   //   }
   //}
}

PersonQueue* Level::FindQueue (int elevator)
{
   //Level::QueueIterType it;
   //for (it=mElevatorQueues.begin(); it<mElevatorQueues.end(); ++it)
   //{
   //   PersonQueue* pQ = (*it);
   //   if( pQ->GetElevatorNumber() == elevator )
   //   {
   //      return pQ;
   //   }
   //}
   return NULL;
}


// prototype test code
//
// member vars
//
//   unsigned char*  mpSpaceGrid;   // the allocated grid
//   int   mSpaceGridSize;          // size of the floor space in units
//   bool  mFloorIsFull;        // Can't place any more objects
//   bool  mNoEmptyFloorSpace;  // Skip the DrawEmptySpace function

// Level tracking methods/functions

void
Level::ResizeFloorSpaceGrid()
{
   if( (mX2-mX) / 9 > mFloorSpaceGridSize )
   {
      try
      {
         mFloorSpaceGridSize = (mX2-mX) / 9;
         if (mpFloorSpaceGrid!=NULL)
         {
            delete mpFloorSpaceGrid;
            mpFloorSpaceGrid = NULL;  // set null in case the new fails, don't want the old pointer
                                 // to make matters worse while the app attemps to save and exit.
         }
         mpFloorSpaceGrid = new unsigned char[mFloorSpaceGridSize+1];
      }
      catch (...)
      {
         throw new HighriseException ("Error resizing FloorSpace grid");
      }
   }
   ScanFloorSpace();
}

// Clear the floor space grid then scan through the occupied space list (mFloorSpaces).
// Keep track of spaces large enough to hold the minimum hotel room or restroom which is 3 units (3*mUnitSize);
// also keep track is there are any empty spaces to skip rendering if level is fully occupied and no empty spaces.
//
void
Level::ScanFloorSpace() // Marks the gird for what is in the space
{
   int iEmpty = 0;
   int iMaxEmptyUnits = 0;
   mFloorIsFull = false;
   if(mpFloorSpaceGrid==NULL)
   {
      return; // for now
   }
   try
   {
      memset (mpFloorSpaceGrid, 0, sizeof(unsigned char)*mFloorSpaceGridSize);
      Level::FloorIterType it;
      for (it=mFloorSpaces.begin(); it<mFloorSpaces.end(); ++it)
      {
         FloorBase* pFB = *it;
         int x = int ((pFB->GetX()-this->mX) / 9);
         int x2 = int ((pFB->GetX2()-this->mX) / 9);

         for (int i=x;i < x2; ++i)
         {
            if (i >= 0 && i < mFloorSpaceGridSize)
            {
               mpFloorSpaceGrid[i] = 1; // pFB->GetTypeCode(); // identify for the minimap
            }
         }
      }
      int iCount = 0;
      for (int i=0;i < mFloorSpaceGridSize;++i)
      {
         if (mpFloorSpaceGrid[i]== 0)
         {
            iCount++;
            iEmpty++;
         }
         else
         {
            if (iCount > iMaxEmptyUnits)
            {
               iMaxEmptyUnits = iCount;   // track floor space for at least one minimum space available else flag no empty space
            }
            iCount = 0;
         }
      }
   }
   catch (...)
   {
      throw new HighriseException ("Array Error scaning FloorSpace");
   }

   if (iEmpty==0)
   {
      mNoEmptyFloorSpace = true;
   }
   else
   {
      mNoEmptyFloorSpace = false;
   }
   if (iMaxEmptyUnits < 3)
   {
      mFloorIsFull = true;
   }
}

bool
Level::IsSpaceEmpty( int ix, int ix2 ) // TestForEmptySpace...
{
   bool bResult = true;
   int x = int ((ix - this->mX) / 9);
   int x2 = int ((ix2 - this->mX) / 9);

   for (int i=x;i < x2; ++i)
   {
      if (i >= 0 && i < mFloorSpaceGridSize)
      {
         if (mpFloorSpaceGrid[i])
         {
            bResult = false;
            break;
         }
      }
   }
   return bResult;
}

void
Level::DrawEmptySpace()
{
   try
   {
      int xStart = -1;
      int xCount = 0;
      for (int i=0;i < mFloorSpaceGridSize; ++i)
      {
         if (mpFloorSpaceGrid[i] == 0)
         {
            if( xStart < 0 )
            {
               xCount = 1;
               xStart = i;
            }
            else
            {
               xCount++;
            }
         }
         else
         {
            if( xCount > 0 )
            {
               Render (mEmptyFLoor, mX + xStart * 9.0f, mX + (xStart + xCount) * 9.0f);
               xStart = -1;
               xCount = 0;
            }
         }
      }
      if( xCount > 0 )
      {
         Render (mEmptyFLoor, mX + xStart * 9.0f, mX + (xStart + xCount) * 9.0f);
      }
   }
   catch (...)
   {
      mFloorSpaceGridSize = 0; // stop this from recurring
      throw new HighriseException ("Error rendering empty Floor Space");
   }
}
