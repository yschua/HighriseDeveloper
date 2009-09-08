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

#ifndef _BACKGROUND_H
#define _BACKGROUND_H

#include "Graphics/modelObject.h"
class AnimationSingle;
class Tiler;

class Background : public Gfx::ModelObject
{
private:
   AnimationSingle* mBackImage;
   Tiler * mBackBuildings;
   Tiler * mBackGround;
//   Camera * cam;

public:
   void Draw ();
   Background (float width, float height);

};

#endif //_BACKGROUND_H
