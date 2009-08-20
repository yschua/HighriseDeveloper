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

#ifndef _ROUTES_H
#define _ROUTES_H

class C_RouteBase; // aggregate of elevators and stairs

class C_Routes
{
private:
    std::list<C_RouteBase *> m_Routes;
    
public:
    C_Routes();
    void add_route(C_RouteBase * route);
    void update (float dt);
    void draw ();
};

#endif //_ROUTES_H
