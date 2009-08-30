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

#ifndef _TILER_H
#define _TILER_H

class C_Tiler
{
private:
   bool m_ClipMode;
   int m_X, m_X2, m_Y;
   int m_ImageSizeX, m_ImageSizeY;
   sf::Image * m_frame;

public:
   enum draw_direction
   {
      Horizontal,
      Vertical
   };
   draw_direction m_direction;
   C_Tiler (sf::Image * image, draw_direction direction, int x, int x2, int y);
   void CalcPos ();
   void Resize (int x, int x2);
   void SetY (int y);
   void SetImage (sf::Image * image);
   std::vector <C_AnimationSingle *> m_Sprites;
   void SetClipping (bool clipping_mode);
};

#endif
