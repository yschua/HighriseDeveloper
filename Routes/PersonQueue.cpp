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

#include "PersonQueue.h"

#include "../People/Person.h"
//#include "Elevator.h"

PersonQueue::PersonQueue()
{
}

void PersonQueue::AddPerson(Person* person, int to)
{
    m_queue.push(std::make_pair(person, to));
}

std::pair<Person*, int> PersonQueue::TakeNextPerson()
{
    if (m_queue.empty()) return std::make_pair(nullptr, 0);

    auto person = m_queue.front();
    m_queue.pop();
    return person;
}

void PersonQueue::Update()
{
}

void PersonQueue::Draw(int vx, int vy)
{
}
