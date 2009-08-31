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

// Pit at the bottom of the shaft with crash landing buffers.

#ifndef _ELEVATORPIT_H
#define _ELEVATORPIT_H

#include "elevatorBase.h"

class C_Elevator;
class C_ElevatorBase;

class C_ElevatorPit : public C_ElevatorBase
{
protected:
//   C_AnimationSingle m_animations;


public:
   // CTOR/DTOR
   C_ElevatorPit(int x, int level, C_Elevator* pElevator );
   virtual ~C_ElevatorPit();

   // Implemantation
   virtual void Update (float dt);
   virtual void Draw ();
};

#endif //_ELEVATORPIT_H
