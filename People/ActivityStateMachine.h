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

#ifndef _ACTIVITYSTATEMACHINE_H
#define _ACTIVITYSTATEMACHINE_H

#include "IActivityState.h"

#include "../AI/PathAgent.h"

#include <map>

class Person;

class ActivityStateMachine
{
public:
    ActivityStateMachine(Person& person);
    virtual ~ActivityStateMachine();
    void Change(IActivityState::Id id);
    void Update(int time);
private:
    std::map<IActivityState::Id, std::unique_ptr<IActivityState>> m_states;
    PathAgent m_pathAgent;
    IActivityState* m_currentState;
    IActivityState* m_nextState;
};

#endif // _ACTIVITYSTATEMACHINE_H