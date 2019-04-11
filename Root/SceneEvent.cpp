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

#include <iostream>

// Then user-defined types
#include "../Graphics/Camera.h"
#include "../Scene/Scene.h"
#include "../Window/Event.h"
#include "GameManager.h" // xml saver
#include "SceneEvent.h"

SceneEvent::SceneEvent(Scene* pScene)
{
    mpScene = pScene;
}

SceneEvent::~SceneEvent() {}

bool SceneEvent::OnToolHit(int tool)
{
    return mpScene->SetTool(tool);
}

bool SceneEvent::OnMouseDown(sf::Mouse::Button Button, Vector2i pointa, Vector2i pointb)
{
    Camera* pCam = Camera::GetInstance();
    int hit = pCam->RenderFramework(mpScene, pointa, 0);
    if (hit) {
        mpScene->Hit(hit, pointa);
    }
    return false; // leave the message in for the pointer
}

bool SceneEvent::OnMouseMove(Vector2i pointa, Vector2i pointb)
{
    Vector2f vec((float)pointa.x, (float)pointa.y);
    mpScene->MoveGhostRoom(vec);
    return true;
}

void SceneEvent::LoadWindows()
{
    mpScene->LoadWindows();
}

bool SceneEvent::OnOpen(const char* pPath)
{
    GameManager tm(*mpScene);
    return tm.LoadGame(pPath);
}

bool SceneEvent::OnSave(const char* pPath)
{
    GameManager tm(*mpScene);
    return tm.SaveGame(pPath);
}
