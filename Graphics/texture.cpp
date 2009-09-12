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
#include "texture.h"
#include "SFML/Graphics.hpp"

using namespace Gfx;

Texture::Texture( const string& pszName )
{
   mName = pszName;
   mID = 0;
}

bool Texture::Load (const string& pszName, int channels)
{
   if (mID>0)
   {
      // UnloadTexture (mID);
   }
   sf::Image * temp;
   temp = new sf::Image;
   std::cout << "Loading file " << pszName << std::endl;
   temp->LoadFromFile (pszName);
   glGenTextures (1, &mID);
   glBindTexture (GL_TEXTURE_2D, mID);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); // setup for the tiler or animation
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);   // near/far filters
   glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

   mChannels = channels;
   glTexImage2D(GL_TEXTURE_2D, 0, mChannels, temp->GetWidth(), temp->GetHeight(), 0, mChannels , GL_UNSIGNED_BYTE, temp->GetPixelsPtr() );

   glTexEnvi(GL_TEXTURE_2D, GL_TEXTURE_ENV_MODE, GL_MODULATE);
   delete temp;
   return true;
}
