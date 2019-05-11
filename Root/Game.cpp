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

#include "Game.h"

#include "../Graphics/Camera.h"
#include "../Scene/Background.h"
#include "GameManager.h"

const int Game::m_updateRate = 100; // number of updates per second
const int Game::m_clockRate = 70; // number of updates for one game minute to pass

Game::Game() : m_mainEvt(m_updateRate) {}

void Game::Initialize()
{
    // Camera manages the window, opengl, and some drawing
    m_camera = Camera::GetInstance();
    m_camera->SetSceneSize(Vector2f(1920, 1920));
    m_camera->SetMaxFramerate(0);
    m_camera->SetActive();
    m_camera->InitGL();

    m_tower = std::make_unique<Tower>(1, 10, m_scene);
    m_tower->AdjustFunds(1'000'000);

    m_scene.SetTower(m_tower.get()); // pointer for graphics

    auto background = std::make_unique<Background>(
        -80.f, -1908.f, m_camera->GetSceneSize().x, m_camera->GetSceneSize().y);
    m_scene.SetBackground(std::move(background));

    m_citizensAgent = std::make_unique<CitizensAgent>(*m_tower);

    InitializeEvents();
}

void Game::InitializeEvents()
{
    m_sceneEvt = std::make_unique<SceneEvent>(&m_scene);
    m_gui = std::make_unique<GUIManager>(*m_sceneEvt, m_interface);

    m_events.Add(m_gui.get());
    m_events.Add(m_camera);
    m_events.Add(m_sceneEvt.get());
    m_events.Add(&m_mainEvt);
}

void Game::ProcessInput()
{
    sf::Event evt;
    while (m_camera->GetEvent(evt)) {
        m_events.HandleEvents(evt);
    }
    m_camera->MoveCamera();
}

void Game::Update()
{
    const auto& dt = m_mainEvt.GetDt();

    // UI updates here so it still works when paused
    m_camera->Integrate(dt);

    if (m_mainEvt.IsPaused()) return;

    // Simulation updates here
    m_interface.mStats.SetPopulation(m_tower->GetPopulation());
    m_interface.mStats.SetNet(static_cast<int>(m_tower->GetAvailableFunds()));
    m_interface.UpdateStats();

    bool timeChanged = m_interface.UpdateTime(m_clockRate);
    const int time = m_interface.GetTimeOfDay();

	if (timeChanged) {
		m_citizensAgent->Update(time);
	}

    m_tower->Update(static_cast<float>(m_interface.GetDayOfYear()), time);
}

void Game::Render()
{
    m_camera->Clear();
    m_camera->SetActive();
    m_camera->DrawModel(&m_scene);
    m_camera->DrawInterface(&m_interface);
    m_camera->DrawPeople(m_citizensAgent.get());
    m_gui->Draw();
    m_camera->Display();
}

void Game::GameLoop()
{
    sf::Clock timer;
    sf::Time accumulator;

    while (!m_mainEvt.IsClosed()) {
        auto frameTime = timer.getElapsedTime();
        if (frameTime > sf::milliseconds(250)) {
            frameTime = sf::milliseconds(250);
        }
        accumulator += frameTime;
        const auto& dt = m_mainEvt.GetDt();

        ProcessInput();

        while (accumulator >= dt) {
            Update();
            accumulator -= dt;
        }

        timer.restart();
        // breakpoints after here will increase the frameTime and break shit
        Render();
    }
}

void Game::Run()
{
    Initialize();

    GameManager gameManager(m_scene);
    gameManager.LoadBuildPack("data/xml/DefaultBuildPack.xml");

    // Load test tower
    m_sceneEvt->OnOpen("data/xml/Tower.xml");
    m_tower->DebugLoad(1, 1, 1);

    GameLoop();
}
