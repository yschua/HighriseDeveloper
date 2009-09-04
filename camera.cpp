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
#include "resources.h"

#include <iostream>
#include <map>
#include <vector>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "physics.h"
#include "image.h"
#include "animation.h"
#include "tiler.h"
//#include "floorBase.h"

#include "camera.h"
#else
#include "highrisedev.h"
#endif

Camera * Camera::mpInstance = NULL;

Camera::Camera ()
:  mback_color (0, 0, 0)
{

   mpWindow = new sf::RenderWindow ();
   mpWindow->Create (sf::VideoMode (800, 600, 32), "Highrise Developer" HR_VERSION);
   mpStaticView = &mpWindow->GetDefaultView ();
   mpView = new sf::View(*mpStaticView);
   mZoomFactor = 1;
   mIgnoreCamera = false;
   mpInput = &(mpWindow->GetInput ());
   mViewRect = mpView->GetRect();
   mWorldRect = sf::Rect<float>(0,0,1280,720);
   mMovingView = false;
}

Vector2i
Camera::GetMouse ()
{
   return ms + GetLocalMouse();
}

Vector2i
Camera::GetLocalMouse()
{
   return mpWindow->ConvertCoords (mpInput->GetMouseX (), mpInput->GetMouseY (), mpStaticView);
}

/*void
Camera::Zoom (float Factor)
{
 std::cout << "Zoom factor: " << Factor << std::endl;
 Factor *= 0.05;
 mpView->Zoom (1.0f + Factor);
}*/

/*int
Camera::GetWorldY ()
{
   return mworld_y;
}

int
Camera::GetWorldX ()
{
   return mworld_x;
}*/

/*int
Camera::GetCamSizeX ()
{
   return mcamx;
}

int
Camera::GetCamSizeY ()
{
   return mcamy;
}*/

void
Camera::SetMaxFramerate (int rate)
{
   mpWindow->SetFramerateLimit (rate);
}

/*void
Camera::SetCamSize (int x, int y)
{
   mpStaticView->SetHalfSize ((float)x/2, (float)y/2);
   mpView->SetHalfSize ((float)x/2, (float)y/2);
}*/

void
Camera::SetWorldSize (Vector2f Size)
{
   mWorldRect.Right = Size.x+mWorldRect.Left;
   mWorldRect.Bottom = Size.y+mWorldRect.Top;
}

void
Camera::Create (const std::string & caption)
{

}

Camera*
Camera::i()
{
   if (mpInstance == NULL)
   {
      mpInstance = new Camera ();
   }
   return mpInstance;
}

Camera*
Camera::GetInstance()
{
   if (mpInstance == NULL)
   {
      mpInstance = new Camera ();
   }
   return mpInstance;
}

void
Camera::Clear ()
{
   mpWindow->Clear (mback_color);
}

void
Camera::Display ()
{
   mpWindow->Display ();
}

void
Camera::Center (int x, int y)
{
   ms.x = x - (mViewRect.Left / 2);
   ms.y = y - (mViewRect.Top / 2);
}

void
Camera::Draw (Animation & to_draw)
{
   if (!mIgnoreCamera)
      to_draw.sprite->SetPosition (to_draw.GetPositionX () - ms.x, to_draw.GetPositionY () - ms.y);
   else
      to_draw.sprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   mpWindow->Draw (*to_draw.sprite);
}

void
Camera::Draw (AnimationSingle & to_draw)
{
   if (!mIgnoreCamera)
      to_draw.mSprite->SetPosition (to_draw.GetPositionX () - ms.x, to_draw.GetPositionY () - ms.y);
   else
      to_draw.mSprite->SetPosition (to_draw.GetPositionX (), to_draw.GetPositionY ());
   mpWindow->Draw (*to_draw.mSprite);
}

void
Camera::Draw (Tiler & to_draw)
{
   for (unsigned int i = 0; i < to_draw.mSprites.size (); i++)
      Draw (*to_draw.mSprites[i]);
}

