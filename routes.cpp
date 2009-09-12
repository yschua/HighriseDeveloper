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

#include <vector>

#include "Tower/routeBase.h"
#include "Tower/elevatorBase.h"
#include "routes.h"

Routes::Routes()
{
}

Routes::~Routes()
{
   std::vector<RouteBase*>::iterator i;
   for (i = mRoutes.begin (); i != mRoutes.end (); i++)
   {
      RouteBase*  pRoute = (*i);
   // TODO: this needs to be done but there is a bug here
   //   delete pRoute;
   }
   //mRoutes.clear();
}

void Routes::AddRoute(RouteBase* route)
{
   mRoutes.push_back( route );
}

void Routes::Update (float dt)
{
   std::vector<RouteBase*>::iterator i;
   for (i = mRoutes.begin (); i != mRoutes.end (); i++)
   {
      (*i)->Update( dt );
   }
}

void Routes::Draw ()
{
   std::vector<RouteBase*>::iterator i;
   for (i = mRoutes.begin (); i != mRoutes.end (); i++)
   {
      (*i)->Draw( );
   }
}
