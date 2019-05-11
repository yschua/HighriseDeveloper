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

// When somone wants to go somewhere, just hand them over to their own personal travel agent.
// "MyPathAgent 2500 will take you to your destination quickly and safely, only 19.95 + S&H"
// The Citizens Agent will hand people to this agent when they enter a travel state.
// A location and destination will be set for the person(s) preparing to embark. The path agent will
// then find the best path to that destination. Folks in the tower(s) will be transitioned from
// point to point. The nearest elevalor is found and enqueued. Should the wait time exceed A limt
// the PA will look for the another elevator close by that stops on the level desired. It found then
// the person procedes there. If time exceeds A&B limit then a moderate distance is searched. Same
// for limit C but forther. If still no satifaction, enter drastic mode( leave, move etc).

#include "CitizensAgent.h"

#include "../People/Citizens.h"
#include "../People/Person.h"
#include "../Root/HighRiseException.h"
#include "../Tower/Level.h"
#include "../Tower/Office.h"
#include "../Tower/PersonQueue.h"
#include "../Tower/RouteBase.h"
#include "../Tower/Routes.h"
#include "../Tower/Tower.h"
#include "FloorAgent.h"
#include "PathAgent.h"

#include <cstdlib>
#include <iostream>
#include <list>
#include <vector>

CitizensAgent::CitizensAgent(Tower& tower) : mTower(tower) {}

CitizensAgent::~CitizensAgent() {}

void CitizensAgent::Update(int tod)
{
    // Shouldn't Citizens be a member within each Tower? Supposedly you would want this seperate.
    Citizens* citizens = Citizens::get_Instance(); // the citizens object that holds the people collection

    // TODO: need a better spawn mechanism, raised to 100
    size_t limit = 10;
    if (citizens->get_Persons().size() < limit) {
        // Location loc; // all zeros
        Person* peep = citizens->CreateNewPerson();
        //      Person* peep = new Person( loc );
        //      mPeople.push_back( peep );
        // Shouldn't this be Update(dt)?
        //citizens->Update(dt);
        // log      std::cout << "Your city added 1 person" << " Population in city: " <<
        // citizens->GetPopulation() << std::endl;
    }

    for (Person* person : citizens->get_Persons()) {
        person->Update(tod);
        // use a state engine to replace this
        switch (person->get_Activity()) {
        case Person::AS_JobHunting:
            JobHunting(person, tod);
            break;
        case Person::AS_CondoHunting:
            CondoHunting(person);
            break;
        case Person::AS_ApartmentHunting:
            ApartmentHunting(person);
            break;
        case Person::AS_GoingToWork:
            GoingToWork(person);
            break;
        case Person::AS_ClockingOut:
            ClockingOut(person);
            break;
        case Person::AS_GoingHome:
            GoingHome(person);
            break;
        case Person::AS_LunchBreak:
            LunchBreak(person, tod);
            break;
        default:
            break;
        }
    }
}

void CitizensAgent::RoutePerson(int index, Path& Path, Person* peep)
{
    Routes& routeList = mTower.GetRoutes();
    if (routeList.GetRoutes().size() > 0) {
        RoutingRequest req; // routing code needs to queue this person
        req.OriginLevel = peep->GetCurrent();
        req.DestinLevel = Path.mPathList[index].mLevel;

        if (req.OriginLevel == req.DestinLevel) return;

        int rte = Path.mPathList[index].mRoute;
        if (rte >= 0 && rte < static_cast<int>(routeList.GetRoutes().size())) {
            RouteBase* route = routeList.GetRoutes()[rte];
            bool IsBoarding = route->SetCallButton(req);
            if (IsBoarding) {
                peep->SetCurrentState(Person::CS_Riding);
                route->LoadPerson(peep, req);
            } else {
                peep->SetCurrentState(Person::CS_Waiting);
                // Level* pLevel = mTower.GetLevel(curLevel);
                PersonQueue* pQ = route->FindQueue(peep->GetCurrent());
                if (pQ) {
                    peep->get_WorkPath().index = index;
                    pQ->AddPerson(peep);
                }
            }
        }
    }
}

void CitizensAgent::Draw()
{
    Citizens* citizens = Citizens::get_Instance(); // the citizens object that holds the people collection
    std::list<Person*>::iterator i;
    std::list<Person*>& persons = citizens->get_Persons(); // get the persons collection.

    // TODO: Need to create a better interface that provides a clear persons iteration.
    for (i = persons.begin(); i != persons.end(); i++) {
        Person* peep = (*i);
        if (peep && peep->GetCurrentState() == Person::AS_JobHunting) {
            peep->Draw(320, 36); // standing outside
        }
    }
}

void CitizensAgent::JobHunting(Person* person, int tod)
{
    if (person->GetCurrentState() == Person::CS_Idle) {
        FloorAgent agent(mTower);
        FloorBase* pFB = agent.FindWork(0);
        if (pFB != NULL) {
            Location dest;
            dest.mBuilding = 1;
            dest.mLevel = pFB->GetLevel(); // TODO:  get a real job finder
            dest.mRoute = 0; // plugged into first elevater until pathfinder does the job.
            dest.mX = 1;     // TODO:  find the room number
                             // Log               std::cout << "A new person has entered your building looking for work
                             // on Level# " << dest.mLevel << std::endl;
            if (tod >= 6 * 60 && tod < 16 * 60) {
                person->SetActivity(Person::AS_GoingToWork);
            } else {
                person->SetActivity(Person::AS_Sleeping);
            }
            if ((rand() % 6) ==
                2) // one out of 6 will make good money to afford more than an apartment
                person->SetOccupation(2);
            else
                person->SetOccupation(1);
            person->SetWorkID(pFB->GetID());
            PathAgent Path(person);
            Path.findPath(person->get_Location(), dest, mTower);

            mTower.EnterTower(person);
        }
    }
}

