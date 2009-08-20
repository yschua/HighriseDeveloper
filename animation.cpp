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

C_Animation::C_Animation ()
{
    m_current_frame = 0;
    m_time = 0;
    sprite = new sf::Sprite ();
}

void
C_Animation::add_frame (sf::Image * image, float duration)
{
    m_frames.push_back (std::pair<sf::Image *, float> (image, duration));
}

void
C_Animation::update (float dt)
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

C_AnimationSingle::C_AnimationSingle (sf::Image * image)
{
    sprite = new sf::Sprite ();
    sprite->SetImage (*image);
}

void
C_AnimationSingle::SetSubRect (int x1, int y1, int x2, int y2)
{
    sf::IntRect * subrect = new sf::IntRect (x1, y1, x2, y2);
    sprite->SetSubRect (*subrect);
}
