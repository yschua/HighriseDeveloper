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

#include "highrisedev.h"
//#include "Graphics/Graphics.h"
using namespace Gfx;

Interface::Interface ()
{
   ImageManager * images = ImageManager::GetInstance ();
   mpCam = Camera::GetInstance ();
   Texture* pTex = images->GetTexture ("clock.png", GL_RGBA);
   mClock = new AnimationSingle (pTex, 60, 60); //images->GetImg ("clock.png"));
   PosCalc ();
}

void
Interface::PosCalc ()
{
   mClock->SetPosition ((mpCam->GetCamRect ().Width() / 2) - 30, 0);
}

void
Interface::Update (float dt)
{

}

void
Interface::Draw ()
{
   mpCam->SetStatic (true);
   mpCam->Draw (*mClock);
   mpCam->SetStatic (false);
}
