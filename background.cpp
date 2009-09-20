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
#include <map>
#include <vector>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "tiler.h"

#include "background.h"
#include "highriseException.h"

using namespace Gfx;

namespace Model
{
   const float dawn[4] = { 128,65,128, 240 };      // a color birds might sing to
   const float full[4] = { 250,250,250,255 };      // just short of sunburn
   const float dusk[4] = { 120,85,75, 220 };       // Sailors delight
   const float twilight[4] = { 25,8,40, 220 };     // longwave light
   const float night[4] = { 10,15,18, 20 };        // glow from lights

   int state_times[]=
   {
      60*5+40,    // 5:40am dawn
      60*8+30,    // 9:30am sun up
      60*16+30,   // 4:30pm start the fade
      60*19+20,   // 7:20pm go twilight (afterglow)
      60*21+10    // 9:10pm go dark
   };
}

Background::Background (float width, float height)
{
   ImageManager * images = ImageManager::GetInstance ();
   // sky this will be the sky dome in 3D
   mBackImage = new AnimationSingle (images->GetTexture ("back.png", GL_RGBA), (int)width, (int)height);
   mBackImage->SetPosition(Vector3f( 0, -680, -0.1f )); //cam->GetSceneRect().Left, cam->GetWorldRect().Top - mBackImage->mSprite->GetImage()->GetHeight()) );
   // move the ground down 36 since lobby is at 0

   // Z axis is 0 for now
   mBackBuildings = new Tiler (images->GetTexture ("buildings.png", GL_RGBA), Tiler::Horizontal, 0, -28, -0.09f, width, 64 );
   mBackGround = new Tiler (images->GetTexture ("ground.png", GL_RGBA), Tiler::Horizontal, 0, 0+36, -0.09f, width, 320 );

   mLightState = BLS_Night;
   memset (mRGBALight,0,sizeof(mRGBALight));
   memcpy (mRGBATransition, Model::night, 4); 
   mInTransition = false;
}

void
Background::Update (int TimeOfDay)
{
   mBackImage->SetLightingColor (mRGBALight);
}

void
Background::Draw ()
{
   try
   {
      Render(mBackImage);
      Render(mBackBuildings);
      Render(mBackGround);
   }
   catch( ... )
   {
      throw new HighriseException( "Error in rendering the background" );
   }
}
