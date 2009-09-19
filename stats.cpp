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
#include "stats.h"

using namespace Gfx;

Stats::Stats ()
{
   mNet = 100000;
   mPopulation = 0;
   mStars = 1;
   

   ImageManager * images = ImageManager::GetInstance ();
   Texture* pTex = images->GetTexture ("stats.png", GL_RGBA);
   mStatsFace = new AnimationSingle (pTex, 256, 16);
   PosCalc ();

}

Stats::~Stats ()
{
}

void
Stats::PosCalc ()
{
   Camera::GetInstance ();
   mStatsFace->SetPosition ((Camera::GetInstance ()->GetCamSize ().x / 2) - 128, -15); // relative based on clock
}

void
Stats::Update ()
{
   char buf[32];
   itoa( mNet, buf, 10 );
   mstrNet = std::string (buf);
   itoa( mPopulation, buf, 10 );
   mstrPopulation = std::string (buf);
}

namespace UI
{
   const float StatBarUVs[4][2] =   // stats.png
   {
      { 0.0, 0.0 },
      { 0.0, 0.5 },
      { 1.0, 0.5 },
      { 1.0, 0.0 }
   };
}

void
Stats::Draw ()
{
   Render( mStatsFace, UI::StatBarUVs );
   float x = mStatsFace->GetPositionX();
   float y = mStatsFace->GetPositionY()+2;
   RenderText( mStatsFace, x+40, y, mstrNet);
   RenderText( mStatsFace, x+158, y, mstrPopulation);
}
