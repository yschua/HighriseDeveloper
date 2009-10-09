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

#include "Condo.h"

using namespace Gfx;

//   condo_vacant,
//   condo_unoccupied_day,
//   condo_occupied_day,
//   condo_occupied_night,
//   condo_sleep_night

Condo_State Condo::vacant (int tod)
{
   return condo_unoccupied_day;
}

Condo_State Condo::unoccupied_day (int tod)
{
   if (tod>13*60+20)
      return condo_occupied_day;
   return condo_unoccupied_day;
}

Condo_State Condo::occupied_day (int tod)
{
   if (tod>16*60)  // and people are home
      return condo_occupied_night;
   return condo_occupied_day;
}

Condo_State Condo::occupied_night (int tod)
{
   if (tod>20*60+30)
      return condo_occupied_sleep;
   return condo_occupied_night;
}

Condo_State Condo::occupied_sleep (int tod)
{
   if (tod < 10*60 && tod > 5*60+20)
      return condo_occupied_day;
   return condo_occupied_sleep;
}

Condo::Condo (int x, int level, Tower * TowerParent)
      :  mCurrentState (condo_vacant)
      ,  FloorBase (x, x + 126, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New Condo at " << mX << ", " << mY << " level " << mLevel << std::endl;
   manimations[condo_vacant] = new Animation (126, 36);
   manimations[condo_vacant]->AddFrame (image_man->GetTexture ("Condo_empty_1.png", GL_RGBA), 1000);
   manimations[condo_vacant]->SetPosition (mX, mY);
   //manimations[condo_occupied_day] = new Animation (72, 36);
   //manimations[condo_occupied_day]->AddFrame (image_man->GetTexture ("Condo_r_d_1.png", GL_RGBA), 1000);
   //manimations[condo_occupied_day]->AddFrame (image_man->GetTexture ("Condo_r_d_2.png", GL_RGBA), 1000);
   //manimations[condo_occupied_day]->AddFrame (image_man->GetTexture ("Condo_r_d_3.png", GL_RGBA), 1000);
   //manimations[condo_occupied_day]->SetPosition (mX, mY);
   //manimations[condo_occupied_night] = new Animation (72, 36);
   //manimations[condo_occupied_night]->AddFrame (image_man->GetTexture ("Condo_r_n_1.png", GL_RGBA), 1000);
   //manimations[condo_occupied_night]->SetPosition (mX, mY);
   //manimations[condo_unoccupied_day] = new Animation (72, 36);
   //manimations[condo_unoccupied_day]->AddFrame (image_man->GetTexture ("Condo_r_u_1.png", GL_RGBA), 1000);
   //manimations[condo_unoccupied_day]->SetPosition (mX, mY);
   //manimations[condo_occupied_sleep] = new Animation (72, 36);
   //manimations[condo_occupied_sleep]->AddFrame (image_man->GetTexture ("Condo_r_s_1.png", GL_RGBA), 1000);
   //manimations[condo_occupied_sleep]->SetPosition (mX, mY);
}

void Condo::Update (float dt, int tod)
{
   manimations[mCurrentState]->Update (dt);
   if( mOccupants < 0 )
   {
      mOccupants = 0;
   }

   switch (mCurrentState)
   {
   case condo_vacant:
      if (mOwner != NULL)
      {
         mCurrentState = unoccupied_day (tod);
      }
      break;

   case condo_unoccupied_day :
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
   case condo_occupied_day :
      mCurrentState = occupied_day (tod);
      break;

   case condo_occupied_night :
      mCurrentState = occupied_night (tod);
      break;

   case condo_occupied_sleep:
      mCurrentState = occupied_sleep (tod);
      break;
   }
}

void Condo::Draw ()
{
   Render (manimations[condo_vacant]);//mCurrentState]);
}

void Condo::DrawFramework ()
{
   RenderFramework( manimations[mCurrentState], mID);
}

void Condo::Save(SerializerBase& ser)
{
   ser.Add("type", "condo");   // first tag
   FloorBase::Save(ser);
   ser.Add("state", ToString((mCurrentState == condo_occupied_day)?1:0).c_str()); // use the state engine get this property
   // if something goes bump, either deal with it or throw it
}