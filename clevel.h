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

#ifndef _CLEVEL_H
#define _CLEVEL_H

class C_level
{
private:
    std::list<C_floor_base *> m_floors;
    animation_single * m_fire_escape_l;
    animation_single * m_fire_escape_r;
    int m_level;
    int m_x, m_x2, m_y;
    
public:
    C_level (int m_level);
    void add_floor (C_floor_base * floor);
    void update (float dt);
    void draw ();
};

#endif
