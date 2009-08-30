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
// If you have trouble compiling with pragma one please lest us know at highrisedev/sourceforge.org
#pragma once
#ifndef _ROUTEVISITOR
#define _ROUTEVISITOR

struct RoutingRequest
{
   int OriginLevel;
   int DestinLevel;
};

// lightweight vistor pattern that minimizes interface with elevators and other means of floor level transit.
class C_RouteVisitor
{
protected:
   RoutingRequest* m_routingRequest; // for now a single request, later we may use a collection.
public:
   C_RouteVisitor (RoutingRequest* rq, int count);
   ~C_RouteVisitor (void);

   virtual RoutingRequest* getRoute( )
   {
      return m_routingRequest;
   }
};

#endif //_ROUTEVISITOR
