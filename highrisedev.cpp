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

#include "Camera.h"

#include "AI/citizensAgent.h"
//#include "AI/pathAgent.h"
//#include "AI/floorAgent.h"

#include "routes.h"
#include "background.h"
#include "Tower/tower.h"
#include "scene.h"

#include <CEGUI.h>

#include "Window/GUIManager.h"
#include "sceneEvent.h"

#include "highrisedev.h"

void debugprint()
{
   std::cout << "Program exited correctly. Creating trace...\n";
}

int
main ()
{
   atexit(debugprint);
   Camera * cam = Camera::GetInstance ();

   cam->SetSceneSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (60);
   cam->SetActive();
   cam->InitGL();

   Interface* pInterface = new Interface();
   Scene theScene;
   Tower theTower (1, 10, theScene); // numero uno with 10 sub levels
   theScene.AddTower (&theTower); // pointer for graphics
   CitizensAgent People( theTower ); // known tower, later this will be a tower list for mutiple towers

   sf::String Title( string("Alpha"));

   std::cout << "Basic loading finished....\n";
   try
   {
      // stuffing the floors with test spaces
      theTower.DebugLoad (0,0,0);

      theScene.SetBG (new Background (cam->GetSceneSize().x, cam->GetSceneSize().y));

      SceneEvent SceneEV(&theScene);
      GUIManager Gui (SceneEV);

      EventHandler Events;
      Events.Add (&Gui);
      Events.Add (cam);

      MainEvent mev;
      Events.Add(&SceneEV);
      Events.Add (&mev);

      std::cout << "Starting event loop...\n";
      while (mev.IsRunning())
      {
         // This should be here so we can create custom events later,
         // and also so we can create fake events for debugging.
         sf::Event Event;
         while (cam->GetEvent(Event))
         {
            Events.HandleEvents (Event);
         }
         cam->Clear ();
         cam->SetActive();
         cam->Integrate (60);
         theTower.Update (60);
         cam->DrawModel(&theScene); // the background and tower(s).
         pInterface->Update(60);
         cam->DrawInterface( pInterface );

         Gui.Draw ();

         cam->Display ();
         People.Update( 40 );
      }
      std::cout << mev.IsRunning() << "\n";
   }
   catch ( HighriseException* ex )
   {
      std::cout << "Exception caught in main: " << ex->get_Message();
      std::cout << "Hit a key to close!";
      char t[4];
      std::cin.get(t[0]);
   }
   return 0;
}
