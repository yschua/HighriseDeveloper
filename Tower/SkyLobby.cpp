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

#include "SkyLobby.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "../Graphics/Tiler.h"
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "FloorBase.h"
#include "Level.h"

#include <iostream>
#include <list>

using namespace Gfx;

SkyLobby::SkyLobby(int x, int x2, int level, Tower* TowerParent) : FloorBase(x, x2, level, TowerParent)
{
    mX2 = (float)x2;
    mX = (float)x;
    mY = (float)level * 36;
    mZ = 0.5;
    ImageManager* images = ImageManager::GetInstance();
    mTile = new Tiler(images->GetTexture("SkyLobby.png", GL_RGBA),
                      Tiler::Horizontal,
                      (float)mX,
                      -mY,
                      mZ,
                      (float)(x2 - x),
                      36);
    mTile->SetTessel((float)(x2 - x) / 72, 1.0f);
    std::cout << "New Sky lobby at " << mX << " to " << mX2 << " Y level " << mY << std::endl;
}

void SkyLobby::Update(float dt, int tod) {}

void SkyLobby::Draw()
{
    Render(mTile);
}

void SkyLobby::DrawFramework()
{
    // RenderFramework( mpFrame, id);
}

void SkyLobby::Save(SerializerBase& ser)
{
    ser.Add("type", "SkyLobby"); // first tag
    ser.Add("level", mLevel);    // first tag
    ser.Add("xstart", mX);       // first tag
    ser.Add("xend", mX2);        // first tag
    ser.Add("ystart", mY);       // first tag
    ser.Add("zstart", mZ);       // first tag
    //   ser.Add("state", ToString((mcurrent_state == lobby_occupied_day)?1:0).c_str()); // use the state
    //   engine get this property
    // if something goes bump, either deal with it or throw it
}