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

#ifndef _OFFICE_H
#define _OFFICE_H

#include <map>

#include "../Graphics/modelObject.h"
#include "floorBase.h"

class Animation;

enum office_state
{
   s_unoccupied_day,
   s_occupied_day
};

class Office : public FloorBase, public Gfx::ModelObject
{
private:
   office_state unoccupied_day (float dt);
   office_state occupied_day (float dt);
   std::map<office_state, Animation *> manimations;
   office_state mcurrent_state;
   int mcurrent_animation;

public:
   Office (int x, int level, Tower * TowerParent);

   void Update (float dt);
   void Draw ();
   void DrawFramework ();

   bool Save(TiXmlElement*);
};

#endif
