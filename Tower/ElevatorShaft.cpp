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
#include "../Physics.h"
#include "../Animation.h"
#include "../Tiler.h"
#include "../Image.h"

#include "ElevatorShaft.h"

using namespace Gfx;

ElevatorShaft::ElevatorShaft ( int x, int topLevel, int bottomLevel, Elevator* pElevator )
      :  ElevatorBase( x, bottomLevel, pElevator )
{
   mx = x;
   this->
   mTopLevel = topLevel;
   mBottomLevel = bottomLevel;
   ImageManager * images = ImageManager::GetInstance ();
   mShaftTiler = new Tiler (images->GetTexture ("liftshaft.png", GL_RGBA), Tiler::Vertical, mx,
                               ((mBottomLevel) * -36), 0, 36, ((mTopLevel-mBottomLevel) * -36));
   mShaftTiler->SetTessel( 1, (mTopLevel-mBottomLevel ));
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
   Render(mShaftTiler);
}