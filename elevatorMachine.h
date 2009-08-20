/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Foobar is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _ELEVATORMACHINE_H
#define _ELEVATORMACHINE_H

class C_Elevator;
class C_FloorBase;

class C_ElevatorMachine : public C_ElevatorBase
{
public:
   enum ElevatorMachine_State : short
   {
      LMS_Idle = 0,
      LMS_Down = 1,
      LMS_Up = 2
   };
private:
   ElevatorMachine_State m_State; // Controls this things motion

protected:
   short m_Direction;
   short m_ImageFrame;
   short m_LastFrame;
   short m_FirstFrame;
    std::map<short, C_Animation *> m_animations;

public:
   // CTOR/DTOR
   C_ElevatorMachine( int x, int level, C_Elevator* pElevator );
   virtual ~C_ElevatorMachine();

   // Implemantation
   virtual void update (float dt);
   virtual void draw ();
};

#endif //_ELEVATORMACHINE_H
