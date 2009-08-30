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

C_Camera* C_Camera::m_instance = NULL;

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

Vector2i
C_Camera::GetMouse ()
{
   Vector2i ret;
   sf::Vector2f temp = m_window->ConvertCoords (m_Input->GetMouseX (), m_Input->GetMouseY (), m_View);
   ret.x = (int) temp.x + (int) m_s.x;
   ret.y = (int) temp.y + (int) m_s.y;
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
C_Camera::GetWorldY ()
{
   return m_world_y;
}

int
C_Camera::GetWorldX ()
{
   return m_world_x;
}

void
C_Camera::SetMaxFramerate (int rate)
{
   m_window->SetFramerateLimit (rate);
}

void
C_Camera::SetCamSize (int x, int y)
{
   m_cam_x = x;
   m_cam_y = y;
   m_StaticView->SetHalfSize (x/2, y/2);
}

void
C_Camera::SetWorldSize (int x, int y)
{
   m_world_x = x;
   m_world_y = y;
}

void
C_Camera::Create (const std::string & caption)
{
   m_window->Create (sf::VideoMode (m_cam_x, m_cam_y, 32), caption);
}

C_Camera*
C_Camera::i()
{
   if (m_instance == NULL)
   {
      m_instance = new C_Camera ();
   }
   return m_instance;
}

C_Camera*
C_Camera::GetInstance()
{
   if (m_instance == NULL)
   {
      m_instance = new C_Camera ();
   }
   return m_instance;
}

void
C_Camera::Clear ()
{
   m_window->Clear (m_back_color);
}

void
C_Camera::Display ()
{
   m_window->Display ();
}

void
C_Camera::Center (int x, int y)
{
   m_s.x = x - (m_cam_x / 2);
   m_s.y = y - (m_cam_y / 2);
}

void
C_Camera::Draw (C_Animation & to_draw)
{
   if (!m_IgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.GetPositionX () - m_s.x, to_draw.GetPositionY () - m_s.y);
   else
      to_draw.sprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   m_window->Draw (*to_draw.sprite);
}

void
C_Camera::Draw (C_AnimationSingle & to_draw)
{
   if (!m_IgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.GetPositionX () - m_s.x, to_draw.GetPositionY () - m_s.y);
   else
      to_draw.sprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   m_window->Draw (*to_draw.sprite);
}

void
C_Camera::Draw (C_Tiler & to_draw)
{
   for (unsigned int i = 0; i < to_draw.m_Sprites.size (); i++)
      Draw (*to_draw.m_Sprites[i]);
}

bool
C_Camera::GetEvent (sf::Event & event)
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
