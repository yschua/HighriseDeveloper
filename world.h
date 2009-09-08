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
#ifndef _WORLD_H
#define _WORLD_H

#include "Graphics/modelObject.h"

class FloorBase; // aggregate of floor spaces for offices, condos and hotels
class Tower;
class Background;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
class World
{
   friend class TowerAgent;

private:
   std::vector<Tower*> mTowers;     // Lobby is at mNo_SubLevels not zero
   Routes mRoutes;
   Background* mpBackground;

public:
   // ctor/dtor
   World();
   ~World();

protected:
   inline std::vector<Tower*>& GetTowers()
   {
      return mTowers;
   }

   // methods
public:
   //Tower* NewTower (int x, int y, int z, int z2, int x2);
   void AddTower (Tower* pTower);
   Tower* GetTower (int no); // positive gets you a level above, negative gets you a basement level
   void SetBG (Background* pBG);

   void Update (float dt);
   void Draw ();
};

#endif //_WORLD_H
