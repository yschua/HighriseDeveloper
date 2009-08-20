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

C_Body::C_Body ()
{
    m_s.first = 0;
    m_s.second = 0;
    m_v.first = 0;
    m_v.second = 0;
    m_a.first = 0;
    m_a.second = 0;
}

C_Body::C_Body (float x, float y)
{
    m_s.first = x;
    m_s.second = y;
    m_v.first = 0;
    m_v.second = 0;
    m_a.first = 0;
    m_a.second = 0;
}

float
C_Body::get_position_x ()
{
    return m_s.first;
}

float
C_Body::get_position_y ()
{
    return m_s.second;
}

float
C_Body::get_velocity_x ()
{
    return m_v.first;
}

float
C_Body::get_velocity_y ()
{
    return m_v.second;
}

float
C_Body::get_acceleration_x ()
{
    return m_a.first;
}

float
C_Body::get_acceleration_y ()
{
    return m_a.second;
}

void
C_Body::debug_print ()
{
    std::cout << "Body: Position " << m_s.first << " , " << m_s.second << std::endl
              << "Velocity " << m_v.first << " , " << m_v.second << std::endl
              << "Acceleration " << m_a.first << " , " << m_a.second << std::endl;
}

void
C_Body::set_position (float x, float y)
{
    m_s.first = x;
    m_s.second = y;
}

void
C_Body::set_velocity (float x, float y)
{
    m_v.first = x;
    m_v.second = y;
}


void
C_Body::set_acceleration (float x, float y)
{
    m_a.first = x;
    m_a.second = y;
}

void
C_Body::integrate (float dt)
{
    float dt_secs = dt / 1000;
    m_s.first += m_v.first * dt_secs;
    m_s.second += m_v.second * dt_secs;
    m_v.first += m_a.first * dt_secs;
    m_v.second += m_a.second * dt_secs;
    if ((m_v.first > -10) && (m_v.first < 10)) {
        m_v.first = 0;
        m_a.first = 0;
    }
    if ((m_v.second > -10) && (m_v.second < 10)) {
        m_v.second = 0;
        m_a.second = 0;
    }
}
