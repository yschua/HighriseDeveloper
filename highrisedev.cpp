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

#include "Window/Window.h"
#include "Window/Button.h"
#include "Window/TextBox.h"
#include "highrisedev.h"

#include "AI/citizensAgent.h"
#include "AI/pathAgent.h"
#include "AI/floorAgent.h"

int
main ()
{
   Camera * cam = Camera::GetInstance ();
   cam->Create ("test");

   //cam->SetCamSize (800, 600);
   cam->SetWorldSize (Vector2f(1280, 720));
   cam->SetMaxFramerate (60);
   sf::Event event;
   Elevator* pElevator;
   Background * pBackground;
   Tower theTower (1, 10); // numero uno with 10 sub levels
   CitizensAgent People( theTower ); // known tower, later this will be a tower list for mutiple towers
   Interface* interface = new Interface();

   cam->InitGL();

   try
   {
      // stuffing the floors with test spaces
      office* my_office = new office(400, 1, &theTower);
      office* my_office2 = new office (400, 2, &theTower);
      office* my_office3 = new office (472, 1, &theTower);
      office* my_office4 = new office (472, 2, &theTower);
      office* my_office5 = new office (544, 1, &theTower);
      office* my_office6 = new office (544, 2, &theTower);
      office* my_office7 = new office (400, 3, &theTower);
      office* my_office8 = new office (472, 3, &theTower);
      office* my_office9 = new office (544, 3, &theTower);

      Apartment* my_apt1 = new Apartment (400, 4, &theTower);
      Apartment* my_apt2 = new Apartment (472, 4, &theTower);
      Apartment* my_apt3 = new Apartment (544, 4, &theTower);
      Apartment* my_apt4 = new Apartment (472, 5, &theTower);
      Apartment* my_apt5 = new Apartment (544, 5, &theTower);

      office* my_basement = new office (400, -1, &theTower);

      Level* sublevel = theTower.GetLevel(-1);
      Level* level_1 = theTower.NewLevel (400, 1, 544+74);
      Level* level_2 = theTower.NewLevel (400, 2, 544+74);
      Level* level_3 = theTower.NewLevel (400, 3, 544+74);
      Level* level_4 = theTower.NewLevel (400, 4, 544+74);
      Level* level_5 = theTower.NewLevel (472, 5, 544+74);
      level_1->AddFloor (my_office);
      level_1->AddFloor (my_office3);
      level_1->AddFloor (my_office5);
      level_2->AddFloor (my_office2);
      level_2->AddFloor (my_office4);
      level_2->AddFloor (my_office6);
      level_3->AddFloor (my_office7);
      level_3->AddFloor (my_office8);
      level_3->AddFloor (my_office9);
      level_4->AddFloor (my_apt1);
      level_4->AddFloor (my_apt2);
      level_4->AddFloor (my_apt3);
      level_5->AddFloor (my_apt4);
      level_5->AddFloor (my_apt5);
      sublevel->AddFloor (my_basement);

      interface = new Interface ();

      pElevator = new Elevator( Elevator::LS_Standard, 472, -1, 6, &theTower );
      theTower.GetRoutes().AddRoute( pElevator );
      pElevator = new Elevator( Elevator::LS_Standard, 472 + 36 + 9, 0, 5, &theTower );
      theTower.GetRoutes().AddRoute( pElevator );
      pBackground = new Background ();


      UI::EventMgr<UI::Window> Windows;
      for (int i = 0; i < 5; i++)
      {
         UI::Window* pWind = new UI::Window;
         if( i ==1 )
         {
            UI::TextBox* pText = new UI::TextBox();
            pText->SetPosition(0, -400);
            pText->SetText( "Office" );
            pWind->AddItem(pText);
            UI::Button* pButton = new UI::Button();
            pButton->SetPosition(0, 20);
            pButton->SetText( "Button" );
            pWind->AddItem(pButton);
         }
         else
         {
            for (int j = 0; j < 3; j++)
            {
               UI::Button* pButton = new UI::Button();
               pButton->SetPosition(0, 20*j);
               pWind->AddItem(pButton);
            }
         }
         Windows.Add(pWind);
      }
      while (1)
      {
         while (cam->GetEvent (event))
         {
            cam->OnEvent(event);
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
         cam->DrawModel(pBackground);
         cam->DrawModel(&theTower);

         cam->SetStatic(true);
         //Windows.Update();
         Windows.Draw();
         cam->SetStatic(false);
         interface->Update(60);
         interface->Draw ();
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
