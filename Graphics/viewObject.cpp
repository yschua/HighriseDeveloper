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


#include <iostream>
#include <string>
#include "../physics.h"
#include "texture.h"
#include "viewObject.h"

// all things not in 3D space. Used for interface
using namespace Gfx;

ViewObject::ViewObject ()
{
}

void ViewObject::Render(Body* pBody)
{
   float x = pBody->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = -pBody->GetPositionY();//-ms.y;
   float z = 100; //pBody->GetPositionZ();
   float x2 = x + pBody->GetWidth();
   float y2 = y + pBody->GetHeight();
   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   glBegin(GL_QUADS);
   {
      glTexCoord2f( 0.0, 1.0 );
      glVertex3f( x, y2, z );
      glTexCoord2f( 0.0, 0.0 );
      glVertex3f( x, y, z );
      glTexCoord2f( 1.0, 0.0 );
      glVertex3f( x2, y, z );
      glTexCoord2f( 1.0, 1.0 );
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

