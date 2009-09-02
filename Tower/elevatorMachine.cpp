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
#include "../physics.h"
#include "../animation.h"
#include "../tiler.h"
#include "../camera.h"
#include "../image.h"

#include "elevatorBase.h"
#include "elevatorMachine.h"

using namespace Gfx;

ElevatorMachine::ElevatorMachine (int x, int level, Elevator* pElevator )
      :  ElevatorBase( x, level, pElevator )
      ,  mState( LMS_Idle )
{
   ImageManager * image_man = ImageManager::GetInstance ();
   my = (Camera::GetInstance()->GetWorldRect ().Top ) - (level * 36);
   std::cout << "New elevator machine at " << mx << ", " << my << std::endl;
   mLifterAnimation = new Animation ();
   mLifterAnimation->AddFrame (image_man->GetImg ("liftMachine_1.png"), 1000);
   mLifterAnimation->AddFrame (image_man->GetImg ("liftMachine_2.png"), 1000);
   mLifterAnimation->AddFrame (image_man->GetImg ("liftMachine_3.png"), 1000);
   mImageFrame = 0;
   mFirstFrame = 0;
   mLastFrame = 2;
   mcam = Camera::GetInstance ();
   my = ( mcam->GetWorldRect ().Top) - (level * 36);
   pos_calc();
}

ElevatorMachine::~ElevatorMachine()
{
   delete mLifterAnimation;
}

void
ElevatorMachine::pos_calc ()
{
   mLifterAnimation->SetPosition ((float)mx, (float)(my) ); // elevator sprite is only 32x32
}

void
ElevatorMachine::Update (float dt)
{
   switch (mState)
   {
      case LMS_Down :
         mDirection = -1;
         break;
      case LMS_Up :
         mDirection = 1;
         break;
      case LMS_Idle :
         mDirection = 0;
         break;
   }
   mImageFrame += mDirection;
   if ( mImageFrame < 0 )
      mImageFrame = mLastFrame;
   if ( mImageFrame > mLastFrame )
      mImageFrame = mFirstFrame;
   mLifterAnimation->Update (dt);
}

void
ElevatorMachine::Draw ()
{
   this->mcam->Draw( * mLifterAnimation );
}
