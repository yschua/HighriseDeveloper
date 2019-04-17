#ifndef _MAINEVENT_H
#define _MAINEVENT_H

#include "Event.h"

class MainEvent : public EventBase
{
public:
    MainEvent();
    virtual ~MainEvent();
    bool OnClose() override;
    bool OnKeyDown(sf::Keyboard::Key key) override;
    bool IsClosed() const;
    bool IsPaused() const;
    sf::Time GetDt() const;

    static const sf::Time m_dtNormal;
    static const sf::Time m_dtFast;

private:
    sf::Time m_dt; // timestep
    bool m_closed;
    bool m_paused;
};

#endif // _MAINEVENT_H