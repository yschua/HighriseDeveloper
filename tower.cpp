#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "physics.h"
#include "animation.h"
#include "image.h"
#include "camera.h"

int
main ()
{
    camera * cam = camera::get_instance ();
    cam->set_cam_size (800, 600);
    cam->set_cam_size (1024, 768);
    cam->set_max_framerate (60);
    cam->create ("test");
    image_manager * image_man = image_manager::get_instance ();
    image_man->set_path ("data/");
    animation test_anim;
    test_anim.add_frame (image_man->get_image ("office_o_d_1.png"), 1000);
    test_anim.add_frame (image_man->get_image ("office_o_d_2.png"), 1000);
    test_anim.add_frame (image_man->get_image ("office_o_d_3.png"), 1000);
    test_anim.add_frame (image_man->get_image ("office_o_d_4.png"), 1000);
    test_anim.add_frame (image_man->get_image ("office_o_d_5.png"), 1000);
    sf::Event event;
    while (1) {
        while (cam->get_event (event)) {
            if (event.Type == sf::Event::Closed)
                exit (0);
        }
        cam->clear ();
        test_anim.update (100);
        cam->draw (test_anim);
        cam->display ();
    }
    return 0;
}
