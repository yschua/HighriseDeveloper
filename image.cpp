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
using namespace Gfx;

namespace Gfx {

Gfx::ImageManager * ImageManager::minstance = NULL;

ImageManager::ImageManager ()
:   mpath_prefix ("data/")
{
}

ImageManager *
ImageManager::GetInstance ()
{
   if (minstance == NULL)
   {
      minstance = new ImageManager ();
   }
   return minstance;
}

void
ImageManager::set_path (const std::string & prefix)
{
   mpath_prefix = prefix;
}

sf::Image *
ImageManager::GetImg (const std::string & name)
{
   if (mimages[name] == NULL)
   {
      sf::Image * temp;
      temp = new sf::Image;
      std::cout << "Loading file " << mpath_prefix + name << std::endl;
      temp->LoadFromFile (mpath_prefix + name);
      mimages[name] = temp;
      return temp;
   }
   std::cout << "Using preloaded file " << name << std::endl;
   return mimages[name];
}

int
ImageManager::preload_image (const std::string & name)
{
   if (mimages[name] == NULL)
   {
      sf::Image * temp;
      temp = new sf::Image;
      temp->LoadFromFile (mpath_prefix + name);
      mimages[name] = temp;
      return 1;
   }
   return 0;
}

   sf::Image* GetImage(const std::string& Key) {
      return ImageManager::GetInstance()->GetImg(Key);
   }
}
