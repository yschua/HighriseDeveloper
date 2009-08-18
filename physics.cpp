#include <iostream>
#include "physics.h"

body::body ()
{
    m_s.first = 0;
    m_s.second = 0;
    m_v.first = 0;
    m_v.second = 0;
    m_a.first = 0;
    m_a.second = 0;
}

body::body (float x, float y)
{
    m_s.first = x;
    m_s.second = y;
    m_v.first = 0;
    m_v.second = 0;
    m_a.first = 0;
    m_a.second = 0;
}

float
body::get_position_x ()
{
    return m_s.first;
}

float
body::get_position_y ()
{
    return m_s.second;
}

float
body::get_velocity_x ()
{
    return m_v.first;
}

float
body::get_velocity_y ()
{
    return m_v.second;
}

float
body::get_acceleration_x ()
{
    return m_a.first;
}

float
body::get_acceleration_y ()
{
    return m_a.second;
}

void
body::debug_print ()
{
    std::cout << "Body: Position " << m_s.first << " , " << m_s.second << std::endl
              << "Velocity " << m_v.first << " , " << m_v.second << std::endl
              << "Acceleration " << m_a.first << " , " << m_a.second << std::endl;
}

void
body::set_position (float x, float y)
{
    m_s.first = x;
    m_s.second = y;
}

void
body::set_velocity (float x, float y)
{
    m_v.first = x;
    m_v.second = y;
}


void
body::set_acceleration (float x, float y)
{
    m_a.first = x;
    m_a.second = y;
}

void
body::integrate (float dt)
{
    float dt_secs = dt / 1000;
    m_s.first += m_v.first * dt_secs;
    m_s.second += m_v.second * dt_secs;
    m_v.first += m_a.first * dt_secs;
    m_v.second += m_a.second * dt_secs;
}
