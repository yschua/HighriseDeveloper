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

#ifndef _MAINEVENT_H
#define _MAINEVENT_H

#include "Event.h"

class MainEvent : public EventBase
{
public:
    MainEvent(int updateRate);
    virtual ~MainEvent();
    bool OnClose() override;
    bool OnKeyDown(sf::Keyboard::Key key) override;
    bool IsClosed() const;
    bool IsPaused() const;
    sf::Time GetDt() const;

private:
    static const float m_fastMultiplier;
    const sf::Time m_dtNormal;
    const sf::Time m_dtFast;
    sf::Time m_dt; // timestep
    bool m_closed;
    bool m_paused;
};

#endif // _MAINEVENT_H