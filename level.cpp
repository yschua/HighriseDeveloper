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

#include "highrisedev.h"

using namespace Gfx;

Level::Level (int level, Tower * TowerParent)
:  mTowerParent (TowerParent)
{
   mLevel = level;
   mY = (Camera::GetInstance()->GetWorldRect ().Top ) - (mLevel * 36);
   mX = Camera::GetInstance()->GetWorldRect ().Left;
   mX2 = 0;

   if (level < 0)
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetImg("foundation.png"));
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetImg("foundation.png"));
   }
   else if (level > 0)
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetImg("fire_escape_l.png"));
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetImg("fire_escape_r.png"));
   }
   else
   {
      nFireEscapeLeft = new AnimationSingle (ImageManager::GetInstance()->GetImg("awn_left.png"));
      nFireEscapeRight = new AnimationSingle (ImageManager::GetInstance()->GetImg("awn_right.png"));
   }
}

void
Level::AddFloor (FloorBase * floor)
{
   mfloors.push_back (floor);
   if (floor->mX < mX)
      mX = floor->mX;
   if (floor->mX2 > mX2)
      mX2 = floor->mX2;
   if ( mLevel < 0 )
   {
      nFireEscapeLeft->SetPosition (mX - 9, mY); // pour some concrete
      nFireEscapeRight->SetPosition (mX2, mY);
   }
   else
   {
      nFireEscapeLeft->SetPosition (mX - 24, mY);
      nFireEscapeRight->SetPosition (mX2, mY);
   }
}

void
Level::Update (float dt)
{
   std::vector<FloorBase *>::iterator i;
   for (i = mfloors.begin (); i != mfloors.end (); i++)
      (*i)->Update (dt);
}

void
Level::Draw ()
{
   std::vector<FloorBase *>::iterator i;
   for (i = mfloors.begin (); i != mfloors.end (); i++)
      (*i)->Draw ();
   Camera::GetInstance()->Draw (*nFireEscapeLeft);
   Camera::GetInstance()->Draw (*nFireEscapeRight);
}
