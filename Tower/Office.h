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

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class Animation;
class SerializerBase;

enum office_state
{
   OS_Vacant,
   OS_Occupied
};
enum office_mode
{
   OM_Night = 0,
   OM_DayUnoccupied,
   OM_DayOccupied
};

class Office : public FloorBase, public Gfx::ModelObject
{
   std::map<office_mode, AnimationBase*> manimations;
   office_state mCurrentState;// vacant /occupied
   office_mode  mCurrentMode; // day / night
   int mCurrentAnimation;
   int mPeopleInOffice;
   int mEmployees;
   int mMaxPositions;
   int mOfficeStyle; // Offices, boardrooms, data centers, phone banks, etc
   int mOfficeNumner;

public:
   Office (int x, int level, Tower * TowerParent);
   static BaseType GetBaseType() { return BaseOffice; }
   static const char* GetTypeString() { return "office"; }

   void Update (float dt, int tod);
   void Draw ();
   void DrawFramework ();
   virtual BaseType GetType () { return BaseOffice; }
   virtual double GetRent ();

   void RemoveImages();
   void SetImages (int set);
   void Save(SerializerBase& ser);

   void PeopleInOut( int count );
   bool PeopleApply( );    // get a job
   void SetOfficeNumber(int no) { mOfficeNumner = no; }
   int  GetOfficeNumber() { return mOfficeNumner; }

   static int mWidth;
   static int mHeight;
private:
   void OfficeMode (int tod);
   void OfficeState();
};

#endif
