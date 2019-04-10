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

#ifndef _GHOSTROOM_H
#define _GHOSTROOM_H

#include "../Root/Physics.h"
#include "../Graphics/Animation.h"
#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class AnimationSingle;
class SerializerBase;
class Tower;

// simple room outline used to track the mouse and assist with placment

enum Ghost_State
{
   GS_Invalid,
   GS_Valid
};

class GhostRoom : public FloorBase, public Gfx::ModelObject
{
   Ghost_State    mCurrentState;// vacant /occupied/ day / night
   AnimationShape mBase;
   BaseType       mShownType;

   int   mWidthUnits;
   int   mOffsetUnits;

public:
   GhostRoom (int x, int level);
   static BaseType GetBaseType() { return BaseEmpty; }
   std::string GetTypeName() const override { return "placementCursor"; }

   void Update (Tower* pTower);
   void Draw ();
   void DrawFramework () {};
   virtual BaseType GetType () { return BaseGhostRoom; }
   void SetShownType (BaseType bt) { mShownType = bt; }
   void SetState( Ghost_State gs );
   void Move (Vector3f& point);
   void SetWidth( int units);

//   void RemoveImages();
//   void SetImages (int set);
//   void Save(SerializerBase& ser) {};
//

private:
   void GhostState(int tod);
};

#endif //_GHOSTROOM_H
