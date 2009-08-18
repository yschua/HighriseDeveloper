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

#ifndef _CAMERA_H
#define _CAMERA_H
class camera : public body
{
private:
    int m_world_x, m_world_y, m_cam_x, m_cam_y;
    sf::RenderWindow * m_window;
    sf::Color m_back_color;
    static camera * m_instance;
    camera ();

public:
    static camera * get_instance ();
    void display ();
    void clear ();
    void draw (animation & to_draw);
    void set_max_framerate (int rate);
    void set_cam_size (int x, int y);
    void set_world_size (int x, int y);
    int get_world_y ();
    void create (const std::string & caption);
    void center (int x, int y);
    bool get_event (sf::Event & event);
};
#endif
