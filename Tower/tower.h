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

#include "../Graphics/modelObject.h"

class FloorBase; // aggregate of floor spaces for offices, condos and hotels
class Level;
class Elevator;
class TowerAgent;
class Routes;
class Person;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
class Tower : public Gfx::ModelObject
{
   friend class TowerAgent;

private:
   int mTowerNo;
   int mNo_SubLevels;
   int mPopulation;  // People in the tower currently

   std::vector<Level *> mLevels;     // Lobby is at mNo_SubLevels not zero
   Routes mRoutes;

public:
   // ctor/dtor
   Tower( int towerNo, int NoSubLevels );
   ~Tower();

   // properties
   inline Routes& GetRoutes()
   {
      return mRoutes;  // For routing citizens
   }
   inline int GetPopulation()
   {
      return mPopulation;
   }

protected:
   inline std::vector<Level *>& Get_Levels()
   {
      return mLevels;
   }

   // methods
public:
   Level* NewLevel (int x, int y, int x2);
   Level* GetLevel (int level); // positive gets you a level above, negative gets you a basement level

   void Update (float dt);
   void Draw ();

   // AI interface
   void EnterTower (Person* pPerson);
   void LeaveTower (Person* pPerson);
};

#endif //_TOWER_H
