#include "MainEvent.h"

const sf::Time MainEvent::m_dtNormal = sf::milliseconds(10);
const sf::Time MainEvent::m_dtFast = sf::milliseconds(1);

MainEvent::MainEvent() : m_closed(false), m_paused(false), m_dt(m_dtNormal) {}

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