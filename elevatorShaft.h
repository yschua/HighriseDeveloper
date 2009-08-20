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

#ifndef _ELEVATORSHAFT_H
#define _ELEVATORSHAFT_H

class C_Elevator;
class C_FloorBase;

class C_ElevatorShaft : public C_ElevatorBase
{
protected:

   int m_X;
   short m_Level;

public:
   // CTOR/DTOR
   C_ElevatorShaft( int x, int level, C_Elevator* pElevator );
   virtual ~C_ElevatorShaft( );

   // Implemantation
   virtual void update (float dt);
   virtual void draw ();
};

#endif //_ELEVATORSHAFT_H
