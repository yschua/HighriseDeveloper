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

#ifndef _LEVEL_H
#define _LEVEL_H

#include "../Graphics/modelObject.h"
#include "floorBase.h"

class AnimationSingle;
class AnimationEmpty;
class FloorBase;
class Tower;
class Elevator;
class PersonQueue;

class Level : public Gfx::ModelObject
{
private:
   std::vector<FloorBase*> mFloorSpaces;
   std::list<PersonQueue*> mElevatorQueues;  // person queue for elevators that stop on this level
   Tower * mTowerParent;
   int  mID;

public:
   static const int mUnitSize;

protected:
   int   mLevel;
   int   mX;    // lower left origin.x
   int   mX2;   // x vector = width
   int   mY;    // lower left origin.y
               // y vector = height
   float mZ;     // face set to zero
               // z vector = depth but not implement until 3D
   AnimationSingle * nFireEscapeLeft;
   AnimationSingle * nFireEscapeRight;
   AnimationSingle * mEmptyFLoor;
   AnimationEmpty* mTheLevel;

protected:
   // Level open Space tracking grid (proto type stuff
   // Just using allocated simple byte array for easy debugging
   unsigned char*  mpFloorSpaceGrid;
   int   mFloorSpaceGridSize;
   bool  mFloorIsFull;        // Can't place any more objects
   bool  mNoEmptyFloorSpace;  // Skip the DrawEmptySpace function
public:
   bool  IsFloorFull()
   {
      return mFloorIsFull;
   }

   // Level tracking methods/functions
   void  ResizeFloorSpaceGrid();
   void  ScanFloorSpace(); // Marks the gird for what is in the space
   bool  IsSpaceEmpty( int x, int x2 ); // TestForEmptySpace...
   void  DrawEmptySpace();
   // End prototype code

public:
   // CTOR
   Level (int level, int x, int y, int x2, Tower * TowerParent);
   virtual ~Level ();

public:
   // decls
   typedef std::vector<FloorBase*>::iterator FloorIterType;
   typedef std::list<PersonQueue*>::iterator QueueIterType;

   // Properties
protected:
   inline std::vector<FloorBase*>& GetFloorSpaces()
   {
      return mFloorSpaces;
   }
   inline std::list<PersonQueue*>& GetPersonQueues()
   {
      return mElevatorQueues;
   }
public:
   inline int GetLevel () { return mLevel; }
   inline int GetID () { return mID; }
   inline int GetX () { return mX; }

   // Methods
   virtual void Update (float dt);
   virtual void Draw ();
   virtual void DrawFramework (bool LevelOnly);

   bool AddFloorSpace (FloorBase * floor);
   void SetFloorPositions( int x, int x2 );
   FloorBase* FindSpace (int x);
   PersonQueue* FindQueue (int elevator);
//   bool AddFloorSpace (FloorBase* pFS, int x, int x2 );
   bool TestForEmptySpace (int x, int x2 );
   void AddElevatorToQueue (Elevator* pElevator);  // set and remove the elevator stops
   void RemoveElevatorFromQueue (Elevator* pElevator);
};

#endif

