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

#include "elevatorPit.h"

class Elevator;

ElevatorPit::ElevatorPit ( int x, int level, Elevator* pElevator )
      :  ElevatorBase( x, level, pElevator )
{
   mx = x;
   mLevel = level;
   //ImageManager * image_man = ImageManager::GetInstance ();
   my = (Camera::GetInstance()->GetWorldRect ().Top ) - (level * 36);
   // std::cout << "New elevator pit at " << mx << ", " << my << std::endl;
   // manimations[s_occupied_day] = new AnimationSingle ();
   // manimations[s_occupied_day]->AddFrame (image_man->GetImg ("liftpit.png"), 1000);
}

ElevatorPit::~ElevatorPit()
{
}

void
ElevatorPit::Update (float dt)
{

}

void
ElevatorPit::Draw ()
{
//    Camera::GetInstance()->Draw (*manimations[mcurrent_state]);
}
