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
#include "person.h"
#include "pathAgent.h"
#include "routeVisitor.h"
#include "routeBase.h"
#include "routes.h"
#include "tower.h"
#include "citizens.h"
#include "level.h"
#include "HighriseException.h"

#include "citizensAgent.h"

C_CitizensAgent::C_CitizensAgent (C_Tower& tower) // use a tower agent for multiple towers
:  m_Tower (tower)
{

}

C_CitizensAgent::~C_CitizensAgent ()
{
}

void C_CitizensAgent::update (float dt)
{
   C_Citizens* citizens = C_Citizens::get_Instance(); // the citizens object that holds the people collection
   if( (rand() % 200) == 3 )   // TODO: need a better spawn mechanism, raised to 100
   {

      //Location loc; // all zeros
      C_Person* peep = citizens->NewPerson();
//      C_Person* peep = new C_Person( loc );
//      m_People.push_back( peep );
      std::cout << "A new person has entered your city" << std::endl;
   }
   std::list<C_Person *>::iterator i;
   std::list<C_Person *>& persons = citizens->get_Persons(); // get the persons collection.
   // TODO: Need to create a better interface that provides a clear persons iteration.
   for (i = persons.begin (); i != persons.end (); i++)
   {
      C_Person* peep = (*i);
      peep->update( dt );
      Path& workPath = peep->get_WorkPath(); // for now just doing work
      //  TODO: case statement from hell, on the refactor list
      switch( peep->get_Activity() )
      {
      case C_Person::AS_Sleeping:
         // check alarm;
         break;

      case C_Person::AS_JobHunting:
         if( peep->get_CurrentState() == C_Person::CS_Idle )
         {
            Location dest;
            dest.m_Building = 1;
            dest.m_Level = 1 + (rand() % 3); // TODO:  get a real job finder
            dest.m_Route = 0;              // plugged into first elevater until pathfinder does the job.
            dest.m_X = 1;                  // TODO:  find the room number
            std::cout << "A new person has entered your building looking for work on Level# " << dest.m_Level << std::endl;
            peep->set_Activity( C_Person::AS_GoingToWork );
            peep->set_Occupation( 1 );
            C_PathAgent Path( peep );
            Path.findPath( peep->get_Location(), dest, m_Tower );
         }
         break;

      case C_Person::AS_CondoHunting:
         // Phase 2 with 2 star building
         break;

      case C_Person::AS_ApartmentHunting:
         // Set up cheap housing (not in the original tower game.
         break;

      case C_Person::AS_GoingToWork:
         if( workPath.index < workPath.size )
         {
            int idx = workPath.index;
            int curLevel = peep->get_Location().m_Level;
            if( curLevel == workPath.m_PathList[idx].m_Level ) // or tower is not = curtower (on a bus, train, car or skycab ).
            {
               // just moving on the same level
            }
            else
            {
               switch( peep->get_CurrentState() )
               {
               case C_Person::CS_Waiting:
                  // tally up wait states
                  break;
               case C_Person::CS_Riding:
                  // enroute
                  break;
               case C_Person::CS_Disembarking:
                  workPath.index++;
                  peep->set_CurrentState( C_Person::CS_Walking );
                  // fall through
               default:
                  //C_Routes* routeList = C_Routes::get_instance();
                  C_Routes& routeList = m_Tower.get_Routes();
                  if(  routeList.get_Routes().size() > 0 )
                  {
                     std::vector<C_RouteBase*>::iterator i;
                     i = routeList.get_Routes().begin ();
                     C_RouteBase* route = (*i);
                     RoutingRequest req;     // routing code needs to queue this person
                     req.OriginLevel = curLevel;
                     req.DestinLevel = workPath.m_PathList[idx].m_Level;
                     C_RouteVisitor visitor(&req, 1);
                     route->setRoute( &visitor );
                  }
               }
               workPath.index++; // TODO: wait for elevator, we are moving ahead before getting to the level
            }
         }
         else
         {
         }
         break;

      case C_Person::AS_GoingHome:
         if( workPath.index >= 0 )
         {
            int idx = workPath.index;
            int curLevel = peep->get_Location().m_Level;
            if( curLevel == workPath.m_PathList[idx].m_Level )
            {
               // just moving on the same level
            }
            else
            {
               //C_Routes* routeList = C_Routes::get_instance();
               C_Routes& routeList = m_Tower.get_Routes();
               if(  routeList.get_Routes().size() > 0 )
               {
                  std::vector<C_RouteBase*>::iterator i;
                  i = routeList.get_Routes().begin ();
                  i++;  // go home on the 2nd elevator
                  C_RouteBase* route = (*i);
                  RoutingRequest req;
                  req.OriginLevel = curLevel;
                  req.DestinLevel = workPath.m_PathList[idx].m_Level;
                  C_RouteVisitor visitor(&req, 1);
                  route->setRoute( &visitor );
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

