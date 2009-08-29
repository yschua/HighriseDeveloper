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

C_Camera * C_Camera::m_instance = NULL;

C_Camera::C_Camera ()
:  m_back_color (0, 0, 0)
{
   m_window = new sf::RenderWindow ();
   m_View = &(m_window->GetDefaultView ());
   m_StaticView = new sf::View ();
   m_ZoomFactor = 1;
   m_IgnoreCamera = false;
   m_Input = &(m_window->GetInput ());
}

std::pair <int, int>
C_Camera::GetMouse ()
{
   std::pair <int, int> ret;
   sf::Vector2f temp = m_window->ConvertCoords (m_Input->GetMouseX (), m_Input->GetMouseY (), m_View);
   ret.first = (int) temp.x + (int) m_s.first;
   ret.second = (int) temp.y + (int) m_s.second;
   return ret;
}

void
C_Camera::Zoom (float Factor)
{
   std::cout << "Zoom factor: " << Factor << std::endl;
   Factor *= 0.05;
   m_View->Zoom (1.0f + Factor);
}

int
C_Camera::get_world_y ()
{
   return m_world_y;
}

int
C_Camera::get_world_x ()
{
   return m_world_x;
}

void
C_Camera::set_max_framerate (int rate)
{
   m_window->SetFramerateLimit (rate);
}

void
C_Camera::set_cam_size (int x, int y)
{
   m_cam_x = x;
   m_cam_y = y;
   m_StaticView->SetHalfSize (x/2, y/2);
}

void
C_Camera::set_world_size (int x, int y)
{
   m_world_x = x;
   m_world_y = y;
}

void
C_Camera::create (const std::string & caption)
{
   m_window->Create (sf::VideoMode (m_cam_x, m_cam_y, 32), caption);
}

C_Camera *
C_Camera::get_instance ()
{
   if (m_instance == NULL)
   {
      m_instance = new C_Camera ();
   }
   return m_instance;
}

void
C_Camera::clear ()
{
   m_window->Clear (m_back_color);
}

void
C_Camera::display ()
{
   m_window->Display ();
}

void
C_Camera::center (int x, int y)
{
   m_s.first = x - (m_cam_x / 2);
   m_s.second = y - (m_cam_y / 2);
}

void
C_Camera::draw (C_Animation & to_draw)
{
   if (!m_IgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.get_position_x () - m_s.first, to_draw.get_position_y () - m_s.second);
   else
      to_draw.sprite->SetPosition (to_draw.get_position_x (), to_draw.get_position_y ());
   m_window->Draw (*to_draw.sprite);
}

void
C_Camera::draw (C_AnimationSingle & to_draw)
{
   if (!m_IgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.get_position_x () - m_s.first, to_draw.get_position_y () - m_s.second);
   else
      to_draw.sprite->SetPosition (to_draw.get_position_x (), to_draw.get_position_y ());
   m_window->Draw (*to_draw.sprite);
}

void
C_Camera::draw (C_Tiler & to_draw)
{
   for (int i = 0; i < to_draw.m_Sprites.size (); i++)
      draw (*to_draw.m_Sprites[i]);
}

bool
C_Camera::get_event (sf::Event & event)
{
   return m_window->GetEvent (event);
}

void
C_Camera::SetStatic (bool set)
{
   if (set)
   {
      m_window->SetView (*m_StaticView);
      m_IgnoreCamera = true;
   }
   else
   {
      m_window->SetView (*m_View);
      m_IgnoreCamera = false;
   }
}
