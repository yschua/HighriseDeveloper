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
:  mlevel (level)
,  mTowerParent (TowerParent)
{
   my = (Camera::GetInstance()->GetWorldY () ) - (mlevel * 36);
   mx = Camera::GetInstance()->GetWorldX ();
   mx2 = 0;
   if (level < 0)
   {
      mfire_escape_l = new AnimationSingle (ImageManager::GetInstance()->GetImg("foundation.png"));
      mfire_escape_r = new AnimationSingle (ImageManager::GetInstance()->GetImg("foundation.png"));
   }
   else if (level > 0)
   {
      mfire_escape_l = new AnimationSingle (ImageManager::GetInstance()->GetImg("fire_escape_l.png"));
      mfire_escape_r = new AnimationSingle (ImageManager::GetInstance()->GetImg("fire_escape_r.png"));
   }
   else
   {
      mfire_escape_l = new AnimationSingle (ImageManager::GetInstance()->GetImg("awn_left.png"));
      mfire_escape_r = new AnimationSingle (ImageManager::GetInstance()->GetImg("awn_right.png"));
   }
}

void
Level::AddFloor (FloorBase * floor)
{
   mfloors.push_back (floor);
   if (floor->mx < mx)
      mx = floor->mx;
   if (floor->mx2 > mx2)
      mx2 = floor->mx2;
   if ( mlevel < 0 )
   {
      mfire_escape_l->SetPosition (mx - 9, my); // pour some concrete
      mfire_escape_r->SetPosition (mx2, my);
   }
   else
   {
      mfire_escape_l->SetPosition (mx - 24, my);
      mfire_escape_r->SetPosition (mx2, my);
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
   Camera::GetInstance()->Draw (*mfire_escape_l);
   Camera::GetInstance()->Draw (*mfire_escape_r);
}
