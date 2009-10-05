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
      ,  FloorBase (x, x + 72, level, NULL)
      ,  mBase (72,36)
{
}

void GhostRoom::SetState( Ghost_State gs )
{
   const float cfGreen[] = { 0.0f, 255.0f, 63.0f, 127.0f };
   const float cfGray[] = { 127.0f, 63.0f, 63.0f, 127.0f };
   mBase.SetLightingColor( (gs == GS_Valid) ? cfGreen : cfGray );
}

void GhostRoom::Move (Vector2f& point)
{
   mX = point.x;
   mX2 = mX + 72;
   mY = point.y;
   mLevel = mY/-36;
   mBase.SetPosition (mX, mY);
}

void GhostRoom::Update (Tower* pTower)
{
   if( mLevel > -20 && mLevel < 110 && !(mLevel == 0) )
   {
      Level* level = pTower->GetLevel(mLevel);
      if (level != NULL)
      {
         SetState (level->IsSpaceEmpty(mX, mX2) ? GS_Valid : GS_Invalid);
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

