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

#ifndef _ELEVATORSHAFT_H
#define _ELEVATORSHAFT_H

#include "../Graphics/modelObject.h"
#include "elevatorBase.h"
class Elevator;
class FloorBase;
//class Camera;
class Tiler;

class ElevatorShaft : public ElevatorBase, public ModelObject
{
protected:

   short mTopLevel;
   short mBottomLevel; // if these are changed, update the tiler ShaftImages

   // moved from elevator and changed name to ShaftTiler to show it is a tiler object
   Tiler * mShaftTiler; // temporary to make a nice looking demo :]
   //Camera* mcam;

public:
   // CTOR/DTOR
   ElevatorShaft( int x, int topLevel, int bottomLevel, Elevator* pElevator );
   virtual ~ElevatorShaft( );

   // Implemantation
   virtual void Update (float dt);
   virtual void Draw ();
};

#endif //_ELEVATORSHAFT_H
