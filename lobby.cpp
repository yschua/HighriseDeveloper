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

using namespace Graphics;

C_Lobby::C_Lobby (int x, int x2, int level, C_Tower * TowerParent)
      :   C_level ( level, TowerParent )
{
   m_x2 = x2;
   m_x = x;
   C_ImageManager * images = C_ImageManager::GetInstance ();
   cam = C_Camera::GetInstance ();
   tile = new C_Tiler (images->GetImg("lobby.png"), C_Tiler::Horizontal, x, x2, m_y);
   m_fire_escape_l->SetPosition (m_x - 56, m_y);
   m_fire_escape_r->SetPosition (m_x2, m_y);
   std::cout << "New lobby at " << m_x << " to " << m_x2 << " Y level " << m_y << std::endl;
}

void
C_Lobby::Update (float dt)
{

}

void
C_Lobby::Draw ()
{
   cam->Draw (*tile);
   cam->Draw (*m_fire_escape_l);
   cam->Draw (*m_fire_escape_r);
}
