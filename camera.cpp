/*This file is part of Highrise Developer.
 *
 *Highrise Developer is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.

 *Highrise Developer is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 *
 *You should have received a copy of the GNU General Public License
 *along with Highrise Developer.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef WIN32
#include <iostream>
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "tiler.h"
#include "floorBase.h"

#include "camera.h"
#else
#include "highrisedev.h"
#endif

C_Camera * C_Camera::mpInstance = NULL;

C_Camera::C_Camera ()
:  m_back_color (0, 0, 0)
{
   mpWindow = new sf::RenderWindow ();
   mpStaticView = &mpWindow->GetDefaultView ();
   mpView = new sf::View(*mpStaticView);
   mZoomFactor = 1;
   mIgnoreCamera = false;
   mpInput = &(mpWindow->GetInput ());
   mViewRect = mpView->GetRect();
   mWorldRect = sf::Rect<float>(0,0,1000,1000);
   mMovingView = false;
}

Vector2i
C_Camera::GetMouse ()
{
   return m_s + GetLocalMouse();
}

Vector2i
C_Camera::GetLocalMouse()
{
   return mpWindow->ConvertCoords (mpInput->GetMouseX (), mpInput->GetMouseY (), mpStaticView);
}

/*void
C_Camera::Zoom (float Factor)
{
 std::cout << "Zoom factor: " << Factor << std::endl;
 Factor *= 0.05;
 mpView->Zoom (1.0f + Factor);
}*/

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

int
C_Camera::GetCamSizeX ()
{
   return m_cam_x;
}

int
C_Camera::GetCamSizeY ()
{
   return m_cam_y;
}

void
C_Camera::SetMaxFramerate (int rate)
{
   mpWindow->SetFramerateLimit (rate);
}

void
C_Camera::SetCamSize (int x, int y)
{
   m_cam_x = x;
   m_cam_y = y;
   mpStaticView->SetHalfSize ((float)x/2, (float)y/2);
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
   mpWindow->Create (sf::VideoMode (m_cam_x, m_cam_y, 32), caption);
}

C_Camera*
C_Camera::i()
{
   if (mpInstance == NULL)
   {
      mpInstance = new C_Camera ();
   }
   return mpInstance;
}

C_Camera*
C_Camera::GetInstance()
{
   if (mpInstance == NULL)
   {
      mpInstance = new C_Camera ();
   }
   return mpInstance;
}

void
C_Camera::Clear ()
{
   mpWindow->Clear (m_back_color);
}

void
C_Camera::Display ()
{
   mpWindow->Display ();
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
   if (!mIgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.GetPositionX () - m_s.x, to_draw.GetPositionY () - m_s.y);
   else
      to_draw.sprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   mpWindow->Draw (*to_draw.sprite);
}

void
C_Camera::Draw (C_AnimationSingle & to_draw)
{
   if (!mIgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.GetPositionX () - m_s.x, to_draw.GetPositionY () - m_s.y);
   else
      to_draw.sprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   mpWindow->Draw (*to_draw.sprite);
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
   return mpWindow->GetEvent (event);
}

void
C_Camera::SetStatic (bool set)
{
   if (set)
      mpWindow->SetView (*mpStaticView);
   else
      mpWindow->SetView (*mpView);
   mIgnoreCamera = set;
}

bool
C_Camera::OnEvent (const sf::Event& Event)
{
   if (Event.Type == sf::Event::Resized)
   {
      mpView->SetHalfSize(Event.Size.Width/(2*mZoomFactor),
      Event.Size.Height/(2*mZoomFactor));
      //Gfx::Window.SetView(Gfx::View);
      mpStaticView->SetHalfSize(Event.Size.Width/2, (Event.Size.Height)/2);
      mpStaticView->SetCenter(Event.Size.Width/2, (Event.Size.Height)/2);
      mViewRect = mpView->GetRect();
      return false;
   }
   if (Event.Type == sf::Event::MouseMoved)
   {
      if (mMovingView)
      {
         Movepx(Vector2i(((mMouseStartPos.x-Event.MouseMove.X)/mZoomFactor), ((mMouseStartPos.y-Event.MouseMove.Y)/mZoomFactor)));
         mMouseStartPos.x = Event.MouseMove.X;
         mMouseStartPos.y = Event.MouseMove.Y;
         return true;
      }
   }
   if (Event.Type == sf::Event::MouseButtonPressed)
   {
      if (mpInput->IsKeyDown(sf::Key::LControl) || mpInput->IsKeyDown(sf::Key::RControl))
      {
         mMovingView = true;
         mMouseStartPos.x = mpInput->GetMouseX();
         mMouseStartPos.y = mpInput->GetMouseY();
         return true;
      }
   }
   if (Event.Type == sf::Event::MouseWheelMoved)
   {
      if (Event.MouseWheel.Delta > 0)
         ZoomIn();
      else
         ZoomOut();
      return true;
   }
   if (Event.Type == sf::Event::KeyReleased)
   {
      if (Event.Key.Code == sf::Key::LControl || Event.Key.Code == sf::Key::RControl)
         mMovingView = false;
   }
   return false;
}

