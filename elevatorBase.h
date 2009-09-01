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

#ifndef _ELEVATORBASE_H
#define _ELEVATORBASE_H

class Elevator;

class ElevatorBase
{
protected:

   int mx;
   int my;
   short mLevel;
   Elevator* mpParent;


public:
   // CTOR/DTOR
   ElevatorBase(  int x, int level, Elevator* pElevator );
   virtual ~ElevatorBase( );

   // Implemantation
   void pos_calc ();
   virtual void Update (float dt) = 0; // pure
   virtual void Draw () = 0;
};

#endif //_ELEVATORBASE_H
