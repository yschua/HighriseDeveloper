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
    integrate (dt);
    m_time += dt;
    if (m_time > m_frames[m_current_frame].second) {
        m_time = 0;
        m_current_frame++;
        if (m_current_frame >= m_frames.size ())
            m_current_frame = 0;
        sprite->SetImage (*m_frames[m_current_frame].first);
    }
}