void
C_Camera::ZoomIn() {
   Zoom(1.25f);
}
void
C_Camera::ZoomOut() {
   Zoom(0.8f);
}
/////////////////////////////////////////////////////////////////////
/// Zoom the camera by the specified factor towards the center of
/// the screen. If you just want to zoom in or out, use the ZoomIn()
/// or ZoomOut() functions, as their zooms can be user-configured
/////////////////////////////////////////////////////////////////////
void
C_Camera::Zoom(float Factor)
{
   sf::Rect<float> ZoomedRect;
   sf::Vector2<float> Center;
   Center.x = (mViewRect.Left+mViewRect.Right)/2;
   Center.y = (mViewRect.Top+mViewRect.Bottom)/2;
   sf::Rect<float> DifRect;
   DifRect.Top = (-Center.y)+mViewRect.Top;
   DifRect.Top /= Factor;
   ZoomedRect.Top = DifRect.Top+Center.y;
   std::cout << "Top: " << ZoomedRect.Top << " Center: (" << Center.x << ", " << Center.y << ") OrigTop: " << mWorldRect.Top << '\n';
   DifRect.Bottom = (-Center.y)+mViewRect.Bottom;
   DifRect.Bottom /= Factor;
   ZoomedRect.Bottom = DifRect.Bottom+Center.y;
   DifRect.Left = (-Center.x)+mViewRect.Left;
   DifRect.Left /= Factor;
   ZoomedRect.Left = DifRect.Left+Center.x;
   DifRect.Right = (-Center.x)+mViewRect.Right;
   DifRect.Right /= Factor;
   ZoomedRect.Right = DifRect.Right+Center.x;

   AdjustBounds(ZoomedRect);
   if (CheckBounds(ZoomedRect))
   {
      mpView->SetFromRect(ZoomedRect);
      mZoomFactor = mZoomFactor*Factor;
      std::cout << "Zooming by a factor of: " << mZoomFactor << '\n';
      std::cout << "Approx Top: " << ZoomedRect.Top << " Left: " << ZoomedRect.Left << " Right: " << ZoomedRect.Right << " Bottom: " << ZoomedRect.Bottom << '\n';
      mViewRect = ZoomedRect;
      //std::cout << "Actual Top: " << Gfx::View.GetRect().Top << " Left: " << Gfx::View.GetRect().Left << " Right: " << Gfx::View.GetRect().Right << " Bottom: " << Gfx::View.GetRect().Bottom << '\n';
      //Gfx::Window.SetView(Gfx::View);
   }
   else
   {
      std::cout << "DEBUG: mWorldView is (" << mViewRect.Top << ", " << mViewRect.Left << ", " << mViewRect.Right << ", " << mViewRect.Bottom << ")\n";
   }
}

/////////////////////////////////////////////////////////////////////
/// Move the camera by the specified number of pixels
/////////////////////////////////////////////////////////////////////
void
C_Camera::Movepx(Vector2f Movement)
{
   sf::Rect<float> NewRect = mViewRect;
   NewRect.Offset(Movement.x, Movement.y);
   AdjustBounds(NewRect);
   if (CheckBounds(NewRect))
   {
      mpView->SetFromRect(NewRect);
      mViewRect = NewRect;
   }
}
/////////////////////////////////////////////////////////////////////
/// Set the center of the camera in pixels
/////////////////////////////////////////////////////////////////////
void
C_Camera::Setpx(Vector2f Center)
{
   /*sf::Vector2<int> Center;
   Center.x = (mWorldRect.Left+mWorldRect.Right)/2;
   Center.y = (mWorldRect.Top+mWorldRect.Bottom)/2;*/
   sf::Rect<float> NewRect;
   NewRect.Top = mViewRect.Top-Center.y;
   NewRect.Left = mViewRect.Left-Center.x;
   NewRect.Right = mViewRect.Right-Center.x;
   NewRect.Bottom = mViewRect.Bottom-Center.y;
   AdjustBounds(NewRect);
   if (CheckBounds(NewRect))
   {
      mViewRect = NewRect;
      mpView->SetFromRect(NewRect);
   }
}
/////////////////////////////////////////////////////////////////////
/// Check if a rectangle is entirely within the bounds of the world
/// Returns true if it is, false if it falls outside.
/////////////////////////////////////////////////////////////////////
bool
C_Camera::CheckBounds(const sf::Rect<float>& RectToCheck)
{
   if (RectToCheck.Left < mWorldRect.Left)
      std::cout << "Outisde of Left bound\n";
   else if (RectToCheck.Right > mWorldRect.Right)
      std::cout << "Outside of Right bound\n";
   else if (RectToCheck.Top < mWorldRect.Top)
      std::cout << "Ouside of Top bound\n";
   else if (RectToCheck.Bottom > mWorldRect.Bottom)
      std::cout << "Outside of Bottom bound\n";
   else
      return true;
   return false;
}
/////////////////////////////////////////////////////////////////////
/// Adjusts a rectangle so that it is within the bounds of the world
/// The rectangle passed as reference is changed.
/////////////////////////////////////////////////////////////////////
void
C_Camera::AdjustBounds(sf::Rect<float>& RectToAdjust)
{
   while (RectToAdjust.Left < mWorldRect.Left)
   {
      RectToAdjust.Left++;
      RectToAdjust.Right++;
   }
   while (RectToAdjust.Right > mWorldRect.Right)
   {
      RectToAdjust.Right--;
      RectToAdjust.Left--;
   }
   while (RectToAdjust.Top < mWorldRect.Top)
   {
      RectToAdjust.Top++;
      RectToAdjust.Bottom++;
   }
   while (RectToAdjust.Bottom > mWorldRect.Bottom)
   {
      RectToAdjust.Bottom--;
      RectToAdjust.Top--;
   }
   if (!CheckBounds(RectToAdjust))
      std::cout << "Unable to adjust rect!";
}

