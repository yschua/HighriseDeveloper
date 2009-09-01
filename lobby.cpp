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

Lobby::Lobby (int x, int x2, int level, Tower * TowerParent)
      :   Level ( level, TowerParent )
{
   mx2 = x2;
   mx = x;
   ImageManager * images = ImageManager::GetInstance ();
   cam = Camera::GetInstance ();
   tile = new Tiler (images->GetImg("lobby.png"), Tiler::Horizontal, x, x2, my);
   mfire_escape_l->SetPosition (mx - 56, my);
   mfire_escape_r->SetPosition (mx2, my);
   std::cout << "New lobby at " << mx << " to " << mx2 << " Y level " << my << std::endl;
}

void
Lobby::Update (float dt)
{

}

void
Lobby::Draw ()
{
   cam->Draw (*tile);
   cam->Draw (*mfire_escape_l);
   cam->Draw (*mfire_escape_r);
}
