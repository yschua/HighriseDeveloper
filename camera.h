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

#ifndef _CAMERA_H
#define _CAMERA_H

class C_Camera : public C_Body
{
private:
   int m_world_x, m_world_y, m_cam_x, m_cam_y;
   sf::RenderWindow * m_window;
   sf::View * m_View;
   sf::View * m_StaticView;
   sf::Color m_back_color;
   static C_Camera * m_instance;
   C_Camera ();
   float m_ZoomFactor;
   bool m_IgnoreCamera;
   const sf::Input * m_Input;

public:
   static C_Camera * get_instance ();
   void display ();
   void clear ();
   void draw (C_Animation & to_draw);
   void draw (C_AnimationSingle & to_draw);
   void draw (C_Tiler & to_draw);
   void set_max_framerate (int rate);
   void set_cam_size (int x, int y);
   void set_world_size (int x, int y);
   int get_world_y ();
   int get_world_x ();
   void create (const std::string & caption);
   void center (int x, int y);
   bool get_event (sf::Event & event);
   void Zoom (float Factor);
   void SetStatic (bool set);
   std::pair <int, int> GetMouse ();
};

#endif
