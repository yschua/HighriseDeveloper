/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <list>

#include "routeBase.h"
#include "elevatorBase.h"
#include "routes.h"

C_Routes::C_Routes()
{
}
void C_Routes::add_route(C_RouteBase * route)
{
   m_Routes.push_back( route );
}

void C_Routes::update (float dt)
{
   for each( C_RouteBase * route in m_Routes )
   {
      route->update( dt );
   }
}

void C_Routes::draw ()
{
   for each( C_RouteBase * route in m_Routes )
   {
      route->draw( );
   }
}

