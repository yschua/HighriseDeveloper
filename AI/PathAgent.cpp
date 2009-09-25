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
// The Activities Agent will hand people to this agent when they enter a travel state.
// A location and destination will be set for the person(s) preparing to embark. The path agent will
// then find the best path to that destination. Folks in the tower(s) will be transitioned from
// point to point. The nearest elevalor is found and enqueued. Should the wait time exceed A limt
// the PA will look for the another elevator close by that stops on the level desired. It found then
// the person procedes there. If time exceeds A&B limit then a moderate distance is searched. Same
// for limit C but forther. If still no satifaction, enter drastic mode( leave, move etc).

#include <vector>
#include "../Person.h"
#include "../Routes.h"
#include "../Tower/RouteBase.h"
#include "../Tower/Tower.h"
#include "../AI/CitizensAgent.h"

#include "PathAgent.h"

PathAgent::PathAgent (Person* person )
      :  mPerson( person )
{

}

// functor level PathAgent
// Instiate, get the person to his destination and done
PathAgent::PathAgent (Person* person, int level)   // deposit person on this level;
      :  mPerson( person )
{
   person->get_Location();
}

PathAgent::~PathAgent ()
{

}

bool PathAgent::findPath (Location& origin, Location& dest, Tower& tower )
{
   Path& path = mPerson->get_WorkPath(); // for now just doing work
   path.clear();
   // normally we would use the commented code but for now I've pluged direct to a single elevator
   //Routes* routeList = Routes::GetInstance();
   Routes& routeList = tower.GetRoutes();
   CitizensAgent People( tower );
   std::vector<RouteBase*>::iterator i;
   //for (i = routeList.get_Routes().begin (); i != routeList.get_Routes().end (); i++)
   //{
   //   RouteBase* route = (*i);
   //}
   path.mPathList[0].mBuilding = dest.mBuilding;
   path.mPathList[0].mLevel = 0;
   path.mPathList[0].mRoute = 0; // first option
   path.mPathList[0].mX = 0;
   path.mPathList[1].mBuilding = dest.mBuilding;
   path.mPathList[1].mLevel = dest.mLevel;
   path.mPathList[1].mRoute = 0;
   path.mPathList[1].mX = dest.mX;
   path.index = 0;
   path.size = 2;
   return true;
}
