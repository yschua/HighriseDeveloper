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

#ifndef _PHYSICS_H
#define _PHYSICS_H

typedef std::pair<float, float> vector2;

class C_Body
{  
public:
    vector2 m_s, m_v, m_a;
    C_Body (float x, float y);
    C_Body ();
    float get_position_x ();
    float get_position_y ();
    float get_velocity_x ();
    float get_velocity_y ();
    float get_acceleration_x ();
    float get_acceleration_y ();
    vector2 get_position ();
    vector2 get_velocity ();
    vector2 get_acceleration ();
    void debug_print ();
    void set_position (float x, float y);
    void set_velocity (float x, float y);
    void set_acceleration (float x, float y);
    void integrate (float dt);
};

#endif