bool
Camera::GetEvent (sf::Event & event)
{
   return mpWindow->GetEvent (event);
}

void
Camera::SetStatic (bool set)
{
   if (set)
      mpWindow->SetView (*mpStaticView);
   else
      mpWindow->SetView (*mpView);
   mIgnoreCamera = set;
}

bool
Camera::OnEvent (const sf::Event& Event)
{
   if (Event.Type == sf::Event::Resized)
   {
      // Update the views so they are not streched!
      mpView->SetHalfSize(Event.Size.Width/(2*mZoomFactor),
      Event.Size.Height/(2*mZoomFactor));
      mpStaticView->SetHalfSize(Event.Size.Width/2, (Event.Size.Height)/2);
      mpStaticView->SetCenter(Event.Size.Width/2, (Event.Size.Height)/2);
      mViewRect = mpView->GetRect();
      return false;
   }
   if (Event.Type == sf::Event::MouseMoved)
   {
      if (mMovingView)
      {
         Movepx(Vector2f(((mMouseStartPos.x-Event.MouseMove.X)), ((mMouseStartPos.y-Event.MouseMove.Y))));
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
   if (Event.Type == sf::Event::KeyPressed)
   {
      // TODO: Bounds checking here. Not familiar with the Body class...
      if (Event.Key.Code == sf::Key::A)
      {
         mv.x = -200;
         ma.x = 150;
      }
      if (Event.Key.Code == sf::Key::S)
      {
         mv.y = 200;
         ma.y = -150;
      }
      if (Event.Key.Code == sf::Key::D)
      {
         mv.x = 200;
         ma.x = -150;
      }
      if (Event.Key.Code == sf::Key::W)
      {
         mv.y = -200;
         ma.y = 150;
      }
      if (Event.Key.Code == sf::Key::E)
      {
         SetVelocity (0, 0);
      }
   }
   return false;
}

void
Camera::ZoomIn() {
   Zoom(1.05f);
}
void
Camera::ZoomOut() {
   Zoom(0.95f);
}
/////////////////////////////////////////////////////////////////////
/// Zoom the camera by the specified factor towards the center of
/// the screen. If you just want to zoom in or out, use the ZoomIn()
/// or ZoomOut() functions, as their zooms can be user-configured
/////////////////////////////////////////////////////////////////////
void
Camera::Zoom(float Factor)
{
   //Rectf ZoomedRect;
   // Calcuate the center
   Vector2f Center;
   Center.x = (mViewRect.Left+mViewRect.Right)/2;
   Center.y = (mViewRect.Top+mViewRect.Bottom)/2;
   // Divide the offset amount by the zoom factor
   Rectf DifRect;
   DifRect = mViewRect;
   // Move the rect so it is centered at (0,0)
   DifRect.Move(Vector2f(-Center.x, -Center.y));
   //DifRect.Top = mViewRect.Top-Center.y;
   DifRect.Top /= Factor;
   DifRect.Bottom /= Factor;
   DifRect.Left /= Factor;
   DifRect.Right /= Factor;
   // Move it back to it's original offset
   DifRect.Move(Vector2f(Center.x, Center.y));
   //ZoomedRect = DifRect;
   // Change the zoomed rect
   //ZoomedRect.Top = DifRect.Top+Center.y;
   //std::cout << "Top: " << ZoomedRect.Top << " Center: (" << Center.x << ", " << Center.y << ") OrigTop: " << mWorldRect.Top << '\n';
   //DifRect.Bottom = (-Center.y)+mViewRect.Bottom;

   //ZoomedRect.Bottom = DifRect.Bottom+Center.y;
   //DifRect.Left = (-Center.x)+mViewRect.Left;

   //ZoomedRect.Left = DifRect.Left+Center.x;
   //DifRect.Right = (-Center.x)+mViewRect.Right;

   //ZoomedRect.Right = DifRect.Right+Center.x;

   AdjustBounds(DifRect);
   if (CheckBounds(DifRect))
   {
      mpView->SetFromRect(DifRect);
      mZoomFactor = mZoomFactor*Factor;
      //std::cout << "Zooming by a factor of: " << mZoomFactor << '\n';
      //std::cout << "Approx Top: " << ZoomedRect.Top << " Left: " << ZoomedRect.Left << " Right: " << ZoomedRect.Right << " Bottom: " << ZoomedRect.Bottom << '\n';
      mViewRect = DifRect;
      //std::cout << "Actual Top: " << Gfx::View.GetRect().Top << " Left: " << Gfx::View.GetRect().Left << " Right: " << Gfx::View.GetRect().Right << " Bottom: " << Gfx::View.GetRect().Bottom << '\n';
      //Gfx::Window.SetView(Gfx::View);
   }
   else
   {
      std::cout << "DEBUG: mViewRect is (" << mViewRect.Top << ", " << mViewRect.Left << ", " << mViewRect.Right << ", " << mViewRect.Bottom << ")\n";
      std::cout << "DEBUG: mWorldRect is (" << mWorldRect.Top << ", " << mWorldRect.Left << ", " << mWorldRect.Right << ", " << mWorldRect.Bottom << ")\n";
   }
}

/////////////////////////////////////////////////////////////////////
/// Move the camera by the specified number of pixels
/////////////////////////////////////////////////////////////////////
void
Camera::Movepx(Vector2f Movement)
{
   Rectf NewRect = mViewRect;
   NewRect.Move(Movement);
   std::cout << "Movement: " << Movement.x << ", " << Movement.y << "\n";
   std::cout << "Orig rect: " << mViewRect.Top << ", " << mViewRect.Left << ", " << mViewRect.Right << ", " << mViewRect.Bottom << "\n";
   std::cout << "After Movement: " << NewRect.Top << ", " << NewRect.Left << ", " << NewRect.Right << ", " << NewRect.Bottom << "\n";
   AdjustBounds(NewRect);
   if (CheckBounds(NewRect))
   {
      mpView->SetFromRect(NewRect);
      mViewRect = NewRect;
      std::cout << "member rect: "; mViewRect.DebugPrint(); std::cout << "\n";// << mViewRect.Top << ", " << mViewRect.Left << ", " << mViewRect.Right << ", " << mViewRect.Bottom << "W: " << mViewRect.Width() << "H: " << mViewRect.Height() << "\n";
      std::cout << "After Adjustment: "; NewRect.DebugPrint(); std::cout << "\n";
      std::cout << "View rect: "; ((Rectf)mpView->GetRect()).DebugPrint(); std::cout << "\n";
   }
}
/////////////////////////////////////////////////////////////////////
/// Set the center of the camera in pixels
/////////////////////////////////////////////////////////////////////
void
Camera::Setpx(Vector2f Center)
{
   /*sf::Vector2<int> Center;
   Center.x = (mWorldRect.Left+mWorldRect.Right)/2;
   Center.y = (mWorldRect.Top+mWorldRect.Bottom)/2;*/
   Rectf NewRect = mViewRect;
   NewRect.Move(Vector2f(-Center.x, -Center.y));
   /*NewRect.Top = mViewRect.Top-Center.y;
   NewRect.Left = mViewRect.Left-Center.x;
   NewRect.Right = mViewRect.Right-Center.x;
   NewRect.Bottom = mViewRect.Bottom-Center.y;*/
   AdjustBounds(NewRect);
   if (CheckBounds(NewRect))
   {
      mpView->SetFromRect(NewRect);
      mViewRect = NewRect;
   }
}
/////////////////////////////////////////////////////////////////////
/// Check if a rectangle is entirely within the bounds of the world
/// Returns true if it is, false if it falls outside.
/////////////////////////////////////////////////////////////////////
bool
Camera::CheckBounds(const Rectf& RectToCheck)
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
Camera::AdjustBounds(Rectf& RectToAdjust)
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

