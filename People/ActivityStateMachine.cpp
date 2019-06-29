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

#include "ActivityStateMachine.h"

#include "ActivityState.h"
#include "../Tower/FloorBase.h"

ActivityStateMachine::ActivityStateMachine(Person& person) : m_pathAgent(&person)
{
    using Id = IActivityState::Id;

    m_states[Id::Home] = std::make_unique<HomeState>(person);
    m_states[Id::Work] = std::make_unique<WorkState>(person);
    m_states[Id::Lunch] = std::make_unique<LunchState>(person);

    m_currentState = m_states[Id::Home].get();
}

ActivityStateMachine::~ActivityStateMachine()
{
}

void ActivityStateMachine::Change(IActivityState::Id id)
{
    if (m_currentState) {
        m_currentState->Exit();
    }
    
    m_nextState = m_states[id].get();
    m_pathAgent.StartPathing(m_currentState->GetLocation(), m_nextState->GetLocation());

    m_currentState = nullptr;
}

void ActivityStateMachine::Update(int time)
{
    if (m_pathAgent.IsPathing()) {
        m_pathAgent.UpdatePathing();
        return;
    }

    if (!m_currentState) {
        m_currentState = m_nextState;
        m_currentState->Enter();
    }

    m_currentState->Update(time);
}
