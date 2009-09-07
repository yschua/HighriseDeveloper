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

// "I movin on up, to that delux apartment in the sky" The Jefferson's

#ifndef _APARTMENT_H
#define _APARTMENT_H
#include "../Graphics/modelObject.h"

class FloorBase;

enum apartment_state
{
   apt_unoccupied_day,
   apt_occupied_day,
   apt_occupied_night,
   apt_occupied_sleep
};

class Apartment : public FloorBase, public Gfx::ModelObject
{
private:
   apartment_state unoccupied_day (float dt);
   apartment_state occupied_day (float dt);
   apartment_state occupied_night (float dt);
   apartment_state occupied_sleep (float dt);       // running sandman functions
   std::map<apartment_state, Animation *> manimations;
   apartment_state mcurrent_state;
   int mcurrent_animation;
//   Camera * mCam;

public:
   virtual void Update (float dt);
   virtual void Draw ();
   Apartment (int x, int level, Tower * TowerParent);
};

#endif   // _APARTMENT_H
