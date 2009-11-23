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

#include "../Types/String.h"

#include "Apartment.h"

using namespace Gfx;

//   apt_vacant,
//   apt_unoccupied_day,
//   apt_occupied_day,
//   apt_occupied_night,
//   apt_sleep_night

apartment_state Apartment::vacant (int tod)
{
   return apt_unoccupied_day;
}

apartment_state Apartment::unoccupied_day (int tod)
{
   if (tod>13*60+20)
      return apt_occupied_day;
   return apt_unoccupied_day;
}

apartment_state Apartment::occupied_day (int tod)
{
   if (tod>16*60)  // and people are home
      return apt_occupied_night;
   return apt_occupied_day;
}

apartment_state Apartment::occupied_night (int tod)
{
   if (tod>20*60+30)
      return apt_occupied_sleep;
   return apt_occupied_night;
}

apartment_state Apartment::occupied_sleep (int tod)
{
   if (tod < 10*60 && tod > 5*60+20)
      return apt_occupied_day;
   return apt_occupied_sleep;
}

Apartment::Apartment (int x, int level, Tower * TowerParent)
      :  mCurrentState (apt_vacant)
      ,  FloorBase (x, x + 72, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New apartment at " << mX << ", " << mY << " level " << mLevel << std::endl;
   manimations[apt_vacant] = new Animation (72, 36);
   manimations[apt_vacant]->AddFrame (image_man->GetTexture ("Apartment_empty_1.png", GL_RGBA), 1000);
   manimations[apt_vacant]->SetPosition (mX, mY);
   manimations[apt_occupied_day] = new Animation (72, 36);
   manimations[apt_occupied_day]->AddFrame (image_man->GetTexture ("Apartment_r_d_1.png", GL_RGBA), 1000);
   manimations[apt_occupied_day]->AddFrame (image_man->GetTexture ("Apartment_r_d_2.png", GL_RGBA), 1000);
   manimations[apt_occupied_day]->AddFrame (image_man->GetTexture ("Apartment_r_d_3.png", GL_RGBA), 1000);
   manimations[apt_occupied_day]->SetPosition (mX, mY);
   manimations[apt_occupied_night] = new Animation (72, 36);
   manimations[apt_occupied_night]->AddFrame (image_man->GetTexture ("Apartment_r_n_1.png", GL_RGBA), 1000);
   manimations[apt_occupied_night]->SetPosition (mX, mY);
   manimations[apt_unoccupied_day] = new Animation (72, 36);
   manimations[apt_unoccupied_day]->AddFrame (image_man->GetTexture ("Apartment_r_u_1.png", GL_RGBA), 1000);
   manimations[apt_unoccupied_day]->SetPosition (mX, mY);
   manimations[apt_occupied_sleep] = new Animation (72, 36);
   manimations[apt_occupied_sleep]->AddFrame (image_man->GetTexture ("Apartment_r_s_1.png", GL_RGBA), 1000);
   manimations[apt_occupied_sleep]->SetPosition (mX, mY);
}

void Apartment::Update (float dt, int tod)
{
   manimations[mCurrentState]->Update (dt);
   if( mOccupants < 0 )
   {
      mOccupants = 0;
   }

   switch (mCurrentState)
   {
   case apt_vacant:
      if (mOwner != NULL)
      {
         mCurrentState = unoccupied_day (tod);
      }
      break;

   case apt_unoccupied_day :
      if (mOwner == NULL)
      {
         mCurrentState = vacant (tod);
      }
      else
      {
         if( mOccupants > 0 )
            mCurrentState = occupied_day (tod);
      }
      break;
   case apt_occupied_day :
      mCurrentState = occupied_day (tod);
      break;

   case apt_occupied_night :
      mCurrentState = occupied_night (tod);
      break;

   case apt_occupied_sleep:
      mCurrentState = occupied_sleep (tod);
      break;
   }
}

void Apartment::Draw ()
{
   Render (manimations[mCurrentState]);
}

void Apartment::DrawFramework ()
{
   RenderFramework( manimations[mCurrentState], mID);
}

void Apartment::Save(SerializerBase& ser)
{
   ser.Add("type", "apartment");   // first tag
   FloorBase::Save(ser);
   ser.Add("state", ToString((mCurrentState == apt_occupied_day)?1:0).c_str()); // use the state engine get this property
   // if something goes bump, either deal with it or throw it
}

double Apartment::GetRent ()
{
   if (mOwner != NULL)
      return mRent;
   return 0;
}
