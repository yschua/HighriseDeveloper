/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <list>

#include "physics.h"
#include "animation.h"
#include "image.h"
#include "camera.h"
#include "floorbase.h"
#include "office.h"
#include "level.h"

int
main ()
{
    camera * cam = camera::get_instance ();
    cam->set_cam_size (800, 600);
    cam->set_world_size (1280, 1080);
    cam->set_max_framerate (60);
    cam->create ("test");
    image_manager * image_man = image_manager::get_instance ();
    sf::Event event;
    C_office my_office (400, 1);
    C_office my_office2 (400, 2);
    C_office my_office3 (472, 1);
    C_office my_office4 (472, 2);
    C_office my_office5 (544, 1);
    C_office my_office6 (544, 2);
    C_office my_office7 (450, 3);
    C_office my_office8 (522, 3);
    C_level level_1 (1);
    C_level level_2 (2);
    C_level level_3 (3);
    level_1.add_floor (&my_office);
    level_1.add_floor (&my_office3);
    level_1.add_floor (&my_office5);
    level_2.add_floor (&my_office2);
    level_2.add_floor (&my_office4);
    level_2.add_floor (&my_office6);
    level_3.add_floor (&my_office7);
    level_3.add_floor (&my_office8);
    while (1) {
        while (cam->get_event (event)) {
            if (event.Type == sf::Event::Closed)
                exit (0);
            if (event.Type == sf::Event::KeyPressed) {
                if (event.Key.Code == sf::Key::A) {
                    cam->m_v.first = -200;
                    cam->m_a.first = 150;
                }
                if (event.Key.Code == sf::Key::S) {
                    cam->m_v.second = 200;
                    cam->m_a.second = -150;
                }
                if (event.Key.Code == sf::Key::D) {
                    cam->m_v.first = 200;
                    cam->m_a.first = -150;
                }
                if (event.Key.Code == sf::Key::W) {
                    cam->m_v.second = -200;
                    cam->m_a.second = 150;
                }
                if (event.Key.Code == sf::Key::E) {
                    cam->set_velocity (0, 0);
                }
            }
        }
        cam->clear ();
        cam->integrate (60);
        level_1.update (60);
        level_1.draw ();
        level_2.update (60);
        level_2.draw ();
        level_3.update (60);
        level_3.draw ();
        cam->display ();
    }
    return 0;
}
