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

#include "PathAgent.h"

#include "../People/Person.h"
#include "../Routes/RouteBase.h"
#include "../Tower/Tower.h"

PathAgent::PathAgent(Person& person) : m_person(person) {}

PathAgent::~PathAgent() {}

void PathAgent::StartPathing(FloorBase* from, FloorBase* to)
{
    // if from == to == nullptr throw something

    auto tower = (from) ? from->GetTower() : to->GetTower();
    int fromLevel = (from) ? from->GetLevel() : 0;
    int toLevel = (to) ? to->GetLevel() : 0;

    m_path = std::move(tower->FindPath(fromLevel, toLevel));
}

void PathAgent::UpdatePathing()
{
    int currentLevel = m_person.GetCurrent();

    if (currentLevel == m_path->GetDestinationLevel()) {
        EndPathing();
        return;
    }

    if (m_path->IsEnd()) return;

    const auto& req = m_path->GetRouteRequest();

    if (currentLevel != req.m_from) return;

    RoutingRequest reqOld = {req.m_from, req.m_to};
    auto route = req.m_route;

    if (route->SetCallButton(reqOld)) {
        route->LoadPerson(&m_person, reqOld);
    } else {
        route->AddToQueue(currentLevel, &m_person, reqOld);
    }

    m_path->Advance();
}

void PathAgent::EndPathing()
{
    m_path.reset();
}

bool PathAgent::IsPathing() const
{
    return (m_path != nullptr);
}