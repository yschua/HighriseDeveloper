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

#include "../Graphics/Image.h"
#include "FloorBase.h"
#include "../Types/String.h"
#include "Tower.h"
#include "Level.h"

#include "GhostRoom.h"

using namespace Gfx;
//using namespace TowerObjects;

GhostRoom::GhostRoom (int x, int level)
      :  mCurrentState (GS_Invalid)
      ,  FloorBase (x, x + Level::mUnitSize, level, NULL)
      ,  mBase (Level::mUnitSize, 36)
{
   mWidthUnits = 1;
   mOffsetUnits = 0;
}

void GhostRoom::SetState( Ghost_State gs )
{
   const float cfGreen[] = { 0.0f, 255.0f, 63.0f, 127.0f };
   const float cfGray[] = { 127.0f, 63.0f, 63.0f, 127.0f };
   mBase.SetLightingColor( (gs == GS_Valid) ? cfGreen : cfGray );
}

void GhostRoom::SetWidth( int units)
{
   mWidthUnits = units;
   mOffsetUnits = units / 2;
   mBase.SetWidth ((float)units * Level::mUnitSize);
}

void GhostRoom::Move (Vector3f& point)
{
   int x = int(point.x) / Level::mUnitSize - mOffsetUnits;
   int y = int(point.y - 28) / 36;
   mX = (float)(x * Level::mUnitSize);
   mX2 = mX + mBase.GetWidth();
   mY = (float)(y * 36);
   mLevel = int(mY/-36);
   mZ = -0.1f; // point.z;
   mBase.SetPosition (mX, mY);
}

void GhostRoom::Update (Tower* pTower)
{
   if( mLevel > -20 && mLevel < 110 && !(mLevel == 0) )
   {
      Level* level = pTower->GetLevel(mLevel);
      if (level != NULL)
      {
         SetState (level->IsSpaceEmpty((int)mX, (int)mX2) ? GS_Valid : GS_Invalid);
      }
      else
      {
         SetState (GS_Invalid);
      }
   }
   else
   {
      SetState (GS_Invalid);
   }
}

void GhostRoom::Draw ()
{
   RenderRectangle (&mBase);
}

