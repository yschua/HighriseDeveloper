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
#include <cstring>
#include <vector>
#include "physics.h"
#include "image.h"
#include "Animation.h"
#include "tiler.h"

#include "background.h"
#include "highriseException.h"

using namespace Gfx;

namespace Model
{
   const float RGBSkyColors[8][4] =
   {
      {  10,  15,  18,  20 }, // night glow from lights
      { 188,  95, 188, 148 }, // dawn a color birds might sing to
      { 250, 250, 250, 255 }, // day just short of sunburn
      { 250, 105,  75, 190 }, // early eve Sailors delight
      {  25,  25,  90,  90 }, // late eve longwave light
      {  10,  15,  18,  20 }, // night glow from lights
      { 200, 250, 120, 255 }  // not good
   };
   int state_times[]=
   {
      60*6+10,    // 6:10am dawn
      60*7+45,    // 7:45am sun up
      60*17+10,   // 5:10pm start the fade
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
   mBackImage->SetLightingColor (mRGBALight);
   // move the ground down 36 since lobby is at 0

   // Z axis is 0 for now
   mBackBuildings = new Tiler (images->GetTexture ("buildings.png", GL_RGBA), Tiler::Horizontal, 0, -28, -0.09f, width, 64 );
   mBackGround = new Tiler (images->GetTexture ("ground.png", GL_RGBA), Tiler::Horizontal, 0, 0+36, -0.09f, width, 320 );

   mLightState = BLS_Night;
   memset (mRGBATransition, 0, sizeof(mRGBALight));
   memcpy (mRGBALight, Model::RGBSkyColors[0], 4*sizeof(float));
   mStepsToTansion = 0;
   mNextTimeEvent = Model::state_times[0];
}

void
Background::Update (int TimeOfDay)
{
   mBackImage->SetLightingColor (mRGBALight);
   if( mStepsToTansion < 0 )
   {
      mStepsToTansion = 0;
   }
   if (TimeOfDay > Model::state_times[mLightState] || mLightState == BLS_Reset)
   {
      switch(mLightState)
      {
         case BLS_Night:
            mLightState = BLS_Dawn;
            break;
         case BLS_Dawn:
            mLightState = BLS_Day;
            break;
         case BLS_Day:
            mLightState = BLS_Dusk;
            break;
         case BLS_Dusk:
            mLightState = BLS_Twilight;
            break;
         case BLS_Twilight:
            mLightState = BLS_Reset;
            break;
         case BLS_Reset:
            mLightState = BLS_Night;
            break;
         default:
            throw new HighriseException ("State error in Background Image");
      }
      const float* pRGB = Model::RGBSkyColors[mLightState];
      mStepsToTansion = (int)fabs(pRGB[3] - mRGBALight[3]); // starts trasition
      if( mStepsToTansion > 0 )
      {
         mRGBATransition[0] = (pRGB[0] - mRGBALight[0]) / mStepsToTansion;
         mRGBATransition[1] = (pRGB[1] - mRGBALight[1]) / mStepsToTansion;
         mRGBATransition[2] = (pRGB[2] - mRGBALight[2]) / mStepsToTansion;
         mRGBATransition[3] = (pRGB[3] - mRGBALight[3]) / mStepsToTansion;
      }
   }
}

void
Background::Draw ()
{
   try
   {
      if (mStepsToTansion > 0)
      {
         mRGBALight[0] += mRGBATransition[0];
         mRGBALight[1] += mRGBATransition[1];
         mRGBALight[2] += mRGBATransition[2];
         mRGBALight[3] += mRGBATransition[3];
         mStepsToTansion--;
         mBackImage->SetLightingColor(mRGBALight);
      }

      Render(mBackImage, true);
      Render(mBackBuildings);
      Render(mBackGround);
   }
   catch( ... )
   {
      throw new HighriseException( "Error in rendering the background" );
   }
}
