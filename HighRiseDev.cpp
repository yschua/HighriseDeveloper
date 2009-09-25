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
#include <CEGUI.h>

#include "Graphics/Camera.h"

#include "AI/CitizensAgent.h"
//#include "AI/PathAgent.h"
//#include "AI/FloorAgent.h"

#include "Tower/Routes.h"
#include "Tower/Tower.h"
#include "Scene/Background.h"
#include "Scene/Scene.h"


#include "Window/GUIManager.h"
#include "Root/SceneEvent.h"

#include "HighRiseDev.h"

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
      theScene.SetBG (new Background (cam->GetSceneSize().x, cam->GetSceneSize().y));

      SceneEvent SceneEV(&theScene);
      GUIManager Gui (SceneEV); //, &theTower);

      EventHandler Events;
      Events.Add (&Gui);
      Events.Add (cam);
      
      MainEvent mev;
      Events.Add(&SceneEV);
      Events.Add (&mev);

      // Load the test tower
      SceneEV.OnOpen("data/xml/Tower.xml");
      // stuffing the floors with test spaces
      theTower.DebugLoad (0,0,0);   // just updating elevators
      //

      std::cout << "Starting event loop...\n";
      int cycle = 0;
      while (mev.IsRunning())
      {
         // This should be here so we can create custom events later,
         // and also so we can create fake events for debugging.
         sf::Event Event;
         while (cam->GetEvent(Event))
         {
            Events.HandleEvents (Event);
         }
         // drawing scope
         cam->Clear ();
         cam->SetActive();
         cam->Integrate (60);
         cam->DrawModel(&theScene); // the background and tower(s).
         cam->DrawInterface( pInterface );
         cam->DrawPeople(&People);
         Gui.Draw ();
         cam->Display ();
         // end drawing scope

         // update scope, thread candidates
         switch( cycle++ )
         {
         case 0:
            theScene.Update (0, pInterface->GetTimeOfDay());
            break;
         case 1:
            pInterface->mStats.SetPopulation( theTower.GetPopulation() );
            pInterface->Update(10);
            break;
         default:
            People.Update( 40 );
            cycle = 0;
            break;
         }
         theTower.Update (60, pInterface->GetTimeOfDay());
         // end update scope
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