void CitizensAgent::CondoHunting(Person* person)
{
    FloorAgent agent(mTower);
    FloorBase* pFB = agent.FindAHome(1); // condo
    if (pFB != NULL) {
        pFB->SetOwner(person);
        mTower.AdjustFunds(pFB->GetSalePrice()); // buy condo
        person->SetResidence(pFB->GetLevel());
        person->SetActivity(Person::AS_GoingHome);
        person->SetCurrentState(Person::CS_Idle);
    } else {
        person->SetActivity(Person::AS_ApartmentHunting);
    }
}

void CitizensAgent::ApartmentHunting(Person* person)
{
    // Set up cheap housing (not in the original tower game.
    FloorAgent agent(mTower);
    FloorBase* pFB = agent.FindAHome(0);
    if (pFB != NULL) {
        pFB->SetOwner(person);
        mTower.AdjustFunds(100); // lease
        person->SetResidence(pFB->GetLevel());
        person->SetActivity(Person::AS_GoingHome);
        person->SetCurrentState(Person::CS_Idle);
    }
    // else keep looking
}

void CitizensAgent::GoingToWork(Person* person)
{
    Path& workPath = person->get_WorkPath(); // for now just doing work
    if (workPath.index < workPath.size) {
        int idx = workPath.index;
        int curLevel = person->get_Location().mLevel;

        if (curLevel == workPath.mPathList[idx].mLevel) 
        { // or tower is not = curtower (on a bus, train, car or skycab ).
            // just moving on the same level
        } else {
            switch (person->GetCurrentState()) {
            case Person::CS_Waiting:
                // tally up wait states
                break;
            case Person::CS_Riding:
                // enroute
                break;
            case Person::CS_Disembarking:
                person->SetCurrent(workPath.mPathList[idx].mLevel);
                curLevel = workPath.mPathList[idx].mLevel;
                workPath.index++;
                person->SetCurrentState(Person::CS_Walking);
                idx = workPath.index;
                // fall through
            default:
                RoutePerson(idx, workPath, person);
            }
            // workPath.index++; // TODO: wait for elevator, we are moving ahead before getting to the
            // level
            if (workPath.index == workPath.size) {
                try {
                    Level* pLevel = mTower.GetLevel(workPath.mPathList[workPath.size - 1].mLevel);
                    FloorBase* pFB = pLevel->GetSpaceByID(person->GetWorkID());
                    if (pFB && pFB->GetType() == BaseOffice) {
                        Office* pOffice = reinterpret_cast<Office*>(pFB);
                        pOffice->PeopleInOut(1);
                    }
                } catch (...) {
                    person->SetOccupation(0); // unemployed
                }
            }
        }
    } else {
    }
}

void CitizensAgent::ClockingOut(Person* person)
{
    Path& workPath = person->get_WorkPath(); // for now just doing work
    if (workPath.index > 0) {
        int idx = workPath.index;
        int curLevel = person->get_Location().mLevel;
        Level* pLevel = mTower.GetLevel(curLevel);
        FloorBase* pFB = pLevel->GetSpaceByID(person->GetWorkID());
        if (pFB && pFB->GetType() == BaseOffice) {
            Office* pOffice = reinterpret_cast<Office*>(pFB);
            pOffice->PeopleInOut(-1);
        }
    }
    person->SetActivity(Person::AS_GoingHome);
}

void CitizensAgent::GoingHome(Person* person)
{
    Path& workPath = person->get_WorkPath(); // for now just doing work
    if (workPath.index >= 0) {
        int idx = workPath.index;
        int curLevel = person->get_Location().mLevel;
        if (curLevel == workPath.mPathList[idx].mLevel) {
            // just moving on the same level
        } else {
            switch (person->GetCurrentState()) {
            case Person::CS_Waiting:
                // tally up wait states
                break;
            case Person::CS_Riding:
                // enroute
                break;
            case Person::CS_Disembarking:
                if (workPath.index > 0) {
                    workPath.index--; // TODO: wait for elevator, we are moving ahead before getting
                                      // to the level
                }
                person->SetCurrentState(Person::CS_Walking);
                person->SetCurrent(workPath.mPathList[idx].mLevel);
                curLevel = workPath.mPathList[idx].mLevel;
                idx = workPath.index;
                // fall through
            default:
                RoutePerson(idx, workPath, person);
            }
        }
    } else {
    }
}

void CitizensAgent::LunchBreak(Person* person, int tod)
{
    Path& workPath = person->get_WorkPath(); // for now just doing work
    if (workPath.index >= 0) {
        int idx = 0;
        int curLevel = person->get_Location().mLevel;
        if (curLevel == workPath.mPathList[idx].mLevel) {
            // just moving on the same level
        } else {
            switch (person->GetCurrentState()) {
            case Person::CS_Waiting:
                // tally up wait states
                break;
            case Person::CS_Riding:
                // enroute
                break;
            case Person::CS_Disembarking:
                if (workPath.index > 0) {
                    workPath.index--; // TODO: wait for elevator, we are moving ahead before getting
                                      // to the level
                }
                person->SetCurrentState(Person::CS_Walking);
                person->SetCurrent(workPath.mPathList[idx].mLevel);
                curLevel = workPath.mPathList[idx].mLevel;
                idx = workPath.index;
                // fall through
            default:
                RoutePerson(idx, workPath, person);
            }
        }
    }
}