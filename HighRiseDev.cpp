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
#include <CEGUI/CEGUI.h>
#include "Window/GUIManager.h"

#include "Graphics/Camera.h"

#include "AI/CitizensAgent.h"

#include "Tower/Routes.h"
#include "Tower/Tower.h"
#include "Scene/Background.h"
#include "Scene/Scene.h"

#include "Root/SceneEvent.h"
#include "Root/GameManager.h" // xml saver

#include "HighRiseDev.h"

void debugprint()
{
    std::cout << "Program exited correctly. Creating trace...\n";
}

int main()
{
    atexit(debugprint);
    // Camera manages the window, opengl, and some drawing. It's a singleton for the sake
    // of simplicity, although it's possible that it should not be (so we can support multiple
    // rendering targets/windows).
    Camera* cam = Camera::GetInstance();

    cam->SetSceneSize(Vector2f(1920, 1920));
    cam->SetMaxFramerate(60);
    cam->SetActive();
    cam->InitGL();

    Interface* pInterface = new Interface();
    Scene theScene;
    Tower theTower(1, 10, theScene); // numero uno with 10 sub levels
    theTower.AdjustFunds(1000000);   // start with 1Mil
    theScene.SetTower(&theTower);    // pointer for graphics
    CitizensAgent People(theTower);  // known tower, later this will be a tower list for mutiple towers

    sf::String Title(string("Alpha"));

    std::cout << "Basic loading finished....\n";
    try {
        theScene.SetBackground(new Background(-80, -1908, cam->GetSceneSize().x, cam->GetSceneSize().y));

        SceneEvent SceneEV(&theScene);
        GUIManager Gui(SceneEV, *pInterface); //, &theTower);
        try {
            GameManager tm(theScene);
            tm.LoadBuildPack("data/xml/DefaultBuildPack.xml"); // use settings for path and pack name
        } catch (...) {
            throw new HighriseException("Failed to load pack\n");
        }

        EventHandler Events;
        Events.Add(&Gui);
        Events.Add(cam);

        MainEvent mev;
        Events.Add(&SceneEV);
        Events.Add(&mev);

        // Load the test tower
        SceneEV.OnOpen("data/xml/Tower.xml");
        // stuffing the floors with test spaces.
        // note this actually loads the xml file
        // at data/xml/Tower.xml
        theTower.DebugLoad(1, 1, 1);
        std::cout << "Starting event loop...\n";
        int cycle = 0;
        // The main event loop. Processed about 30 times per second, although
        // lower framerates shouldn't slow down the game when we get it all
        // working properly.
        while (mev.IsRunning()) {
            // This should be here so we can create custom events later,
            // and also so we can create fake events for debugging.
            sf::Event Event;
            while (cam->GetEvent(Event)) {
                Events.HandleEvents(Event);
            }
            // drawing scope
            cam->Clear();
            cam->SetActive();
            cam->Integrate(80);
            cam->DrawModel(&theScene); // the background and tower(s).
            cam->DrawInterface(pInterface);
            cam->DrawPeople(&People);
            Gui.Draw();
            cam->Display();
            // end drawing scope

            // update scope, thread candidates
            switch (cycle++) {
            case 0:
                theScene.Update(80, pInterface->GetTimeOfDay());
                break;
            case 1:
                pInterface->mStats.SetPopulation(theTower.GetPopulation());
                pInterface->mStats.SetNet((int)theTower.GetAvailableFunds());
                pInterface->Update(20);
                break;
            default:
                static int cc_count = 30; // only once in a while
                if (cc_count < 1) {
                    People.Update(800, pInterface->GetTimeOfDay());
                    cc_count = 20;
                }
                cc_count--;
                cycle = 0;
                break;
            }
            theTower.Update((float)pInterface->GetDayOfYear(), pInterface->GetTimeOfDay());
            // end update scope
        }
        std::cout << mev.IsRunning() << "\n";
        delete pInterface;
    } catch (HighriseException* ex) {
        std::cout << "Exception caught in main: " << ex->get_Message();
        std::cout << "Hit a key to close!";
        char t[4];
        std::cin.get(t[0]);
    }
    return 0;
}
