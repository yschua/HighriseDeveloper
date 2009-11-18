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
#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H

class Tower;
class Scene;
class TiXmlElement;
class TiXmlNode;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
class GameManager
{

private:
   Scene& mScene;

public:
   GameManager( Scene& scene);
   ~GameManager() {}
   bool LoadBuildPack (const char *fileName);
   bool LoadGame(const char* fileName);
   bool SaveGame(const char* fileName);

   bool LoadTower(TiXmlNode* nTower, Tower* pTower);
   bool SaveTower(TiXmlElement* pnParent, Tower* pTower);

   void Add( TiXmlNode* pnElement, const char* szTag, const char* szText);
};

#endif //_GAMEMANAGER_H
