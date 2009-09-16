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

#include <map>
#include <cstring>
#include "image.h"
#include "animation.h"
#include "Camera.h"
#include "clock.h"

using namespace Gfx;

namespace Gfx
{
   const unsigned char kszColor0[] = { 16,16,16,255 }; // dark charcoal
   const unsigned char kszColor1[] = { 126,136,36,255 }; // dark dold
   const unsigned char kszColor2[] = { 142,150,42,255 }; // light gold
}

Clock::Clock ()
{
   mTimeOfDay = 0;
   mDayOfYear = 1;
   mYear = 1950;

   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("clock.png", GL_RGBA);
   mClockFace = new AnimationSingle (pTex, 64, 64);
   PosCalc ();

   // cut out some hands based on a 64x64 clock face
   // these are the vectors for rendering the hands.
   // Hour and minute angles will transform them to 360 degs of turn.
   mMinuteHand.Points[0] = Vector3f ( 0,   0, 0);
   mMinuteHand.Points[1] = Vector3f (-3, -18, 0);
   mMinuteHand.Points[2] = Vector3f ( 3, -18, 0);
   mMinuteHand.Points[3] = Vector3f ( 0, -30, 0);
   memcpy( mMinuteHand.Colors[0], kszColor0, 4 );
   memcpy( mMinuteHand.Colors[1], kszColor1, 4 );
   memcpy( mMinuteHand.Colors[2], kszColor1, 4 );
   memcpy( mMinuteHand.Colors[3], kszColor0, 4 );
   mHourHand.Points[0] = Vector3f ( 0,   0, 0);
   mHourHand.Points[1] = Vector3f (-4, -11, 0);
   mHourHand.Points[2] = Vector3f ( 4, -11, 0);
   mHourHand.Points[3] = Vector3f ( 0, -22, 0);
   memcpy( mHourHand.Colors[0], kszColor0, 4 );
   memcpy( mHourHand.Colors[1], kszColor2, 4 );
   memcpy( mHourHand.Colors[2], kszColor2, 4 );
   memcpy( mHourHand.Colors[3], kszColor0, 4 );
}

void
Clock::PosCalc ()
{
   Camera::GetInstance ();
   mClockFace->SetPosition ((Camera::GetInstance ()->GetCamSize ().x / 2) - 32, 0);
   mHourHand.Position = Vector3f((Camera::GetInstance ()->GetCamSize ().x / 2), 32, 100.2f );
   mMinuteHand.Position = Vector3f((Camera::GetInstance ()->GetCamSize ().x / 2), 32, 100.1f );
}

void
Clock::Update (int minutes)
{
   mTimeOfDay += minutes;
   if (mTimeOfDay > 23*60+59)   // only 1440 minutes in a day
   {
      mTimeOfDay -= 24*60;
      mDayOfYear++;
      if (mDayOfYear > 365)
      {
         mDayOfYear = 1;
         mYear++;
      }
   }
   int mins = mTimeOfDay % 60;
   int hours = mTimeOfDay / 60;
   mHourHand.Angle = 360.0f / 24 * hours;
   mMinuteHand.Angle =  360.0f / 60 * mins;
}

void
Clock::Draw ()
{
   Render( mClockFace );
   Render( &mHourHand );
   Render( &mMinuteHand );
}
