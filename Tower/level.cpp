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

#ifdef WIN32
#include <iostream>
#include <map>
#include <vector>
#include <list>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../physics.h"
#include "../camera.h"
#include "../image.h"
#include "../animation.h"
#include "../person.h"
#include "../personQueue.h"

#include "floorBase.h"
#include "level.h"

#else
#include "../highrisedev.h"
#endif

using namespace Gfx;

Level::Level (int level, int x, int y, int x2, Tower * TowerParent)
:  mTowerParent (TowerParent)
{
   mLevel = level;
               // The levels origin and vectors (partial implementation for 3D)
   mX = x;     //(int)Camera::GetInstance()->GetWorldRect ().Left;
   mY = y*-36; //(int)(Camera::GetInstance()->GetWorldRect ().Top ) - (mLevel * 36);
   mZ = -0.4f;     // Face is always at zero for now
   mX2 = x2;   // simple xvector defaults to a minimum floor size
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
}

void
Level::AddFloor (FloorBase * floor)
{
   mFloorSpaces.push_back (floor);
   if (floor->mX < mX)
      mX = floor->mX;
   if (floor->mX2 > mX2)
      mX2 = floor->mX2;
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
}

void
Level::Update (float dt)
{
   std::vector<FloorBase *>::iterator i;
   for (i = mFloorSpaces.begin (); i != mFloorSpaces.end (); i++)
      (*i)->Update (dt);
}

void
Level::Draw ()
{
   std::vector<FloorBase *>::iterator i;
   for (i = mFloorSpaces.begin (); i != mFloorSpaces.end (); i++)
      (*i)->Draw ();
   //Camera::GetInstance()->Draw (*nFireEscapeLeft);
   //Camera::GetInstance()->Draw (*nFireEscapeRight);
   Render (nFireEscapeLeft);
   Render (nFireEscapeRight);

}


FloorBase* Level::FindSpace (int x)
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

bool Level::TestForEmptySpace (int x, int x2 )
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

void Level::AddElevatorToQueue (Elevator* pElevator)
{
   // may wand to check for dups
   PersonQueue* pQ = new PersonQueue();
   pQ->AssignElevator(pElevator);
   mElevatorQueues.push_back (pQ);
}

void Level::RemoveElevatorFromQueue (Elevator* pElevator)
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
