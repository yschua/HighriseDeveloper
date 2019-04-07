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

#ifndef _SCENE_H
#define _SCENE_H

#include "../Types/Vector2.h"

class Tower;
class Background;
class BuildStrategyBase;

class Scene
{
public:
    Scene();
    ~Scene();
    void SetTower(Tower* pTower);
    void SetBackground(Background* pBG);
    bool SetTool(int tool);
    void Update(float dt, int timeOfDay);
    void Draw();
    void RenderFramework(int level); // hit test run
    void Hit(int hit, Vector2i& point);
    void MoveGhostRoom(Vector2f& point);
    Tower* GetTower() const { return mpTower; }

private:
    Tower* mpTower;
    Background* mpBackground;
    BuildStrategyBase* mpBuildStrategy;  // Place floor objects
};

#endif //_SCENE_H
