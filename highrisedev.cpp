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

#include "Types/Rect.h"
#include "Types/Vector2.h"

#include "Camera.h"
#include "Window/Window.h"
#include "Window/Button.h"
#include "Window/TextBox.h"

#include "person.h"
#include "AI/citizensAgent.h"
//#include "AI/pathAgent.h"
//#include "AI/floorAgent.h"

#include "routes.h"
#include "background.h"
#include "Tower/elevatorBase.h"
#include "Tower/elevator.h"
#include "Tower/Tower.h"
#include "world.h"

#include <CEGUI.h>
#include <OpenGLGUIRenderer/openglrenderer.h>
#include <CEGUISystem.h>
#include <CEGUIDefaultResourceProvider.h>

#include "highrisedev.h"

int
main ()
{
   Camera * cam = Camera::GetInstance ();
   cam->Create ("test");

   cam->SetWorldSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (60);
   sf::Event event;
   Elevator* pElevator;
   Background * pBackground;
   Tower theTower (1, 10); // numero uno with 10 sub levels
   CitizensAgent People( theTower ); // known tower, later this will be a tower list for mutiple towers
   Interface* interface = new Interface();
   World theWorld;
   theWorld.AddTower (&theTower); // pointer for graphics
   float width = cam->GetWorldRect().Right - cam->GetWorldRect().Left;
   float height = cam->GetWorldRect().Bottom - cam->GetWorldRect().Top;

   cam->InitGL();

   try
   {
      // stuffing the floors with test spaces
      theTower.DebugLoad (0,0,0);

      interface = new Interface ();

      pElevator = new Elevator( Elevator::LS_Standard, 472, -1, 6, &theTower );
      theTower.GetRoutes().AddRoute( pElevator );
      pElevator = new Elevator( Elevator::LS_Standard, 472 + 36 + 9, 0, 5, &theTower );
      theTower.GetRoutes().AddRoute( pElevator );
      pBackground = new Background (width, height);
      theWorld.SetBG (pBackground);
      CEGUI::OpenGLRenderer* pCERenderer = new CEGUI::OpenGLRenderer( 1000 );

      CEGUI::System* pCESystem = new CEGUI::System(pCERenderer);

      // initialise the required dirs for the DefaultResourceProvider
      CEGUI::DefaultResourceProvider* rp = static_cast<CEGUI::DefaultResourceProvider*>
          (CEGUI::System::getSingleton().getResourceProvider());

      rp->setResourceGroupDirectory("schemes", "datafiles/schemes/");
      rp->setResourceGroupDirectory("imagesets", "datafiles/imagesets/");
      rp->setResourceGroupDirectory("fonts", "datafiles/fonts/");
      rp->setResourceGroupDirectory("layouts", "datafiles/layouts/");
      rp->setResourceGroupDirectory("looknfeels", "datafiles/looknfeel/");
      rp->setResourceGroupDirectory("lua_scripts", "datafiles/lua_scripts/");

      // set the default resource groups to be used
      CEGUI::Imageset::setDefaultResourceGroup("imagesets");
      CEGUI::Font::setDefaultResourceGroup("fonts");
      CEGUI::Scheme::setDefaultResourceGroup("schemes");
      CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");
      CEGUI::WindowManager::setDefaultResourceGroup("layouts");
      CEGUI::ScriptModule::setDefaultResourceGroup("lua_scripts");

      // load in the scheme file, which auto-loads the TaharezLook imageset
      CEGUI::SchemeManager::getSingleton().loadScheme( "TaharezLook.scheme" );

      // load in a font.  The first font loaded automatically becomes the default font.
      if(! CEGUI::FontManager::getSingleton().isFontPresent( "Commonwealth-10" ) )
         CEGUI::FontManager::getSingleton().createFont( "Commonwealth-10.font" );
      using namespace CEGUI;
      WindowManager& CEWM = WindowManager::getSingleton();
      Window* myRoot = CEWM.createWindow( "DefaultWindow", "root" );
      System::getSingleton().setGUISheet( myRoot );
      FrameWindow* fWnd = (FrameWindow*)CEWM.createWindow( "TaharezLook/FrameWindow", "testWindow" );
      myRoot->addChildWindow( fWnd );


      UI::EventMgr<UI::Window> Windows;
      UI::Window* pWind = new UI::Window;
      for (int j = 0; j < 3; j++)
      {
         UI::Button* pButton = new UI::Button();
         pButton->SetPosition( 0, 20*j);
         pWind->AddItem(pButton);
      }
      Windows.Add(pWind);
      while (1)
      {
         while (cam->GetEvent (event))
         {
            if (!cam->OnEvent(event)) Windows.OnEvent(event);
            if (event.Type == sf::Event::Closed)
               exit (0);
            //else
            /*else if (event.Type == sf::Event::MouseWheelMoved)
            {
               if (event.MouseWheel.Delta == 1) {cam->ZoomIn();} else {cam->ZoomOut();}
            }*/
            else if (event.Type == sf::Event::MouseButtonPressed)
            {
               Vector2i coords = cam->GetMouse ();
               std::cout << "Mouse click coords: " << coords.x << ", " << coords.y;
               int click_level = (int)(cam->GetWorldRect ().Top / 36) - (coords.y / 36);
               std::cout << " Click level: " << click_level << std::endl;
            }

         }
         cam->Clear ();
         cam->Integrate (60);

         theTower.Update (60);
         cam->DrawModel(&theWorld); // the background and tower(s).

         interface->Update(60);
         interface->Draw ();

         cam->SetStatic(true);
         //Windows.Update();
         Windows.Draw();
         cam->SetStatic(false);
         CEGUI::System::getSingleton().renderGUI();
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