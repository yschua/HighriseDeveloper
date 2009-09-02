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
#include "../physics.h"
#include "../animation.h"
#include "../tiler.h"
#include "../camera.h"
#include "../image.h"

#include "elevatorShaft.h"

using namespace Gfx;

ElevatorShaft::ElevatorShaft ( int x, int topLevel, int bottomLevel, Elevator* pElevator )
      :  ElevatorBase( x, bottomLevel, pElevator )
{
   mx = x;
   mTopLevel = topLevel;
   mBottomLevel = bottomLevel;
   ImageManager * images = ImageManager::GetInstance ();
   mcam = Camera::GetInstance ();
   mShaftTiler = new Tiler (images->GetImg ("liftshaft.png"), Tiler::Vertical,
                               mcam->GetWorldRect ().Top - (mTopLevel * 36),
                               mcam->GetWorldRect ().Top - ((mBottomLevel - 1) * 36), mx );
}

ElevatorShaft::~ElevatorShaft()
{
}

void
ElevatorShaft::Update (float dt)
{

}

void
ElevatorShaft::Draw ()
{
   mcam->Draw (*mShaftTiler);
}
