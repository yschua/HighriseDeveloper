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

#include <iostream>
#include <SFML/Graphics.hpp>
#include <string.h>
#include <map>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "Camera.h"
#include "interface.h"

using namespace Gfx;

Interface::Interface ()
{
   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("clock.png", GL_RGBA);
   mClock = new AnimationSingle (pTex, 60, 60);
   PosCalc ();
}

void
Interface::PosCalc ()
{
   Camera::GetInstance ();
   mClock->SetPosition ((Camera::GetInstance ()->GetCamRect ().Width() / 2) - 30, 0);
}

void
Interface::Update (float dt)
{

}

void
Interface::Draw ()
{
   Render( mClock );
}
