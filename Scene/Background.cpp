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
#include "../Root/Physics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Graphics/Tiler.h"

#include "Background.h"
#include "../Root/HighRiseException.h"

using namespace Gfx;

namespace Model
{
   const float RGBSkyColors[8][4] =
   {
      {  15,  20,  38,  80 }, // night glow from lights
      { 178,  185, 168, 148 }, // dawn a color birds might sing to
      { 250, 250, 250, 255 }, // day just short of sunburn
      { 250, 105,  75, 190 }, // early eve Sailors delight
      {  95,  45,  90,  90 }, // late eve longwave light
      {  45,  35,  78,  80 }, // night glow from lights
      {  25,  25,  58,  80 }, // night glow from lights
      { 200, 250, 120, 255 }  // not good
   };
   int state_times[]=
   {
      60*5+30,    // 6:10am dawn
      60*7+45,    // 7:45am sun up
      60*17+10,   // 5:10pm start the fade
      60*19+20,   // 7:20pm go twilight (afterglow)
      60*21+10,   // 9:10pm go dark
      60*23+50    //11:50pm reset
   };
}

Background::Background (float left, float top, float width, float height)
{
   ImageManager * images = ImageManager::GetInstance ();
   // sky this will be the sky dome in 3D
   mBackImage = new AnimationSingle (images->GetTexture ("Back.png", GL_RGBA), (int)width, (int)height);
   mBackImage->SetPosition(Vector3f( left, top, -0.1f )); //cam->GetSceneRect().Left, cam->GetWorldRect().Top - mBackImage->mSprite->GetImage()->GetHeight()) );
   mBackImage->SetLightingColor (mRGBALight);
   // move the ground down 36 since lobby is at 0

   // Z axis is 0 for now
   mBackBuildings = new Tiler (images->GetTexture ("Buildings.png", GL_RGBA), Tiler::Horizontal, left, -36, -0.09f, width, 72 );
   mBackGround = new Tiler (images->GetTexture ("Ground.png", GL_RGBA), Tiler::Horizontal, left, 0+36, -0.09f, width, 320 );

   mLightState = BLS_Night;
   memset (mRGBATransition, 0, sizeof(mRGBALight));
   memcpy (mRGBALight, Model::RGBSkyColors[0], 4*sizeof(float));
   mStepsToTransition = 0;
   mNextTimeEvent = Model::state_times[0];
}

void
Background::Update (int TimeOfDay)
{
   mBackImage->SetLightingColor (mRGBALight);
   if( mStepsToTransition < 0 )
   {
      mStepsToTransition = 0;
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
      mStepsToTransition = int(2*fabs(pRGB[3] - mRGBALight[3])); // starts trasition
      if( mStepsToTransition > 0 )
      {
         mRGBATransition[0] = (pRGB[0] - mRGBALight[0]) / mStepsToTransition;
         mRGBATransition[1] = (pRGB[1] - mRGBALight[1]) / mStepsToTransition;
         mRGBATransition[2] = (pRGB[2] - mRGBALight[2]) / mStepsToTransition;
         mRGBATransition[3] = (pRGB[3] - mRGBALight[3]) / mStepsToTransition;
      }
   }
}

void
Background::Draw ()
{
   try
   {
      if (mStepsToTransition > 0)
      {
         mRGBALight[0] += mRGBATransition[0];
         mRGBALight[1] += mRGBATransition[1];
         mRGBALight[2] += mRGBATransition[2];
         mRGBALight[3] += mRGBATransition[3];
         mStepsToTransition--;
         mBackImage->SetLightingColor(mRGBALight);
         if( !(mLightState == BLS_Reset || mLightState == BLS_Night) )
         {
            mBackBuildings->SetLightingColor(mRGBALight); // keep these semi lit
         }
      }

      Render(mBackImage, true);
      Render(mBackBuildings, true);
      Render(mBackGround);
   }
   catch( ... )
   {
      throw new HighriseException( "Error in rendering the background" );
   }
}
