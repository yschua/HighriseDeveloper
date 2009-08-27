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

C_Background::C_Background ()
{
   C_ImageManager * images = C_ImageManager::get_instance ();
   cam = C_Camera::get_instance ();
   m_BackImage = new C_AnimationSingle (images->get_image ("back.png"));
   m_BackBuildings = new C_Tiler (images->get_image ("buildings.png"), C_Tiler::Horizontal, 0, cam->get_world_x (), cam->get_world_y () - 360 - 55);
   m_BackGround = new C_Tiler (images->get_image ("ground.png"), C_Tiler::Horizontal, 0, cam->get_world_x (), cam->get_world_y () - 360);
}

void
C_Background::draw ()
{
   cam->draw (*m_BackImage);
   cam->draw (*m_BackBuildings);
   cam->draw (*m_BackGround);
}
