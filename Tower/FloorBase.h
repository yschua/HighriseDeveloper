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

#ifndef _FLOORBASE_H
#define _FLOORBASE_H

class Tower;
class Person;
class Level;
class TiXmlElement;
class SerializerBase;

enum BaseType
{
   BaseEmpty = 0,
   BaseGhostRoom,
   BaseResidence,
   BaseOffice,
   BaseRetail,
   BaseRestaurant,
   BaseHotel,
   BaseVenue,
   BaseService,
   BaseSecurity,
   BaseClinic,
   BaseRestroom,
   BaseWasteManagement,
   BaseStair,
   BaseElevator
};

class FloorBase
{
   friend class Level;  // allows level to own these spaces by being able to set protected variables.

protected:
   int mLevel;
   int mID;
   int mOccupants;
   Tower * mTowerParent;
   Person* mOwner;

//public:
   float mX;    // lower left origin.x
   float mX2;   // x vector = width
   float mY;    // lower left origin.y
   float mZ;
               // y vector = height
               // z vector = depth but not implement until 3D
//   int mx, mx2, my;
   static unsigned int NextID;   // all model objects will get one
public:
   // CTOR
   FloorBase (int x, int x2, int level, Tower * TowerParent);

   // Properties
   inline float GetX() { return mX; }
   inline float GetX2() { return mX2; }
   inline float GetY() { return mY; }
   inline float GetZ() {return mZ; }
   inline int   GetLevel() { return mLevel; }
   inline int   GetID () { return mID; }

   inline void SetX(float x) { mX = x; }
   inline void SetX2(float x) { mX2 = x; }
   inline void SetY(float y) { mY = y; }

   // Methods
   virtual void Update (float dt, int tod);
   virtual void Draw ();
   virtual void DrawFramework () { }
   virtual BaseType GetType () { return BaseEmpty; }

   void SetOwner (Person* pPerson);
   bool IsVacant () { return (mOwner==NULL); }

   virtual void Save(SerializerBase& ser);// iXmlElement* pnParent)

   static int GetNextID();
};

#endif
