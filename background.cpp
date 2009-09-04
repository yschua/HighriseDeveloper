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
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "camera.h"
#include "animation.h"
#include "tiler.h"
//#include "floorBase.h"

#include "background.h"
#else
#include "highrisedev.h"
#endif
#include "highriseException.h"

using namespace Gfx;

Background::Background ()
{
   ImageManager * images = ImageManager::GetInstance ();
   cam = Camera::i();
   // sky this will be the sky dome in 3D
   mBackImage = new AnimationSingle (images->GetImg ("back.png"));
   mBackImage->SetPosition(Vector2f( cam->GetWorldRect().Left, cam->GetWorldRect().Top - mBackImage->mSprite->GetImage()->GetHeight()) );
   // move the ground down 36 since lobby is at 0
   mBackBuildings = new Tiler (images->GetImg ("buildings.png"), Tiler::Horizontal, cam->GetWorldRect().Left, cam->GetWorldRect().Right, cam->GetWorldRect().Top + 36 - 64);
   mBackGround = new Tiler (images->GetImg ("ground.png"), Tiler::Horizontal, cam->GetWorldRect().Left, cam->GetWorldRect().Right, cam->GetWorldRect().Top + 36);
}

void
Background::Draw ()
{
   try
   {
      cam->Draw (*mBackImage);
      cam->Draw (*mBackBuildings);
      cam->Draw (*mBackGround);
   }
   catch( ... )
   {
      throw new HighriseException( "Error in rendering the background" );
   }
}
