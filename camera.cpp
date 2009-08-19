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

#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "animation.h"
#include "camera.h"

C_Camera * C_Camera::m_instance = NULL;

C_Camera::C_Camera ()
:   m_back_color (0, 0, 0)
{
    m_window = new sf::RenderWindow ();
}

int
C_Camera::get_world_y ()
{
    return m_world_y;
}

int
C_Camera::get_world_x ()
{
    return m_world_x;
}

void
C_Camera::set_max_framerate (int rate)
{
    m_window->SetFramerateLimit (rate);
}

void
C_Camera::set_cam_size (int x, int y)
{
    m_cam_x = x;
    m_cam_y = y;
}

void
C_Camera::set_world_size (int x, int y)
{
    m_world_x = x;
    m_world_y = y;
}

void
C_Camera::create (const std::string & caption)
{
    m_window->Create (sf::VideoMode (m_cam_x, m_cam_y, 32), caption);
}

C_Camera *
C_Camera::get_instance ()
{
    if (m_instance == NULL) {
        m_instance = new C_Camera ();
    }
    return m_instance;
}

void
C_Camera::clear ()
{
    m_window->Clear (m_back_color);
}

void
C_Camera::display ()
{
    m_window->Display ();
}

void
C_Camera::center (int x, int y)
{
    m_s.first = x - (m_cam_x / 2);
    m_s.second = y - (m_cam_y / 2);
}

void
C_Camera::draw (C_Animation & to_draw)
{
    to_draw.sprite->SetPosition (to_draw.get_position_x () - m_s.first, to_draw.get_position_y () - m_s.second);
    m_window->Draw (*to_draw.sprite);
}

void
C_Camera::draw (C_AnimationSingle & to_draw)
{
    to_draw.sprite->SetPosition (to_draw.get_position_x () - m_s.first, to_draw.get_position_y () - m_s.second);
    m_window->Draw (*to_draw.sprite);
}

bool
C_Camera::get_event (sf::Event & event)
{
    return m_window->GetEvent (event);
}
