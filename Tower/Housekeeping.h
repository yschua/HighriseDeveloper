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

#ifndef _HOUSEKEEPING_H
#define _HOUSEKEEPING_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class Animation;
class SerializerBase;

enum service_state
{
   SS_Vacant,
   SS_Occupied
};
enum service_mode
{
   SM_Night = 0, 
   SM_DayUnoccupied,
   SM_DayOccupied
};

class Housekeeping : public FloorBase, public Gfx::ModelObject
{
   std::map<service_mode, AnimationBase*> manimations;
   service_state mCurrentState;// vacant /occupied
   service_mode  mCurrentMode; // day / night
   int mCurrentAnimation;
   int mPeopleInService;
   int mEmployees;
   int mMaxPositions;
   int mServiceNumner;

public:
   Housekeeping (int x, int level, Tower * TowerParent);
   static BaseType GetBaseType() { return BaseHousekeeping; }
   std::string GetTypeName() const override { return "housekeeping"; }

   void Update (float dt, int tod);
   void Draw ();
   void DrawFramework ();
   virtual BaseType GetType () { return BaseService; }

   void RemoveImages();
   void SetImages (int set);
   void Save(SerializerBase& ser);

   void PeopleInOut( int count );
   bool PeopleApply( );    // get a job
   void SetServiceNumber(int no) { mServiceNumner = no; }
   int  GetServiceNumber() { return mServiceNumner; }

private:
   void ServiceMode (int tod);
   void ServiceState();
};

#endif //_HOUSEKEEPING_H
