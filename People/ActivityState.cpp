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

#include "ActivityState.h"

#include "Person.h"
#include "../Tower/Office.h"

#include <iostream>

HomeState::HomeState(Person& person) : m_person(person)
{
}

void HomeState::Update(int time)
{
    if (time > 8 * 60 && time < 14 * 60)
        m_person.GetActivityStateMachine().Change(Id::Work);
}

void HomeState::Enter()
{
    std::cout << m_person.GetId() << " going home\n";
}

void HomeState::Exit()
{
}

FloorBase* HomeState::GetLocation() const
{
    return nullptr;
}

WorkState::WorkState(Person& person) : m_person(person)
{
}

void WorkState::Update(int time)
{
    if (time > 12 * 60 && time < 12 * 60 + 15)
        m_person.GetActivityStateMachine().Change(Id::Lunch);

    if (time > 17 * 60)
        m_person.GetActivityStateMachine().Change(Id::Home);
}

void WorkState::Enter()
{
    std::cout << m_person.GetId() << " going to work\n";

    auto office = static_cast<Office*>(m_person.GetWorkID());
    office->PeopleInOut(1);
}

void WorkState::Exit()
{
    auto office = static_cast<Office*>(m_person.GetWorkID());
    office->PeopleInOut(-1);
}

FloorBase* WorkState::GetLocation() const
{
    return m_person.GetWorkID();
}

LunchState::LunchState(Person& person) : m_person(person)
{
}

void LunchState::Update(int time)
{
    if (time > 13 * 60)
        m_person.GetActivityStateMachine().Change(Id::Work);
}

void LunchState::Enter()
{
    std::cout << m_person.GetId() << " going to lunch\n";
}

void LunchState::Exit()
{
}

FloorBase* LunchState::GetLocation() const
{
    return 0;
}
