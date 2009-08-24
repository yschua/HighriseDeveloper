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

   // root of the levels and sublevels, the building/ tower.
   // create an instance of this. The lobby is created empty.
   // call newLevel or newSubLevel to add floors or basement levels
#ifndef _TOWER_H
#define _TOWER_H

class C_FloorBase; // aggregate of floor spaces for offices, condos and hotels
class C_level;
class C_TowerAgent;

class C_Tower
{
   friend C_TowerAgent;
private:
   int m_TowerNo;
   std::list<C_level *> m_Levels;     // Lobby is at 0
   std::list<C_level *> m_SubLevels;  // basement level (-1 = 1, -2 = 2 ) 
                                          //SubLevel 0 = power and utilies not accessible to people
public:
   // ctor/dtor
   C_Tower( int towerNo );
   ~C_Tower();
   // properties

   // implementation
protected:
   std::list<C_level *>& get_Levels()
   {
      return m_Levels;
   }
   std::list<C_level *>& get_SubLevels()
   {
      return m_SubLevels;
   }
public:
   C_level* newLevel( );  
   C_level* newSubLevel( );
   C_level* getLevel( int level ); // positive gets you a level above, negative gets you a basement level


   void update (float dt);
   void draw ();
};

#endif //_TOWER_H
