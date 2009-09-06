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
#include "Graphics/texture.h"

using namespace Gfx;

class Tiler
{
private:
   bool mClipMode;
   int mX;
   int mY;
   int mZ;
   int mWidth;
   int mHeight;
   int mTesselX;
   int mTesselY;
   //int mImageSizeX, mImageSizeY;
//   sf::Image * mframe;
   Texture* mpTexture;

public:
   enum draw_direction
   {
      Horizontal,
      Vertical
   };
   draw_direction mdirection;
//   Tiler (sf::Image * image, draw_direction direction, int x, int x2, int y);
   Tiler (Texture* pTex, draw_direction direction, int x, int y, int z, int width, int height);
   void SetY (int y);
   int GetTesselX() { return mTesselX; }
   int GetTesselY() { return mTesselY; }
   int GetPositionX() { return mX; }
   int GetPositionY() { return mY; }
   int GetWidth() { return mWidth; }
   int GetHeight() { return mHeight; }
   int GetTextureID() { return mpTexture->GetID(); }

//   void SetImage (sf::Image * image);
   void SetTexture (Texture* pTex) { mpTexture = pTex; }
   void SetTessel (int x, int y) { mTesselX=x; mTesselY=y; }

   void CalcPos ();
   void Resize (int x, int x2, int tesx, int tessy);
//   std::vector <AnimationSingle *> mSprites;
   void SetClipping (bool clipping_mode);
};

#endif
