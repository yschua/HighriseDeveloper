/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <cstdlib> 
#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "animation.h"
#include "camera.h"
#include "cfloorbase.h"
#include "coffice.h"
#include "image.h"

office_state
C_office::unoccupied_day (float dt)
{
    if (rand () % 50 == 3)
        return s_occupied_day;
    return s_unoccupied_day;
}

office_state
C_office::occupied_day (float dt)
{
    if (rand () % 50 == 3)
        return s_unoccupied_day;
    return s_occupied_day;
}

C_office::C_office (int x, int level)
:   m_current_state (s_unoccupied_day)
{
    image_manager * image_man = image_manager::get_instance ();
    m_level = --level;
    m_x = x;
    m_x2 = x + 72;
    m_y = (camera::get_instance()->get_world_y () ) - (level * 36);
    std::cout << "newly made office is at " << m_x << " , " << m_y << std::endl;
    m_animations[s_occupied_day] = new animation ();
    m_animations[s_occupied_day]->add_frame (image_man->get_image ("office_o_d_1.png"), 1000);
    m_animations[s_occupied_day]->add_frame (image_man->get_image ("office_o_d_2.png"), 1000);
    m_animations[s_occupied_day]->add_frame (image_man->get_image ("office_o_d_3.png"), 1000);
    m_animations[s_occupied_day]->add_frame (image_man->get_image ("office_o_d_4.png"), 1000);
    m_animations[s_occupied_day]->add_frame (image_man->get_image ("office_o_d_5.png"), 1000);
    m_animations[s_occupied_day]->set_position (m_x, m_y);
    m_animations[s_unoccupied_day] = new animation ();
    m_animations[s_unoccupied_day]->add_frame (image_man->get_image ("office_u_d.png"), 1000);
    m_animations[s_unoccupied_day]->set_position (m_x, m_y);
}

void
C_office::update (float dt)
{
    m_animations[m_current_state]->update (dt);
    office_state new_state;
    switch (m_current_state) {
        case s_unoccupied_day :
            new_state = unoccupied_day (dt);
        break;
        case s_occupied_day :
            new_state = occupied_day (dt);
        break;
    }
    m_current_state = new_state;
}

void
C_office::draw ()
{
    camera::get_instance()->draw (*m_animations[m_current_state]);
}
