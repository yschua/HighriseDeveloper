#include <iostream>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "image.h"

image_manager * image_manager::m_instance = NULL;

image_manager::image_manager ()
:   m_path_prefix ("")
{
}

image_manager *
image_manager::get_instance ()
{
    if (m_instance == NULL) {
        m_instance = new image_manager ();
    }
    return m_instance;
}

void
image_manager::set_path (const std::string & prefix)
{
    m_path_prefix = prefix;
}

sf::Image *
image_manager::get_image (const std::string & name)
{
    if (m_images[name] == NULL) {
        sf::Image * temp;
        temp = new sf::Image;
        std::cout << "Loading file " << m_path_prefix + name << std::endl;
        temp->LoadFromFile (m_path_prefix + name);
        m_images[name] = temp;
        return temp;
    }
    return m_images[name];
}

int
image_manager::preload_image (const std::string & name)
{
    if (m_images[name] == NULL) {
        sf::Image * temp;
        temp = new sf::Image;
        temp->LoadFromFile (m_path_prefix + name);
        m_images[name] = temp;
        return 1;
    }
    return 0;
}
