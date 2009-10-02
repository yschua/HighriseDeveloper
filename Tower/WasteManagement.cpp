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

#include "WasteManagement.h"

using namespace Gfx;

namespace TowerObjects
{
   // use the XML serializer to replace this
   // 
   const char* WasteMgtImages0[] =
   {
      "WasteMgt_0_n.png",
      "WasteMgt_0_d_0.png",
      "WasteMgt_0_d_1.png",
      "WasteMgt_0_d_2.png",
      "WasteMgt_0_d_3.png",
      "WasteMgt_0_d_4.png",
      "WasteMgt_0_d_5.png"
   };
   struct WasteMgtImage
   {
      const char** Images;
      int count;
   };
   WasteMgtImage WasteMgtImages[] =
   {
      { WasteMgtImages0, 7 }
      //{ WasteMgtImagesU, 3 },
      //{ WasteMgtImages6, 4 },
      //{ WasteMgtImages7, 7 }
   };
   const int TotalSets = 1;
}

using namespace TowerObjects;

WasteManagement::WasteManagement (int x, int level, Tower * TowerParent)
      :  mCurrentState (WMS_Vacant)
      ,  mCurrentMode (WMM_Night)
      ,  FloorBase (x, x + 72, level, TowerParent)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   std::cout << "New WasteMgt at " << mX << ", " << mY << " level " << mLevel << std::endl;
   mPeopleInWasteManagement = 0;
   mEmployees = 0;
   mMaxPositions = rand() % 6 + 2;
   SetImages (0);
}

void WasteManagement::WasteManagementMode (int tod)
{
   if (mPeopleInWasteManagement > 0)  // some people are at work
   {
      mCurrentMode = WMM_DayOccupied;
   }
   else if (tod > 8*60 && tod < 16*60)
   {
      mCurrentMode = WMM_DayUnoccupied;
   }
   else
   {
      mCurrentMode = WMM_Night;
   }
}

void WasteManagement::WasteManagementState()
{
   if ( mCurrentState == WMS_Vacant && mPeopleInWasteManagement > 0 )  // need to check for rent paid
   {
      int set = 0;// + rand() % (TotalSets-1);
      RemoveImages();
      SetImages(set);
      mCurrentState = WMS_Occupied;
   }
}

void WasteManagement::RemoveImages()
{
   manimations[WMM_Night]->ClearFrames();
   manimations[WMM_DayUnoccupied]->ClearFrames();
   manimations[WMM_DayOccupied]->ClearFrames();
}

void WasteManagement::SetImages (int set)
{
   ImageManager * image_man = ImageManager::GetInstance ();
   WasteMgtImage& oi = WasteMgtImages [set];
   manimations[WMM_Night] = new AnimationSingle (image_man->GetTexture (oi.Images[0], GL_RGBA), 72, 36);
   manimations[WMM_Night]->SetPosition (mX, mY);
   manimations[WMM_DayUnoccupied] = new AnimationSingle (image_man->GetTexture (oi.Images[1], GL_RGBA), 72, 36);
   manimations[WMM_DayUnoccupied]->SetPosition (mX, mY);
   Animation* pAn = new Animation (72,36);
   manimations[WMM_DayOccupied] = pAn;
   for (int idx = 2; idx < oi.count; ++idx )
   {
      pAn->AddFrame (image_man->GetTexture (oi.Images[idx], GL_RGBA), (float)(1500+rand()%120));
      pAn->SetPosition (mX, mY);
   }
}

void WasteManagement::Update (float dt, int tod)
{
   WasteManagementMode (tod);
   manimations[mCurrentMode]->Update (dt);
}

void WasteManagement::Draw ()
{
   Render (manimations[mCurrentMode]);
}

void WasteManagement::DrawFramework ()
{
   RenderFramework( manimations[mCurrentMode], mID);
}

void WasteManagement::Save(SerializerBase& ser)
{
   ser.Add("type", "wastemgt");   // first tag
   FloorBase::Save(ser);
   ser.Add("state", ToString((mCurrentState == WMS_Occupied)?1:0).c_str());
   ser.Add("mode", mCurrentMode );
   // if something goes bump, either deal with it or throw it
}

void WasteManagement::PeopleInOut( int count )
{
   mPeopleInWasteManagement += count;
   if (mPeopleInWasteManagement < 0 )
   {
      mPeopleInWasteManagement = 0;
   }
   WasteManagementState();
}

bool WasteManagement::PeopleApply( )
{
   if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
   {
      mEmployees++;
      return true;
   }
   return false;
}