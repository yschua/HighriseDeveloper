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

#include <list>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "../Person.h"
#include "../RouteVisitor.h"
#include "../Routes.h"
#include "../PersonQueue.h"
#include "../Tower/RouteBase.h"
#include "../Tower/Tower.h"
#include "../Tower/Level.h"
#include "../HighRiseException.h"
#include "../Citizens.h"

#include "PathAgent.h"
#include "CitizensAgent.h"

CitizensAgent::CitizensAgent (Tower& tower) // use a tower agent for multiple towers
      :  mTower (tower)
{

}

CitizensAgent::~CitizensAgent ()
{
}

void CitizensAgent::Update (float dt)
{
   // Shouldn't Citizens be a member within each Tower? Supposedly you would want this seperate.
   Citizens* citizens = Citizens::get_Instance(); // the citizens object that holds the people collection
   if ( (rand() % 200) == 3 )  // TODO: need a better spawn mechanism, raised to 100
   {

      //Location loc; // all zeros
      Person* peep = citizens->NewPerson();
//      Person* peep = new Person( loc );
//      mPeople.push_back( peep );
      // Shouldn't this be Update(dt)?
      citizens->Update( 1 );
//log      std::cout << "Your city added 1 person" << " Population in city: " << citizens->GetPopulation() << std::endl;
   }
   // std::list<Person*> Should be a member typedef!
   std::list<Person *>::iterator i;
   std::list<Person *>& persons = citizens->get_Persons(); // get the persons collection.

   // TODO: Need to create a better interface that provides a clear persons iteration.
   for (i = persons.begin (); i != persons.end (); i++)
   {
      Person* peep = (*i);
      peep->Update( dt );
      Path& workPath = peep->get_WorkPath(); // for now just doing work
      //  TODO: case statement from hell, on the refactor list
      switch ( peep->get_Activity() )
      {
         case Person::AS_Sleeping:
            // check alarm;
            break;

         case Person::AS_JobHunting:
            if (peep->get_CurrentState() == Person::CS_Idle)
            {
               Location dest;
               dest.mBuilding = 1;
               dest.mLevel = 1 + (rand() % 3); // TODO:  get a real job finder
               dest.mRoute = 0;              // plugged into first elevater until pathfinder does the job.
               dest.mX = 1;                  // TODO:  find the room number
//Log               std::cout << "A new person has entered your building looking for work on Level# " << dest.mLevel << std::endl;
               peep->set_Activity( Person::AS_GoingToWork);
               peep->set_Occupation (1);
               PathAgent Path (peep);
               Path.findPath (peep->get_Location(), dest, mTower);

               mTower.EnterTower (peep);
            }
            break;

         case Person::AS_CondoHunting:
            // Phase 2 with 2 star building
            break;

         case Person::AS_ApartmentHunting:
            // Set up cheap housing (not in the original tower game.
            break;

         case Person::AS_GoingToWork:
            if ( workPath.index < workPath.size )
            {
               int idx = workPath.index;
               int curLevel = peep->get_Location().mLevel;
               if ( curLevel == workPath.mPathList[idx].mLevel ) // or tower is not = curtower (on a bus, train, car or skycab ).
               {
                  // just moving on the same level
               }
               else
               {
                  switch ( peep->get_CurrentState() )
                  {
                  case Person::CS_Waiting:
                     // tally up wait states
                     break;
                  case Person::CS_Riding:
                     // enroute
                     break;
                  case Person::CS_Disembarking:
                     workPath.index++;
                     peep->set_CurrentState( Person::CS_Walking );
                     // fall through
                  default:
                     //Routes* routeList = Routes::GetInstance();
                     Routes& routeList = mTower.GetRoutes();
                     if (  routeList.Get_Routes().size() > 0 )
                     {
                        std::vector<RouteBase*>::iterator i;
                        i = routeList.Get_Routes().begin ();
                        RouteBase* route = (*i);
                        RoutingRequest req;     // routing code needs to queue this person
                        req.OriginLevel = curLevel;
                        req.DestinLevel = workPath.mPathList[idx].mLevel;
                        RouteVisitor visitor(&req, 1);
                        route->SetCallButton( &visitor );
                        if( visitor.IsBoarding() )
                        {
                           peep->set_CurrentState( Person::CS_Riding );
                           Level* pLevel = mTower.GetLevel(curLevel);
                           PersonQueue* pQ = pLevel->FindQueue(route);
                           if( pQ )
                           {
                              pQ->AddPerson(peep);
                           }
                        }
                        else
                        {
                           peep->set_CurrentState( Person::CS_Waiting );
                        }
                     }
                  }
                  workPath.index++; // TODO: wait for elevator, we are moving ahead before getting to the level
               }
            }
            else
            {
            }
            break;

         case Person::AS_GoingHome:
            if ( workPath.index >= 0 )
            {
               int idx = workPath.index;
               int curLevel = peep->get_Location().mLevel;
               if ( curLevel == workPath.mPathList[idx].mLevel )
               {
                  // just moving on the same level
               }
               else
               {
                  switch ( peep->get_CurrentState() )
                  {
                  case Person::CS_Waiting:
                     // tally up wait states
                     break;
                  case Person::CS_Riding:
                     // enroute
                     break;
                  case Person::CS_Disembarking:
                     workPath.index++;
                     peep->set_CurrentState( Person::CS_Walking );
                     // fall through
                  default:
                     //Routes* routeList = Routes::GetInstance();
                     Routes& routeList = mTower.GetRoutes();
                     if ( routeList.Get_Routes().size() > 0 )
                     {
                        std::vector<RouteBase*>::iterator i;
                        i = routeList.Get_Routes().begin ();
                        i++;  // go home on the 2nd elevator
                        RouteBase* route = (*i);
                        RoutingRequest req;
                        req.OriginLevel = curLevel;
                        req.DestinLevel = workPath.mPathList[idx].mLevel;
                        RouteVisitor visitor(&req, 1);
                        route->SetCallButton( &visitor );
                        if( visitor.IsBoarding() )
                        {
                           peep->set_CurrentState( Person::CS_Riding );
                        }
                        else
                        {
                           peep->set_CurrentState( Person::CS_Waiting );
                        }
                     }
                  }
                  workPath.index--; // TODO: wait for elevator, we are moving ahead before getting to the level
               }
            }
            else
            {
            }
            break;
         default:
            // do something
            break;   // microsoft requires this break
      }
   }
}

void CitizensAgent::Draw()
{
   Citizens* citizens = Citizens::get_Instance(); // the citizens object that holds the people collection
   std::list<Person *>::iterator i;
   std::list<Person *>& persons = citizens->get_Persons(); // get the persons collection.

   // TODO: Need to create a better interface that provides a clear persons iteration.
   for (i = persons.begin (); i != persons.end (); i++)
   {
      Person* peep = (*i);
      if( peep && peep->get_CurrentState() == Person::CS_Waiting )
      {
         peep->Draw();
      }
   }
}
