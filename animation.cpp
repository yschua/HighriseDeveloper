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

animation::animation ()
{
    m_current_frame = 0;
    m_time = 0;
    sprite = new sf::Sprite ();
}

void
animation::add_frame (sf::Image * image, float duration)
{
    m_frames.push_back (std::pair<sf::Image *, float> (image, duration));
}

void
animation::update (float dt)
{
    m_time += dt;
    if (m_time > m_frames[m_current_frame].second) {
        m_time = 0;
        m_current_frame++;
        if (m_current_frame >= m_frames.size ())
            m_current_frame = 0;
        sprite->SetImage (*m_frames[m_current_frame].first);
    }
}
