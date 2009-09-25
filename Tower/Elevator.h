/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ELEVATOR_H
#define _ELEVATOR_H

// Elevator class, this is the elevator carrige.
// Handles the car movement and operations.
// Elevator is the overhead cable machine.
// LiftShaft is the evelator shaft.
// ListPit is the crash landing pit below in the event of a break failure.
// This three parts build the shaft for the elevator/lift to run in.

// these decls allow inclusion of this header without the need to load these class headers.
//class RouteBase;
class RouteVisitor;
class AnimationSingle;
class ElevatorMachine; // mover above
class ElevatorShaft;   // holds the tiler to show the shaft
class ElevatorPit;     // landing pit below
class Person;
class Tower;
class SerializerBase;

#include "../Physics.h"
#include "RouteBase.h"
#include "../Graphics/ModelObject.h"

// Setting elevator levels serviced.
//
// The UI should read the FloorStops array and the range of floors.
// Then display all available floors and ticking those floors in the FloorStops array.
// The user will be able to untick levels to diable and tick levels to enable.
// Then the FloorStops array is reloaded with only floors that are ticked.

// Other
//
// This code and the routing agent can determine which elevators reach which levels
//  to determine what paths are available virtically through the tower.
// ButtonFlag is the direction a person wishes to travel to their destination.
// BUTTON_UP and BUTTON_DOWN are the bit flags.

#define BUTTON_UP 0x01     // this is a call to floor
#define BUTTON_DOWN 0x02   // this is a call to floor
#define DESINATION  0x04   // this is a level destination

struct FloorStop
{
   short mLevel;
   char  mButtonFlag;
};

struct Rider
{
   Person* mPerson;
   short    mDestLevel;
};

class Elevator : public Body, public RouteBase, public Gfx::ModelObject // Quad morphic
{
public:

   enum LiftOps_State
   {
      LOS_EStop = 0,
      LOS_FireMode,
      LOS_Waiting,
      LOS_WxpressUp,
      LOS_ExpressDown,
      LOS_NearestCall,
      LOS_FullService,  // Normal any call operation.
      LOS_ReturnToHome, // Send car to set home floor
   };

   enum Lift_Styles
   {
      LS_Small = 0,
      LS_Standard,
      LS_HighCapacity,
      LS_Freight,
      LS_Express
   };

protected:
   static int gElevatorsNumber;
   static const int mStandingPositions[];

   AnimationSingle* mElevatorImage;
   AnimationSingle* mLiftPit;
   ElevatorMachine* mLiftMachine;
   ElevatorShaft*   mElevatorShaft;

   Rider       mRiders[16];
   FloorStop   mStops[32];

   // Controls this things motion
   int   mX;
   int   mY;
   float mZ;

   int   mNumber;    // number of this lift
   short mCurrentLevel;
   short mDirection;
   short mTopLevel;
   short mBottomLevel;
   short mPosition;
   short mIdleTime;
   short mOffset;   // adjust for starting floor.

   short mStartRoute;
   short mEndRoute;
   short mEnd2;
   short mRidersOnBoard;
   short mFloorCount;
   short mMaxCap;

   LiftOps_State  mLiftOperation;
   unsigned char  mLiftStyle;

   Tower * mTowerParent;

public:
   // CTOR/DTOR  Use create to make on
   Elevator( Lift_Styles style, int x, short BottLevel, short TopLevel, Tower * TowerParent );
   Elevator( SerializerBase& ser, short TopLevel, Tower * TowerParent );
   virtual ~Elevator();

   static Elevator* Create( Lift_Styles style, int x, short BottomLevel, short TopLevel, Tower * TowerParent );  // this is rejected for som reason

   // Properties
   inline int  GetNumber() { return mNumber; }

   // Methods
   void ClearStops();
   void Move( int x, int y );
   void Resize( int x, int y );

protected:
   void PosCalc ();
   virtual void SetCallButton (RouteVisitor* visitor);
   virtual void SetFloorButton (RouteVisitor* visitor);
   int  LoadPerson(Person* person, int destLevel); // returns space remaining
   void NextCallButton ();
   void Motion ();
   void SetDestination (int level);
public:

   virtual void Update (float dt);
   virtual void Draw ();
   virtual void DrawFramework () { } // later we do lifts to
   
   void Save( SerializerBase& ser );
};

#endif