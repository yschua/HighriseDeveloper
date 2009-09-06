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

Tiler::Tiler (Texture* pTex, draw_direction direction, int x, int y, int z, int width, int height)
{
   mpTexture = pTex;
   mClipMode = true;
//   mframe = image;
   mX = x;
   //mX2 = x2;
   mY = y;
   mZ = z;
   mWidth = width;
   mHeight = height;
   mTesselX = 24;    // These are done in hardware as fills
   mTesselY = 1;
   //mImageSizeX = mframe->GetWidth();
   //mImageSizeY = mframe->GetHeight();

   if ( mpTexture == NULL ) //(mImageSizeY * mImageSizeX) == 0 )
      throw new HighriseException( "Missing image file" );

   // Hardware shader does this !
   //if (direction == Horizontal)
   //{
   //   unsigned int tiled_num = (unsigned int) ((x2 - x) / mImageSizeX);
   //   int part = (int) ((tiled_num * mImageSizeX) + x);
   //   for ( unsigned int i = 0; i <= tiled_num; i++)
   //   {
   //      AnimationSingle * new_tiler_part = new AnimationSingle (mframe);
   //      mSprites.push_back (new_tiler_part);
   //      new_tiler_part->SetPosition ((float)(mX + (i * mImageSizeX)), (float)mY);
   //   }
   //   if (mClipMode)
   //   {
   //      AnimationSingle * end = mSprites[mSprites.size()-1];
   //      end->SetSubRect (0, 0, x2 - part, mImageSizeY);
   //   }
   //}
   //else
   //{
   //   unsigned int tiled_num = (unsigned int) ((x2 - x) / mImageSizeY);
   //   int part = (int) ((tiled_num * mImageSizeY) + x);
   //   for ( unsigned int i = 0; i <= tiled_num; i++)
   //   {
   //      AnimationSingle * new_tiler_part = new AnimationSingle (mframe);
   //      mSprites.push_back (new_tiler_part);
   //      new_tiler_part->SetPosition ((float)mY, (float)(mX + (i * mImageSizeY)));
   //   }
   //   if (mClipMode)
   //   {
   //      AnimationSingle * end = mSprites[mSprites.size()-1];
   //      end->SetSubRect (0, 0, mImageSizeX, x2 - part);
   //   }
   //}
}

void
Tiler::SetClipping (bool clipping_mode)
{
   mClipMode = clipping_mode;
}
