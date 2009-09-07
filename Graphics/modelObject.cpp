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

//#include "highrisedev.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "../physics.h"
#include "../tiler.h"
#include "texture.h"
#include "modelObject.h"

using namespace Gfx;

ModelObject::ModelObject ()
{
}

void ModelObject::Render(Body* pBody)
{
   float x = pBody->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = pBody->GetPositionY();//-ms.y;
   float z = 0; //pBody->GetPositionZ();
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

void ModelObject::Render(Tiler* pTiler)
{
   float x = pTiler->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = pTiler->GetPositionY();//-ms.y;
   float z = 0;//pTiler->GetPositionZ();
   float x2 = x + pTiler->GetWidth();
   float y2 = y + pTiler->GetHeight();
   float xT = pTiler->GetTesselX();
   float yT = pTiler->GetTesselY();
   glBindTexture( GL_TEXTURE_2D, pTiler->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   glBegin(GL_QUADS);
   {
      glTexCoord2f( 0.0, yT );
      glVertex3f( x, y2, z );
      glTexCoord2f( 0.0, 0.0 );
      glVertex3f( x, y, z );
      glTexCoord2f( xT, 0.0 );
      glVertex3f( x2, y, z );
      glTexCoord2f( xT, yT );
      glVertex3f( x2, y2, z );
   }
   glEnd();
}
