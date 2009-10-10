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

#ifndef _HOTEL_H
#define _HOTEL_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class Animation;
class SerializerBase;

enum Hotel_State
{
   HS_Vacant,
   HS_UnoccupiedDay,
   HS_UnoccupiedNight,
   HS_OccupiedDay,
   HS_OccupiedNight,
   HS_OccupiedSleep
};

class HotelRoom : public FloorBase, public Gfx::ModelObject
{
   std::map<Hotel_State, AnimationBase*> manimations;
   Hotel_State mCurrentState;// vacant /occupied/ day / night
   int mCurrentAnimation;
   int mOccupants;
   int mRoomStyle; // Regular, Double, King, Suite
   int mHotelNumner;
   int mWidth;

public:
   HotelRoom (int x, int level, Tower * TowerParent);
   static BaseType GetBaseType() { return BaseHotel; }
   static const char* GetTypeString() { return "hotelRoom"; }

   void Update (float dt, int tod);
   void Draw ();
   void DrawFramework ();
   virtual BaseType GetType () { return BaseHotel; }

   void RemoveImages();
   void SetImages (int set);
   void Save(SerializerBase& ser);

   void PeopleInOut( int count );
   void SetHotelNumber(int no) { mHotelNumner = no; }
   int  GetHotelNumber() { return mHotelNumner; }

private:
   void HotelState(int tod);
};

#endif //_HOTEL_H
