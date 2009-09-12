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
#include "Types/Rect.h"
#include "Types/Vector2.h"

#include "Camera.h"

#include "person.h"
#include "AI/citizensAgent.h"
//#include "AI/pathAgent.h"
//#include "AI/floorAgent.h"

#include "routes.h"
#include "background.h"
#include "Tower/elevatorBase.h"
#include "Tower/elevator.h"
#include "Tower/tower.h"
#include "world.h"

#include <CEGUI.h>
#include <RendererModules/OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>

#include "Window/GUIManager.h"

#include "highrisedev.h"

int
main ()
{
   Camera * cam = Camera::GetInstance ();

   cam->SetWorldSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (60);

   Elevator* pElevator;
   Background * pBackground;
   Tower theTower (1, 10); // numero uno with 10 sub levels
   CitizensAgent People( theTower ); // known tower, later this will be a tower list for mutiple towers
   Interface* pInterface = new Interface();
   World theWorld;
   theWorld.AddTower (&theTower); // pointer for graphics
   float width = cam->GetWorldSize().x;
   float height = cam->GetWorldSize().y;

   cam->SetActive();
   cam->InitGL();
   sf::String Title( string("Alpha"));

   try
   {
      // stuffing the floors with test spaces
      theTower.DebugLoad (0,0,0);

      pBackground = new Background (width, height);
      theWorld.SetBG (pBackground);
      GUIManager Gui;

      EventHandler Events;
      Events.Add (&Gui);
      Events.Add (cam);
      MainEvent mev;
      Events.Add (&mev);

      while (mev.IsRunning())
      {
         Events.HandleEvents ();
         cam->Clear ();
         cam->SetActive();
         cam->Integrate (60);
         theTower.Update (60);
         cam->DrawModel(&theWorld); // the background and tower(s).
         pInterface->Update(60);
         cam->DrawInterface( pInterface );

         Gui.Draw ();

         cam->Display ();
         People.Update( 40 );
      }
   }
   catch ( HighriseException* ex )
   {
      std::cout << "Exception caught in main: " << ex->get_Message();
   }
   return 0;
}
