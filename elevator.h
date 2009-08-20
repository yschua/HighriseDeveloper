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

class C_LiftMachine; // mover above
class C_LiftPit;     // landing pit below
class C_Body;

class C_Elevator : public C_Body
{
public:

   enum LiftOps_State : short
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

   enum Lift_Styles : short
   {
      LS_Small = 0,
      LS_Standard,
      LS_HighCapacity,
      LS_Freight,
      LS_Express
   };

protected:
   // Controls this things motion
   int   m_X;
   short m_Level;
   short m_CurrentLevel;
   short m_Direction;
   LiftOps_State  m_LiftOperation;
   Lift_Styles    m_LiftStyle;

   // CTOR/DTOR  Use create to make on
   C_Elevator( Lift_Styles style, int x, int level );
   virtual ~C_Elevator();
public:
   C_Elevator* Create( Lift_Styles style, int x, int level );

   // Implemantation
   void Move( int x, int y );
   void Resize( int x, int y );
   virtual void update (float dt);
   virtual void draw ();
};

#endif
