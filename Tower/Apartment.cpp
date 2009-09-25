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
#include <map>
#include <vector>
#include "../Root/Physics.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "../Root/SerializerBase.h"

#include "FloorBase.h"
#include "../Types/String.h"

#include "Apartment.h"

using namespace Gfx;

//   apt_unoccupied_day,
//   apt_occupied_day,
//   apt_occupied_night,
//   apt_sleep_night

apartment_state
Apartment::unoccupied_day (float dt)
{
   if (rand () % 50 == 3)
      return apt_occupied_day;
   return apt_unoccupied_day;
}

apartment_state
Apartment::occupied_day (float dt)
{
   if (rand () % 50 == 3)
      return apt_unoccupied_day;
   return apt_occupied_day;
}

apartment_state
Apartment::occupied_night (float dt)
{
   return apt_occupied_sleep;
}

apartment_state
Apartment::occupied_sleep (float dt)
{
   return apt_occupied_day;
}

Apartment::Apartment (int x, int level, Tower * TowerParent)
      :  mcurrent_state (apt_occupied_day)
      ,  FloorBase (x, x + 72, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New apartment at " << mX << ", " << mY << " level " << mLevel << std::endl;
   manimations[apt_occupied_day] = new Animation (72, 36);
   manimations[apt_occupied_day]->AddFrame (image_man->GetTexture ("apartment_r_d_1.png", GL_RGBA), 1000);
   manimations[apt_occupied_day]->AddFrame (image_man->GetTexture ("apartment_r_n_1.png", GL_RGBA), 1000);
   manimations[apt_occupied_day]->SetPosition (mX, mY);
   manimations[apt_unoccupied_day] = new Animation (72, 36);
   manimations[apt_unoccupied_day]->AddFrame (image_man->GetTexture ("apartment_r_s_1.png", GL_RGBA), 1000);
   manimations[apt_unoccupied_day]->SetPosition (mX, mY);
}

void
Apartment::Update (float dt)
{
   manimations[mcurrent_state]->Update (dt);
   apartment_state new_state;
   switch (mcurrent_state)
   {
      case apt_unoccupied_day :
         new_state = unoccupied_day (dt);
         break;
      case apt_occupied_day :
         new_state = occupied_day (dt);
         break;
   }
   mcurrent_state = new_state;
}

void Apartment::Draw ()
{
   Render (manimations[mcurrent_state]);
}

void Apartment::DrawFramework ()
{
   RenderFramework( manimations[mcurrent_state], mID);
}

void Apartment::Save(SerializerBase& ser)
{
   ser.Add("type", "apartment");   // first tag
   FloorBase::Save(ser);
   ser.Add("state", ToString((mcurrent_state == apt_occupied_day)?1:0).c_str()); // use the state engine get this property
   // if something goes bump, either deal with it or throw it
}