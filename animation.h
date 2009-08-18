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

#ifndef _ANIMATION_H
#define _ANIMATION_H

class animation : public body
{
private:
    std::vector<std::pair<sf::Image *, float> > m_frames;
    int m_current_frame;
    float m_time;
    
public:
    animation ();
    void add_frame (sf::Image * image, float duration);
    void update (float dt);
    sf::Sprite * sprite;
};

#endif
