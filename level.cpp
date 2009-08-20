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
 
C_level::C_level (int level)
:   m_level (level)
{
    m_y = (C_Camera::get_instance()->get_world_y () ) - (level * 36);
    m_x = C_Camera::get_instance()->get_world_x ();
    m_x2 = 0;
}

void
C_level::add_floor (C_FloorBase * floor)
{
    m_fire_escape_l = new C_AnimationSingle (C_ImageManager::get_instance()->get_image("fire_escape_l.png"));
    m_fire_escape_r = new C_AnimationSingle (C_ImageManager::get_instance()->get_image("fire_escape_r.png"));
    m_floors.push_back (floor);
    if (floor->m_x < m_x)
        m_x = floor->m_x;
    if (floor->m_x2 > m_x2)
        m_x2 = floor->m_x2;
    m_fire_escape_l->set_position (m_x - 24, m_y);
    m_fire_escape_r->set_position (m_x2, m_y);
}

void
C_level::update (float dt)
{
    std::list<C_FloorBase *>::iterator i;
    for (i = m_floors.begin (); i != m_floors.end (); i++)
        (*i)->update (dt);
}

void
C_level::draw ()
{
    std::list<C_FloorBase *>::iterator i;
    for (i = m_floors.begin (); i != m_floors.end (); i++)
        (*i)->draw ();
    C_Camera::get_instance()->draw (*m_fire_escape_l);
    C_Camera::get_instance()->draw (*m_fire_escape_r);
}
