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

#include "CitizensAgent.h"

#include "FloorAgent.h"
#include "PathAgent.h"
#include "../People/Citizens.h"
#include "../People/Person.h"
#include "../Tower/Tower.h"

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
        JobHunting(peep, tod);
    }

    for (Person* person : citizens->get_Persons()) {
        person->Update(tod);
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
        //if (peep && peep->GetCurrentState() == Person::AS_JobHunting) {
        //    peep->Draw(320, 36); // standing outside
        //}
    }
}

void CitizensAgent::JobHunting(Person* person, int tod)
{
    //if (person->GetCurrentState() == Person::CS_Idle) {
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
            if ((rand() % 6) ==
                2) // one out of 6 will make good money to afford more than an apartment
                person->SetOccupation(2);
            else
                person->SetOccupation(1);
            person->SetWorkID(pFB);

            mTower.EnterTower(person);
        }
    //}
}
