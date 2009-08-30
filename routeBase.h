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

#ifndef _ROUTEBASE_H
#define _ROUTEBASE_H
class C_RouteVisitor;

class C_RouteBase // Abstract, does not even have a CPP file at this point.
{

public:
   C_RouteBase() {};
   virtual void SetRoute( C_RouteVisitor* visitor ) = 0;
   virtual void Update (float dt) = 0;
   virtual void Draw () = 0;
};

#endif //_ROUTEBASE_H
