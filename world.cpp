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
#include "physics.h"
#include "routes.h"
#include "Tower/floorBase.h"
#include "Tower/Tower.h"
#include "background.h"
#include "world.h"

#else
#include "../highrisedev.h"
#endif

//using namespace Gfx;
World::World ()
{
}

World::~World ()
{
}

void
World::AddTower (Tower* pTower)
{
   mTowers.push_back (pTower);   // only saved here for drawing
}

void
World::SetBG (Background* pBG)
{
   mpBackground = pBG;
}

void
World::Update (float dt)
{
   std::cout << "World Update method called but it was not implemented" << std::endl;
}

void
World::Draw ()
{
   mpBackground->Draw();
   std::vector<Tower *>::iterator iTower;
   for (iTower = mTowers.begin (); iTower != mTowers.end (); iTower++)
   {
      (*iTower)->Draw( );
   }
}
