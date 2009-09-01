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

class Animation;
class AnimationSingle;
class Tiler;

class Camera : public C_Body
{
private:
   int m_world_x, m_world_y, m_cam_x, m_cam_y;
   sf::RenderWindow* mpWindow;
   sf::View* mpView;
   sf::View* mpStaticView;
   sf::Color m_back_color;
   static Camera * mpInstance;
   Camera ();
   float mZoomFactor;
   bool mIgnoreCamera;
   const sf::Input* mpInput;
   sf::Rect<float> mWorldRect;
   sf::Rect<float> mViewRect;
   Vector2i mMouseStartPos;
   bool mMovingView;
public:
   static Camera* GetInstance();
   static Camera* i();
   void Display ();
   void Clear ();
   void Draw (Animation & to_draw);
   void Draw (AnimationSingle & to_draw);
   void Draw (Tiler & to_draw);
   void Draw (const sf::Drawable& ToDraw) {
      mpWindow->Draw(ToDraw);
   }
   void SetMaxFramerate (int rate);
   void SetCamSize (int x, int y);
   void SetWorldSize (int x, int y);
   int GetWorldX ();
   int GetWorldY ();
   int GetCamSizeX ();
   int GetCamSizeY ();
   void Create (const std::string & caption);
   void Center (int x, int y);
   bool GetEvent (sf::Event & event);
   void Zoom (float Factor);
   void SetStatic (bool set);
   Vector2i GetMouse ();
   Vector2i GetLocalMouse();
   bool OnEvent(const sf::Event& Event);
   void ZoomIn();
   void ZoomOut();
   void Movepx(Vector2f Movement);
   void Setpx(Vector2f Center);
   bool CheckBounds(const sf::Rect<float>& RectToCheck);
   void AdjustBounds(sf::Rect<float>& RectToAdjust);
};

#endif
