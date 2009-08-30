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

C_ImageManager * C_ImageManager::m_instance = NULL;

C_ImageManager::C_ImageManager ()
      :   m_path_prefix ("data/")
{
}

C_ImageManager *
C_ImageManager::GetInstance ()
{
   if (m_instance == NULL)
   {
      m_instance = new C_ImageManager ();
   }
   return m_instance;
}

void
C_ImageManager::set_path (const std::string & prefix)
{
   m_path_prefix = prefix;
}

sf::Image *
C_ImageManager::GetImg (const std::string & name)
{
   if (m_images[name] == NULL)
   {
      sf::Image * temp;
      temp = new sf::Image;
      std::cout << "Loading file " << m_path_prefix + name << std::endl;
      temp->LoadFromFile (m_path_prefix + name);
      m_images[name] = temp;
      return temp;
   }
   std::cout << "Using preloaded file " << name << std::endl;
   return m_images[name];
}

int
C_ImageManager::preload_image (const std::string & name)
{
   if (m_images[name] == NULL)
   {
      sf::Image * temp;
      temp = new sf::Image;
      temp->LoadFromFile (m_path_prefix + name);
      m_images[name] = temp;
      return 1;
   }
   return 0;
}
