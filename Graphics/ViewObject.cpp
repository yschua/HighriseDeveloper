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
#include "../Animation.h"
#include "texture.h"
#include "viewObject.h"

// all things not in 3D space. Used for interface
using namespace Gfx;

ViewObject::ViewObject ()
{
}

void ViewObject::Render(AnimationBase* pBase)
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = (pBase->GetPositionY());//-ms.y;
   float z = 100; //pBody->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y + pBase->GetHeight();
//   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
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

void ViewObject::Render(AnimationBase* pBase, const float uvs[4][2])
{
   float x = pBase->GetPositionX();//-ms.x; position needs to be a member of modelObject, let physics access it to move it.
   float y = (pBase->GetPositionY());//-ms.y;
   float z = 100; //pBody->GetPositionZ();
   float x2 = x + pBase->GetWidth();
   float y2 = y + pBase->GetHeight();
//   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      glTexCoord2fv (uvs[0]);
      glVertex3f( x, y2, z );
      glTexCoord2fv (uvs[1]);
      glVertex3f( x, y, z );
      glTexCoord2fv (uvs[2]);
      glVertex3f( x2, y, z );
      glTexCoord2fv (uvs[3]);
      glVertex3f( x2, y2, z );
   }
   glEnd();
}

void ViewObject::RenderText(AnimationBase* pBase, float x, float y, string str)
{
   const float cu = 0.035f;
   float z = 100; //pBody->GetPositionZ();
   float x2 = x + 9;
   float y2 = y + 12;
//   glBindTexture( GL_TEXTURE_2D, pBody->GetTextureID() );//to_draw.GetTexture() ); // get the current texture
   pBase->BindTexture();
   glBegin(GL_QUADS);
   {
      for( unsigned int ic = 0; ic < str.length(); ++ic)
      {
         char t=str[ic]-'0';
         float u = t * cu;
         float v = 0.9f;
         glTexCoord2f (u, v-0.32f);
         glVertex3f( x, y2, z );
         glTexCoord2f (u, v);
         glVertex3f( x, y, z );
         glTexCoord2f (u+cu, v);
         glVertex3f( x2, y, z );
         glTexCoord2f (u+cu, v-0.32f);
         glVertex3f( x2, y2, z );
         x+=8;
         x2+=8;
      }
   }
   glEnd();
}

void ViewObject::Render(SimpleQuad* pQuad)
{
   float x = pQuad->Position.x;
   float y = pQuad->Position.y;
   float z = pQuad->Position.z;

   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
//      glLoadIdentity();
      glDisable (GL_TEXTURE_2D);
      glEnable (GL_COLOR_MATERIAL);
      glTranslatef (x, y, z);
      glRotatef( -pQuad->Angle, 0, 0, 1 );
      glBegin(GL_QUADS);
      {
         glColor4ubv (pQuad->Colors[0]);
         glVertex3fv ((float*)&pQuad->Points[0].x);
         glColor4ubv (pQuad->Colors[1]);
         glVertex3fv ((float*)&pQuad->Points[1].x);
         glColor4ubv (pQuad->Colors[2]);
         glVertex3fv ((float*)&pQuad->Points[2].x);
         glColor4ubv (pQuad->Colors[3]);
         glVertex3fv ((float*)&pQuad->Points[3].x);
      }
      glEnd();
      glDisable (GL_COLOR_MATERIAL);
      glEnable (GL_TEXTURE_2D);
      glColor4ub (255,255,255,255);
   glPopMatrix();
}

