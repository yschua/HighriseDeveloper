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
#include "../Root/SerializerBase.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "FloorBase.h"
#include "../Types/String.h"

#include "HotelRoom.h"

using namespace Gfx;

namespace TowerObjects
{
   // use the XML serializer to replace this
   // 
   const char* HotelImagesU[] =
   {
      "Hotel_u_n.png",
      "Hotel_u_d.png",
      "Hotel_u_0.png"
   };
   const char* HotelImagesS[] =
   {
      "Hotel_S_u.png",
      "Hotel_S_n.png",
      "Hotel_S_d_0.png",
      "Hotel_S_d_1.png",
      "Hotel_S_d_2.png",
      "Hotel_S_d_3.png",
      "Hotel_S_d_4.png",
      "Hotel_S_d_5.png"
   };
   const char* HotelImages6[] =
   {
      "Hotel_6_n.png",
      "Hotel_6_d_0.png",
      "Hotel_6_d_1.png",
      "Hotel_6_d_2.png"
   };
   const char* HotelImages7[] =
   {
      "Hotel_7_n.png",
      "Hotel_7_d_0.png",
      "Hotel_7_d_1.png",
      "Hotel_7_d_2.png",
      "Hotel_7_d_4.png",
      "Hotel_7_d_3.png",
      "Hotel_7_d_5.png"
   };
   struct RetailImage
   {
      const char** Images;
      int count;
   };
   RetailImage HotelImages[] =
   {
      { HotelImagesS, 3 }
      //{ HotelImages0, 7 },
      //{ HotelImages6, 4 },
      //{ HotelImages7, 7 }
   };
   const int TotalSets = 1;
}

using namespace TowerObjects;

HotelRoom::HotelRoom (int x, int level, Tower * TowerParent)
      :  mCurrentState (HS_Vacant)
      ,  FloorBase (x, x + 72, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New Retail at " << mX << ", " << mY << " level " << mLevel << std::endl;
   mOccupants = 0;
   SetImages (0);
}

void HotelRoom::HotelState (int tod)
{
   if (mOccupants > 0)  // some people are in the room
   {
      if (tod >= 14*60 || tod < 6*60)
      {
         mCurrentState = HS_OccupiedNight;
      }
      else
      {
         mCurrentState = HS_OccupiedDay;
      }
   }
   else if (tod > 8*60 && tod < 20*60)
   {
      mCurrentState = HS_UnoccupiedDay;
   }
   else if (tod >= 14*60 || tod < 6*60)
   {
      mCurrentState = HS_UnoccupiedNight;
   }
}

void HotelRoom::SetImages (int set)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   RetailImage& oi = HotelImages [set];
//HS_OccupiedNight,
//HS_OccupiedSleep

   manimations[HS_UnoccupiedDay] = new AnimationSingle (image_man->GetTexture (oi.Images[0], GL_RGBA), 72, 36);
   manimations[HS_UnoccupiedDay]->SetPosition (mX, mY);
   manimations[HS_UnoccupiedNight] = new AnimationSingle (image_man->GetTexture (oi.Images[1], GL_RGBA), 72, 36);
   manimations[HS_UnoccupiedNight]->SetPosition (mX, mY);
   Animation* pAn = new Animation (72,36);
   manimations[HS_OccupiedDay] = pAn;
   for (int idx = 2; idx < oi.count; ++idx )
   {
      pAn->AddFrame (image_man->GetTexture (oi.Images[idx], GL_RGBA), (float)(1500+rand()%120));
      pAn->SetPosition (mX, mY);
   }
}

void HotelRoom::Update (float dt, int tod)
{
   HotelState (tod);
   manimations[mCurrentState]->Update (dt);
}

void HotelRoom::Draw ()
{
   Render (manimations[mCurrentState]);
}

void HotelRoom::DrawFramework ()
{
   RenderFramework( manimations[mCurrentState], mID);
}

void HotelRoom::Save(SerializerBase& ser)
{
   ser.Add("type", "hotelroom");   // first tag
   FloorBase::Save(ser);
   ser.Add("state", mCurrentState );
   // if something goes bump, either deal with it or throw it
}

void HotelRoom::PeopleInOut( int count )
{
   mOccupants += count;
   if (mOccupants < 0 )
   {
      mOccupants = 0;
   }
}
