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

#include "Scene.h"

#include "../Graphics/Camera.h"
#include "../Tower/BuildFactory.h"
#include "../Tower/BuildStrategies.h"
#include "../Tower/Level.h"
#include "../Tower/Tower.h"
#include "../Window/Event.h"
#include "../Window/RoomWindow.h"
#include "Background.h"

#include <iostream>

Scene::Scene() : mpBackground(nullptr), mpBuildStrategy(nullptr), m_tool(Tool::Select) {}

Scene::~Scene() {}

void Scene::SetTower(Tower* pTower)
{
    mpTower = pTower; // only saved here for drawing
}

bool Scene::SetTool(int tool)
{
    delete mpBuildStrategy;
    mpBuildStrategy = nullptr;

    if (tool > HR_SelectBuildOption && tool < HR_PlaceNone) {
        // building new room
        auto pBuildFactory = TowerObjects::BuildFactory::GetInstance();
        mpBuildStrategy = pBuildFactory->CreateStrategy(tool, mpTower);
        m_tool = Tool::Build;
    } else {
        auto& ghostRoom = mpTower->GetGhostRoom();
        ghostRoom.SetShownType(BaseEmpty);
        ghostRoom.SetWidth(1);
        m_tool = (tool == HR_Remove) ? Tool::Remove : Tool::Select;
    }

    return true;
}

void Scene::SetBackground(std::unique_ptr<Background> pBG)
{
    mpBackground = std::move(pBG);
}

void Scene::Update(float dt, int timeOfDay)
{
    mpBackground->Update(timeOfDay);
}

void Scene::Draw()
{
    mpBackground->Draw();
    mpTower->Draw();
}

void Scene::RenderFramework(int level)
{
    if (level == 0) {
        bool bLevelsOnly = (mpBuildStrategy != nullptr);
        mpTower->DrawFramework(bLevelsOnly);
    } else {
        // only draw empty space slection zones
        mpTower->GetLevel(level)->DrawEmptyFramework();
    }
}

void Scene::MoveGhostRoom(Vector2f& point)
{
    Camera* pCam = Camera::GetInstance();
    Vector3f vec = pCam->GetOGLPos(point);
    mpTower->GetGhostRoom().Move(vec); // asp
}

void Scene::LoadWindows()
{
    m_roomWnd = std::make_unique<RoomWindow>();
}

// taking a mouse hit, send it through geometry to see what we hit
void Scene::Hit(int hit)
{
    auto level = mpTower->FindLevel(mpTower->GetGhostRoom().GetLevel());

    if (level == nullptr) return;

    if (m_tool == Tool::Build && mpBuildStrategy != nullptr) {
        int x = static_cast<int>(mpTower->GetGhostRoom().GetX() / 9);
        mpBuildStrategy->BuildHere(mpTower, x, level->GetLevel());
    } else if (m_tool == Tool::Remove) {
        auto room = level->GetSpaceByID(hit);
        if (room != nullptr) {
            level->RemoveFloorSpace(room);
        }
    } else if (m_tool == Tool::Select) {
        auto room = level->GetSpaceByID(hit);
        if (room != nullptr) {
            m_roomWnd->SetRoom(room);
            m_roomWnd->Show();
        }
    }
}
