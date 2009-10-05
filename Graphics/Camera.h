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

#include "../Types/Vector2.h"
#include "../Types/Rect.h"
#include "../Root/Physics.h"
#include "../Window/Interface.h"
#include "../Window/Event.h"

class Animation;
class AnimationSingle;
class Tiler;
class Scene;
class Level;
class CitizensAgent;

class Camera : public Body, public EventBase
{
private:
   Vector2f mScene, mCam;
   sf::Window* mpWindow;
   const sf::Input* mpInput;
   static Camera* mpInstance;
   float mZoomFactor;
   float mAspect;
   bool mIgnoreCamera;
   Vector2i mMouseStartPos;
   bool mMovingView;
   Camera ();

protected:
   ~Camera() {};
   void Zoom (float Factor);
   void SetStatic (bool set);
   // instance

public:
   static Camera* GetInstance();
   const sf::Input * GetInput ();
   // properties
   void SetMaxFramerate (int rate);
   float GetAspect () { return mAspect; }
   float GetZoom() { return mZoomFactor; }
   //void SetCamSize (int x, int y);
   void SetSceneSize (Vector2f);
   Vector2f GetSceneSize () { return mScene; }
   Vector2f GetCamSize () { return mCam; }
   Vector2i GetMouse ();
   Vector2i GetLocalMouse();

   // methods
   void SetActive();
   void Display ();
   void Clear ();
   void InitGL();

   void DrawModel (Scene* pModel);
   void DrawPeople (CitizensAgent* peeps);
   void DrawInterface (Interface* pI);
   int  RenderFramework (Scene* pModel, Vector2f mouse, int level); // level == 0, render the whole tower.
   int  TranslateX (Scene* pModel, Vector2f mouse);
   void Create (const std::string & caption);
   void Center (int x, int y);
   bool GetEvent (sf::Event & event);
   void ZoomIn();
   void ZoomOut();

   // Event hanlders
   bool OnKeyDown (sf::Key::Code Key);
   bool OnMouseWheel (int Delta);
   bool OnResize(Vector2i);
};

#endif
