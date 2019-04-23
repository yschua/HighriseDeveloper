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

#ifndef _GAME_H
#define _GAME_H

#include "../AI/CitizensAgent.h"
#include "../Scene/Scene.h"
#include "../Tower/Tower.h"
#include "../Window/Interface.h"
#include "../Window/Event.h"
#include "../Window/MainEvent.h"
#include "../Window/GUIManager.h"
#include "SceneEvent.h"

#include <memory>

class Camera;

class Game
{
public:
    Game();
    void Run();

private:
    void Initialize();
    void InitializeEvents();
    void ProcessInput();
    void Update();
    void Render();
    void GameLoop();

    static const int m_updateRate;
    static const int m_clockRate;

    Interface m_interface;
    Scene m_scene;
    EventHandler m_events;
    MainEvent m_mainEvt;
    std::unique_ptr<Tower> m_tower;
    std::unique_ptr<CitizensAgent> m_citizensAgent;
    std::unique_ptr<GUIManager> m_gui;
    std::unique_ptr<SceneEvent> m_sceneEvt;
    Camera* m_camera;
};

#endif // _GAME_H