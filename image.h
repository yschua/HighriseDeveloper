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

#ifndef _IMAGE_H
#define _IMAGE_H
class image_manager
{
private:
    std::string m_path_prefix;
    std::map<std::string, sf::Image *> m_images;
    static image_manager * m_instance;
    image_manager ();
    
public:
    static image_manager * get_instance ();
    sf::Image * get_image (const std::string & name);
    int preload_image (const std::string & name);
    void set_path (const std::string & prefix);
};
#endif
