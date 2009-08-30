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
   static C_Camera* GetInstance();
   static C_Camera* i();
   void Display ();
   void Clear ();
   void Draw (C_Animation & to_draw);
   void Draw (C_AnimationSingle & to_draw);
   void Draw (C_Tiler & to_draw);
   void SetMaxFramerate (int rate);
   void SetCamSize (int x, int y);
   void SetWorldSize (int x, int y);
   int GetWorldX ();
   int GetWorldY ();
   void Create (const std::string & caption);
   void Center (int x, int y);
   bool GetEvent (sf::Event & event);
   void Zoom (float Factor);
   void SetStatic (bool set);
   Vector2i GetMouse ();
};

#endif
