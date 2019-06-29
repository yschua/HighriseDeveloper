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

#ifndef _ACTIVITYSTATE_H
#define _ACTIVITYSTATE_H

#include "IActivityState.h"

class Person;

class EmptyState : public IActivityState
{
public:
    void Update(int time) override {}
    void Enter() override {}
    void Exit() override {}
    FloorBase* GetLocation() const override { return nullptr; }
};

class HomeState : public IActivityState
{
public:
    HomeState(Person& person);
    void Update(int time) override;
    void Enter() override;
    void Exit() override;
    FloorBase* GetLocation() const override;
private:
    Person& m_person;
};

class WorkState : public IActivityState
{
public:
    WorkState(Person& person);
    void Update(int time) override;
    void Enter() override;
    void Exit() override;
    FloorBase* GetLocation() const override;
private:
    Person& m_person;
};

class LunchState : public IActivityState
{
public:
    LunchState(Person& person);
    void Update(int time) override;
    void Enter() override;
    void Exit() override;
    FloorBase* GetLocation() const override;
private:
    Person& m_person;
};

#endif // _ACTIVITYSTATE_H
