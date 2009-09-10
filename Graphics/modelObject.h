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

// This class is a graphics implementation object that all modeled "Tower" objects are derived from.

#ifndef _MODELOBJECT_H
#define _MODELOBJECT_H

class Body;    // Main body of physics component
class Tiler;

namespace Gfx
{

   class ModelObject
   {

   public:
      ModelObject ();

      virtual void Draw() = 0;
   protected:
      void Render(Body* pBody);  // draw method replacement, drawing now happens on the GPU side for us
      void Render(Tiler* pTiler);  // draw method replacement, drawing now happens on the GPU side for us

   };
}
#endif // _MODELOBJECT_H