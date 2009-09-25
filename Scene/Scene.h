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
#ifndef _SCENE_H
#define _SCENE_H

#include <map>
#include "../Types/Vector2.h"
#include "../Tower/Routes.h"
#include "../Graphics/ModelObject.h"

class FloorBase; // aggregate of floor spaces for offices, condos and hotels
class Tower;
class Background;
class BuildStategyBase;
class GameManager;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
class Scene
{
   friend class TowerAgent;
   friend class GameManager;
public:
   typedef std::vector<Tower*>::iterator TypeTowerIterator;
   typedef std::vector<Tower*> TypeTowerVector;

private:
   std::vector<Tower*> mTowers;     // Lobby is at mNo_SubLevels not zero

   typedef std::map<int,FloorBase*>::iterator TypeFloorSpaceIterator;
   typedef std::pair<int,FloorBase*> TypeFloorSpaceMap;
   std::map<int,FloorBase*> mFloorSpaces;

   //Routes mRoutes;
   Background* mpBackground;
   BuildStategyBase* mpBuildStrategy;  // Place floor objects

public:
   // ctor/dtor
   Scene();
   ~Scene();

protected:
   inline std::vector<Tower*>& GetTowers()
   {
      return mTowers;
   }

   // methods
public:
   //Tower* NewTower (int x, int y, int z, int z2, int x2);
   void AddTower (Tower* pTower);
   //Tower* GetTower (int no); // positive gets you a level above, negative gets you a basement level
   void SetBG (Background* pBG);

   bool SelectTool( int ToolID );
   void RegisterFloorSpace (int id, FloorBase* pFS);
   void UnregisterFloorSpace (int id, FloorBase* pFS);
   FloorBase* FindFloorSpace (int id);

   void Update (float dt, int timeOfDay);
   void Draw ();
   void RenderFramework (int level); // hit test run
   void Hit (int hit, Vector2i Scene);  // mouse x and y, send it through geometry to see what we hit

};

#endif //_SCENE_H
