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
class C_RouteBase;
class C_RouteVisitor;
class C_AnimationSingle;
class C_ElevatorMachine; // mover above
class C_ElevatorShaft;   // holds the tiler to show the shaft
class C_ElevatorPit;     // landing pit below
class C_Camera;
class C_Person;
class C_Tower;

#include "physics.h"

// The UI should read the FloorStops array and the range of floors.
// Then display all available floors and ticking those floors in the FloorStops array.
// The user will be able to untick levels to diable and tick levels to enable.
// Then the FloorStops array is reloaded with only floors that are ticked.
// This code and the routing agent can determine which elevators reach which levels
//  to determine what paths are available virtically through the tower.
// ButtonFlag is the direction a person wishes to travel to their destination.
// BUTTON_UP and BUTTON_DOWN are the bit flags.

#define BUTTON_UP 0x01
#define BUTTON_DOWN 0x02
#define DESINATION  0x04  // this is a destination level.

struct FloorStop
{
   short m_Level;
   char  m_ButtonFlag;
};

struct Rider
{
   C_Person* m_Person;
   short    m_DestLevel;
};

class C_Elevator : public C_Body, public C_RouteBase
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

   C_AnimationSingle* m_ElevatorImage;
   C_AnimationSingle* m_LiftPit;
   C_ElevatorMachine* m_LiftMachine;
   C_ElevatorShaft*   m_ElevatorShaft;

   Rider       m_Riders[16];
   FloorStop   m_Stops[32];

   //C_Tiler * m_ElevatorShaft; // temporary to make a nice looking demo :] Moved into shaft object.
   C_Camera* m_cam;
   // Controls this things motion
   int   m_X;
   int   m_Y;
   //short m_Level;
   short m_CurrentLevel;
   short m_Direction;
   short m_TopLevel;
   short m_BottomLevel;
   short m_Position;
   short m_IdleTime;
   short m_Offset;   // adjust for starting floor.
   // test code
   short m_StartRoute;
   short m_EndRoute;
   short m_End2;
   short m_RidersOnBoard;
   short m_FloorCount;

   LiftOps_State  m_LiftOperation;
   unsigned char  m_LiftStyle;

   C_Tower * m_TowerParent;

public:
   // CTOR/DTOR  Use create to make on
   C_Elevator( Lift_Styles style, int x, short BottLevel, short TopLevel, C_Tower * TowerParent );
   virtual ~C_Elevator();

   static C_Elevator* Create( Lift_Styles style, int x, short BottomLevel, short TopLevel, C_Tower * TowerParent );  // this is rejected for som reason

   // Implemantation
   void ClearStops();
   void Move( int x, int y );
   void Resize( int x, int y );
   void pos_calc ();
   void PosCalc ();
   void SetSetCallButton (int level, int dir);
   virtual void SetRoute( C_RouteVisitor* visitor );
   virtual void Update (float dt);
   virtual void Draw ();
};

#endif