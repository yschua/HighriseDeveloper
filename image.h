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

#ifndef _IMAGE_H
#define _IMAGE_H

class C_ImageManager
{
private:
   std::string m_path_prefix;
   std::map<std::string, sf::Image *> m_images;
   static C_ImageManager * m_instance;
   C_ImageManager ();

public:
   static C_ImageManager * GetInstance ();
   static C_ImageManager* i() { return GetInstance(); };
   sf::Image * GetImg (const std::string & name);
   int preload_image (const std::string & name);
   void set_path (const std::string & prefix);
};

#endif
