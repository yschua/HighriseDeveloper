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

#include <vector>
#include <iostream>
#include "person.h"
#include "citizensAgent.h"
#include "pathAgent.h"
#include "routeVisitor.h"
#include "routeBase.h"
#include "routes.h"
#include "HighriseException.h"

C_CitizensAgent::C_CitizensAgent ( )
{

}

C_CitizensAgent::~C_CitizensAgent ()
{
   std::cout << "Cleaning up C_Citizens";
   try
   {
      std::vector<C_Person *>::iterator i;
      for (i = m_People.begin (); i != m_People.end (); i++)
      {
         C_Person* peep = (*i);
         delete peep;
      }
   }
   catch (...)
   {
      throw new C_HighriseException( "Error in CitezensAgent destructor" );
   }
}

void C_CitizensAgent::update (float dt)
{
   if( (rand() % (int)dt) == 3 )   // TODO: need a better spawn mechanism
   {
      Location loc; // all zeros
      C_Person* peep = new C_Person( loc );
      m_People.push_back( peep );
      std::cout << "A new person has entered your building looking for work";
   }
   std::vector<C_Person *>::iterator i;
   for (i = m_People.begin (); i != m_People.end (); i++)
   {
      C_Person* peep = (*i);
      peep->update( dt );
      int act = peep->get_Activity();
      if( act == C_Person::AS_JobHunting )
      {
         Location dest;
         dest.m_Building = 1;
         dest.m_Level = 1 + (rand() % 3); // TODO:  get a real job finder
         dest.m_State = 1;              // plug a 1 for now meaning active
         dest.m_X = 1;                  // TODO:  find the room number
         C_PathAgent Path( peep );
         std::cout << "A new person has entered your building looking for work on Level# " << dest.m_Level;
         peep->set_Activity( C_Person::AS_GoingToWork );
         peep->set_Occupation( 1 );
         Path.findPath( peep->get_Location(), dest );
      }
      else if( act == C_Person::AS_CondoHunting )
      {
      }
      else if( act == C_Person::AS_ApartmentHunting )
      {
      }
      else if( act == C_Person::AS_GoingToWork )
      {
         Path& path = peep->get_WorkPath(); // for now just doing work
         if( path.index < path.size )
         {
            int idx = path.index;
            //path.index++;
            int curLevel = peep->get_Location().m_Level;
            if( curLevel == path.m_PathList[idx].m_Level )
            {
               // just moving on the same level
            }
            else
            {
               C_Routes* routeList = C_Routes::get_instance();
               if(  routeList->get_Routes().size() > 0 )
               {
                  std::vector<C_RouteBase*>::iterator i;
                  i = routeList->get_Routes().begin ();
                  C_RouteBase* route = (*i);
                  RoutingRequest req;
                  req.OriginLevel = curLevel;
                  req.DestinLevel = path.m_PathList[idx].m_Level;
                  C_RouteVisitor visitor(&req);
                  route->setRoute( &visitor );
               }
               path.index++; // TOFO: wait for elevator, we are moving ahead before getting to the level
            }
         }
         else
         {
         }
      }
      else if( act == C_Person::AS_GoingHome )
      {
         Path& path = peep->get_WorkPath(); // for now just doing work
         if( path.index >= 0 )
         {
            int idx = path.index;
            //path.index++;
            int curLevel = peep->get_Location().m_Level;
            if( curLevel == path.m_PathList[idx].m_Level )
            {
               // just moving on the same level
            }
            else
            {
               C_Routes* routeList = C_Routes::get_instance();
               if(  routeList->get_Routes().size() > 0 )
               {
                  std::vector<C_RouteBase*>::iterator i;
                  i = routeList->get_Routes().begin ();
                  C_RouteBase* route = (*i);
                  RoutingRequest req;
                  req.OriginLevel = curLevel;
                  req.DestinLevel = path.m_PathList[idx].m_Level;
                  C_RouteVisitor visitor(&req);
                  route->setRoute( &visitor );
               }
               path.index--; // TOFO: wait for elevator, we are moving ahead before getting to the level
            }
         }
         else
         {
         }
      }
   }   
}

