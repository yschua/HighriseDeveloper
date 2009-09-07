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
#include "../tiler.h"
#include "../animation.h"
#include "level.h"
#include "floorBase.h"

#include "lobby.h"
#else
#include "../highrisedev.h"
#endif

using namespace Gfx;

Lobby::Lobby (int x, int x2, int level, Tower * TowerParent)
:   Level ( level, TowerParent )
{
   mX2 = x2;
   mX = x;
   ImageManager * images = ImageManager::GetInstance ();
//   cam = Camera::GetInstance ();
   tile = new Tiler (images->GetTexture("lobby.png", GL_RGBA), Tiler::Horizontal, x, 0, 0, x2-x, 36);
   nFireEscapeLeft->SetPosition (mX - 56, mY);
   nFireEscapeRight->SetPosition (mX2, mY);
   std::cout << "New lobby at " << mX << " to " << mX2 << " Y level " << mY << std::endl;
}

void
Lobby::Update (float dt)
{

}

void
Lobby::Draw ()
{
//   cam->Draw (*tile);
//   cam->Draw (*nFireEscapeLeft);
//   cam->Draw (*nFireEscapeRight);
   Render(tile);
   Render(nFireEscapeLeft);
   Render(nFireEscapeRight);
}
