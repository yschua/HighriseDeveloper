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

#include "highrisedev.h"
#include "citizensAgent.h"
#include "pathAgent.h"

int
main ()
{
   C_Camera * cam = C_Camera::get_instance ();
   cam->set_cam_size (800, 600);
   cam->set_world_size (1280, 1080);
   cam->set_max_framerate (60);
   cam->create ("test");
   sf::Event event;
   C_Elevator* pElevator;
   C_Background * pBackground;
   C_CitizensAgent People;
   C_Tower theTower (1,10); // numero uno with 10 sub levels

   try
   {
      // stuffing the floors with test spaces
      // C_Lobby* my_lobby = new C_Lobby(370, 640, 0);
      C_office* my_office = new C_office(400, 1);
      C_office* my_office2 = new C_office (400, 2);
      C_office* my_office3 = new C_office (472, 1);
      C_office* my_office4 = new C_office (472, 2);
      C_office* my_office5 = new C_office (544, 1);
      C_office* my_office6 = new C_office (544, 2);
      C_office* my_office7 = new C_office (400, 3);
      C_office* my_office8 = new C_office (472, 3);
      C_office* my_office9 = new C_office (544, 3);

      C_Apartment* my_apt1 = new C_Apartment (400, 4);
      C_Apartment* my_apt2 = new C_Apartment (472, 4);
      C_Apartment* my_apt3 = new C_Apartment (544, 4);
      C_Apartment* my_apt4 = new C_Apartment (472, 5);
      C_Apartment* my_apt5 = new C_Apartment (544, 5);

      C_office* my_basement = new C_office (400, -1);

      C_Routes& routes = *C_Routes::get_instance();
//      C_level* sublevel = theTower.newSubLevel();
      C_level* sublevel = theTower.getLevel(-1);
      C_level* level_1 = theTower.newLevel();
      C_level* level_2 = theTower.newLevel();
      C_level* level_3 = theTower.newLevel();
      C_level* level_4 = theTower.newLevel();
      C_level* level_5 = theTower.newLevel();
      level_1->add_floor (my_office);
      level_1->add_floor (my_office3);
      level_1->add_floor (my_office5);
      level_2->add_floor (my_office2);
      level_2->add_floor (my_office4);
      level_2->add_floor (my_office6);
      level_3->add_floor (my_office7);
      level_3->add_floor (my_office8);
      level_3->add_floor (my_office9);
      level_4->add_floor (my_apt1);
      level_4->add_floor (my_apt2);
      level_4->add_floor (my_apt3);
      level_5->add_floor (my_apt4);
      level_5->add_floor (my_apt5);
      sublevel->add_floor (my_basement);
      
      pElevator = new C_Elevator( C_Elevator::LS_Standard, 472+18, -1, 6 );
      routes.add_route( pElevator );
      pBackground = new C_Background ();

      while (1) {
         while (cam->get_event (event)) {
            if (event.Type == sf::Event::Closed)
               exit (0);
            if (event.Type == sf::Event::KeyPressed)
            {
               if (event.Key.Code == sf::Key::A)
               {
                  cam->m_v.first = -200;
                  cam->m_a.first = 150;
               }
               if (event.Key.Code == sf::Key::S)
               {
                  cam->m_v.second = 200;
                  cam->m_a.second = -150;
               }
               if (event.Key.Code == sf::Key::D)
               {
                  cam->m_v.first = 200;
                  cam->m_a.first = -150;
               }
               if (event.Key.Code == sf::Key::W)
               {
                  cam->m_v.second = -200;
                  cam->m_a.second = 150;
               }
               if (event.Key.Code == sf::Key::E)
               {
                  cam->set_velocity (0, 0);
               }
            }
         }
         cam->clear ();
         cam->integrate (60);
         pBackground->draw ();
         //level_1.update (60);
         //level_1.draw ();
         //level_2.update (60);
         //level_2.draw ();
         //level_3.update (60);
         //level_3.draw ();
         //my_lobby.update (60);
         //my_lobby.draw ();
         theTower.update (60);
         routes.update (60);
         theTower.draw ();
         routes.draw ();
         cam->display ();

         People.update( 40 );
      }
   }
   catch( C_HighriseException* ex )
   {
      std::cout << "Exception caught in main: " << ex->get_Message();
   }
   return 0;
}
