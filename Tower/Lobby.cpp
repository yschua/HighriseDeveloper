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
#include <list>
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "../Graphics/Image.h"
#include "../Graphics/Tiler.h"
#include "../Graphics/Animation.h"
#include "Level.h"
#include "FloorBase.h"

#include "Lobby.h"

using namespace Gfx;

Lobby::Lobby (int x, int x2, int level, Tower * TowerParent)
:   Level ( level, x, 0, x2, TowerParent )
{
   mX2 = x2;
   mX = x;
   ImageManager * images = ImageManager::GetInstance ();
   if( level > 0 )
   {
      mDesk = NULL;
      mTile = new Tiler (images->GetTexture("skylobby.png", GL_RGBA), Tiler::Horizontal, (float)x+36, 0, 0, (float)(x2-x-36), 36);
      mTile->SetTessel ((float)(x2-x)/72, 1.0f);
   }
   else
   {
      mDesk = new AnimationSingle( images->GetTexture("lobbyA.png", GL_RGBA), 36, 36 );
      mDesk->SetPosition((float)mX, 0);
      mTile = new Tiler (images->GetTexture("lobbyB.png", GL_RGBA), Tiler::Horizontal, (float)x+36, 0, 0, (float)(x2-x-36), 36);
      mTile->SetTessel ((float)(x2-x)/72, 1.0f);
   }
   nFireEscapeLeft->SetPosition ((float)mX - 56, (float)mY);
   nFireEscapeRight->SetPosition ((float)mX2, (float)mY);
   std::cout << "New lobby at " << mX << " to " << mX2 << " Y level " << mY << std::endl;
}

void
Lobby::Update (float dt, int tod)
{

}

void Lobby::Draw ()
{
   if( mDesk != NULL) Render(mDesk);
   Render(mTile);
   Render(nFireEscapeLeft);
   Render(nFireEscapeRight);
}

void Lobby::DrawFramework ()
{
   //RenderFramework( mpFrame, id);
}

void Lobby::Save(SerializerBase& ser)
{
   ser.Add("type", "Lobby");   // first tag
   ser.Add("level", mLevel);   // first tag
   ser.Add("xstart", mX);   // first tag
   ser.Add("xend", mX2);   // first tag
   ser.Add("ystart", mY);   // first tag
   ser.Add("zstart", mZ);   // first tag
//   ser.Add("state", ToString((mcurrent_state == lobby_occupied_day)?1:0).c_str()); // use the state engine get this property
   // if something goes bump, either deal with it or throw it
}