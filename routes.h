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

class RouteBase; // aggregate of elevators and stairs

class Routes
{
private:
   std::vector<RouteBase *> mRoutes;
//   static Routes* minstance; no longer static as each tower has it's own routes

public:
   Routes(); // not part of Tower.
   ~Routes();
//   static Routes* GetInstance ();
   std::vector<RouteBase *>& Get_Routes()
   {
      return mRoutes;
   }
   void AddRoute(RouteBase * route);
   void Update (float dt);
   void Draw ();
};

#endif //_ROUTES_H
