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

#include "../Graphics/ModelObject.h"
#include "GhostRoom.h" // local for speed
#include "../Routes/Routes.h"
#include "../AI/PathFinding.h"
#include <vector>

class Level;
class Routes;
class Person;
class Scene;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
class Tower : public Gfx::ModelObject
{
public:
    Tower(int towerNo, int NoSubLevels, Scene& rScene);
    virtual ~Tower();

    // properties
    inline Routes& GetRoutes() { return mRoutes; } // For routing citizens
    inline int GetPopulation() { return mPopulation; }
    inline double GetAvailableFunds() { return mAvailableFunds; }
    void AdjustFunds(double amt) { mAvailableFunds += amt; } // pass neg value to subtract
    inline Scene& GetScene() { return mScene; }
    inline GhostRoom& GetGhostRoom() { return mGhostRoom; }

    Level* NewLevel(int x, int y, int x2);
    Level* GetLevel(int level); // positive gets you a level above, negative gets you a basement level

    void Update(float dt, int timeOfDay);
    void Draw();
    void DrawFramework(bool bLevelsOnly);

    // AI interface
    void EnterTower(Person* pPerson);
    Level* FindLevel(int level);
    std::unique_ptr<Path> FindPath(int startLevel, int goalLevel);

    // Debug Methods
    void DebugLoad(int x, int y, int x2); // this simply pumps floor objects and elevators into the tower.

    inline std::vector<Level*>& GetLevels() { return mLevels; }
    inline Routes::RoutesVector& GetRouteList() { return mRoutes.GetRoutes(); }

private:
    int mNo_SubLevels;
    int mPopulation; // People in the tower currently
    int mFloorWorkingOn;
    double mAvailableFunds;

    std::vector<Level*> mLevels; // Lobby is at mNo_SubLevels not zero
    Routes mRoutes;
    Scene& mScene; // this is where all the towers are modeled in OpenGL.
    GhostRoom mGhostRoom;
    PathFinding m_pathFinding;
};

#endif //_TOWER_H
