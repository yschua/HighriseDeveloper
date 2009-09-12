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

#include "Types/Vector2.h"
#include "Types/Rect.h"
#include "interface.h"
#include "physics.h"
#include "Window/event.h"

class Animation;
class AnimationSingle;
class Tiler;
class World;

class Camera : public Body, public EventBase
{
private:
   //int mworld_x, mworld_y, mcamx, mcamy;
   sf::Window* mpWindow;
   sf::View* mpView;
   sf::View* mpStaticView;
   sf::Color mback_color;
   sf::WindowSettings Settings;
   const sf::Input* mpInput;
   static Camera* mpInstance;
   float mZoomFactor;
   float mAspect;
   bool mIgnoreCamera;
   Rectf mWorldRect;
   Rectf mViewRect;
   Vector2i mMouseStartPos;
   bool mMovingView;

   // CTOR/DTOR
private:
   Camera ();
protected:
   ~Camera() {};
   // instance
public:
   static Camera* GetInstance();
   static Camera* i();
   const sf::Input * GetInput ();

   // properties
   void SetMaxFramerate (int rate);
   //void SetCamSize (int x, int y);
   void SetWorldSize (Vector2f);
   Rectf GetWorldRect() { return mWorldRect; }
   Rectf GetCamRect() { return mViewRect; }
   //int GetWorldX ();
   //int GetWorldY ();
   //int GetCamSizeX ();
   //int GetCamSizeY ();
   Vector2i GetMouse ();
   Vector2i GetLocalMouse();

   // methods
   void SetActive();
   void Display ();
   void Clear ();
   void InitGL();

   void DrawModel (World* pModel);
   void DrawInterface (Interface* pI); // temp until we build the rest of the view
   // Four Draw methods to be depricated when we move the view objects
   //void Draw (Animation & to_draw);
   //void Draw (AnimationSingle & to_draw); // used by Interface for now
   //void Draw (Tiler & to_draw);
   void Draw (const sf::Drawable& ToDraw)
   {
//      mpWindow->Draw(ToDraw);
   }
   void Create (const std::string & caption);
   void Center (int x, int y);
   //bool Resize (Vector2i viewSize);
   bool GetEvent (sf::Event & event);
protected:
   void Zoom (float Factor);
   void SetStatic (bool set);
public:
   bool OnEvent(const sf::Event& Event);
   void ZoomIn();
   void ZoomOut();
   void Movepx(Vector2f Movement);
   void Setpx(Vector2f Center);
   bool CheckBounds(const Rectf& RectToCheck);
   void AdjustBounds(Rectf& RectToAdjust);

   // Event hanlders
   bool OnKeyDown (sf::Key::Code Key);
   bool OnMouseWheel (int Delta);
   bool OnResize(Vector2i);
};

#endif
