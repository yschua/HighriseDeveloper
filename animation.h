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

#ifndef _ANIMATION_H
#define _ANIMATION_H

class C_Animation : public C_Body
{
private:
    std::vector<std::pair<sf::Image *, float> > m_frames;
    int m_current_frame;
    float m_time;
    
public:
    C_Animation ();
    void add_frame (sf::Image * image, float duration);
    void update (float dt);
    sf::Sprite * sprite;
};

class C_AnimationSingle : public C_Body
{
public:
    sf::Sprite * sprite;
    C_AnimationSingle (sf::Image * image);
    void SetSubRect (int x1, int y1, int x2, int y2);
};

#endif
