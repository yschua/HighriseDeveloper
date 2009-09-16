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
#include "../physics.h"
#include "../image.h"
#include "../animation.h"
#include "floorBase.h"

#include "damage.h"

using namespace Gfx;


Damage::Damage (int x, int x2, int level, Tower * TowerParent, AnimationSingle* pFrame)
:  FloorBase (x, x2, level, TowerParent)
,  mFire (64, 32)
{
   mpFrame = pFrame;
   mpFrame->SetPosition (mX, mY);
   ImageManager * image_man = ImageManager::GetInstance ();
   mFire.SetPosition( mX, (mLevel-1) * 36);
   mFire.AddFrame( image_man->GetTexture ("explode.png", GL_RGBA), 220);
   mFire.AddFrame( image_man->GetTexture ("particle1.png", GL_RGBA), 120);
   mFire.AddFrame( image_man->GetTexture ("particle2.png", GL_RGBA), 120);
}

void
Damage::Update (float dt)
{
   // nothing happening
   mFire.Update (20);
}

void
Damage::Draw ()
{
   Render (mpFrame);
   RenderParallax (&mFire, 20);
}
