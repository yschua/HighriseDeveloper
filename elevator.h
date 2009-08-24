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
class C_Body;
class C_Camera;

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
   // test code
   short m_StartRoute;
   short m_EndRoute;
   short m_End2;
   LiftOps_State  m_LiftOperation;
   unsigned char  m_LiftStyle;

public:
   // CTOR/DTOR  Use create to make on
   C_Elevator( Lift_Styles style, int x, short BottLevel, short TopLevel );
   virtual ~C_Elevator();

   static C_Elevator* Create( Lift_Styles style, int x, short BottomLevel, short TopLevel );  // this is rejected for som reason

   // Implemantation
   void Move( int x, int y );
   void Resize( int x, int y );
   void pos_calc ();
   virtual void setRoute( C_RouteVisitor* visitor );
   virtual void update (float dt);
   virtual void draw ();
};

#endif
