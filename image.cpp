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
