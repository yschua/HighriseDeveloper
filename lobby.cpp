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

C_Lobby::C_Lobby (int x, int x2, int level)
:   m_level (level + 11)
{
   m_x = x;
   m_x2 = x2;
   C_ImageManager * images = C_ImageManager::get_instance ();
   cam = C_Camera::get_instance ();
   m_y = (cam->get_world_y ()) - (m_level * 36);
   tile = new C_Tiler (images->get_image("lobby.png"), C_Tiler::Horizontal, x, x2, m_y);
   awn_left = new C_AnimationSingle (images->get_image ("awn_left.png"));
   awn_right = new C_AnimationSingle (images->get_image ("awn_right.png"));
   pos_calc ();
}

void
C_Lobby::pos_calc ()
{
   awn_left->set_position (m_x - 56, m_y);
   awn_right->set_position (m_x2, m_y);
   std::cout << "New lobby at " << m_x << " to " << m_x2 << " Y level " << m_y << std::endl;
}

void
C_Lobby::update (float dt)
{

}

void
C_Lobby::draw ()
{
   cam->draw (*tile);
   cam->draw (*awn_left);
   cam->draw (*awn_right);
}