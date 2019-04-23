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

#include "MainEvent.h"

const float m_fastMultipier = 10.f;

MainEvent::MainEvent(int updateRate) : 
    m_closed(false),
    m_paused(false),
    m_dtNormal(sf::seconds(1.f / updateRate)),
    m_dtFast(m_dtNormal / m_fastMultipier),
    m_dt(m_dtNormal)
{}

MainEvent::~MainEvent() {}

bool MainEvent::IsClosed() const
{
    return m_closed;
}

bool MainEvent::OnClose()
{
    m_closed = true;
    return true;
}

bool MainEvent::OnKeyDown(sf::Keyboard::Key key)
{
    switch (key) {
    case sf::Keyboard::Key::Equal:
        m_dt = m_dtFast;
        break;
    case sf::Keyboard::Key::Hyphen:
        m_dt = m_dtNormal;
        break;
    case sf::Keyboard::Key::Space:
        m_paused = !m_paused;
        break;
    default:
        return false;
    }

    return true;
}

sf::Time MainEvent::GetDt() const
{
    return m_dt;
}

bool MainEvent::IsPaused() const
{
    return m_paused;
}