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
   cam = Camera::GetInstance ();
   int width = cam->GetWorldRect().Right - cam->GetWorldRect().Left;
   int height = cam->GetWorldRect().Bottom - cam->GetWorldRect().Top;
   // sky this will be the sky dome in 3D
   mBackImage = new AnimationSingle (images->GetTexture ("back.png", GL_RGBA), width, height);
   mBackImage->SetPosition(Vector2f( 0, -680 )); //cam->GetWorldRect().Left, cam->GetWorldRect().Top - mBackImage->mSprite->GetImage()->GetHeight()) );
   // move the ground down 36 since lobby is at 0

   // Z axis is 0 for now
   mBackBuildings = new Tiler (images->GetTexture ("buildings.png", GL_RGBA), Tiler::Horizontal, cam->GetWorldRect().Left, -28, 0, width, 64 );
   mBackGround = new Tiler (images->GetTexture ("ground.png", GL_RGBA), Tiler::Horizontal, cam->GetWorldRect().Left, cam->GetWorldRect().Top+36, 0, width, 320 );
}

void
Background::Draw ()
{
   try
   {
      glMatrixMode(GL_MODELVIEW);
      glPushMatrix();
      {                       // brackets just keep the code in push and pop uniform
         glTranslatef (cam->GetPositionX(), -(cam->GetPositionY()), 0);
         Render(mBackImage);
         Render(mBackBuildings);
         Render(mBackGround);
      }
   glPopMatrix();
   }
   catch( ... )
   {
      throw new HighriseException( "Error in rendering the background" );
   }
}
