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

#include "../Graphics/ModelObject.h"
#include "ElevatorBase.h"

class Elevator;
class FloorBase;
class Animation;

class ElevatorMachine : public ElevatorBase, public ModelObject
{
public:
    enum ElevatorMachine_State { LMS_Idle = 0, LMS_Down = 1, LMS_Up = 2 };

private:
    ElevatorMachine_State mState; // Controls this things motion

protected:
    short mDirection;
    short mImageFrame;
    short mLastFrame;
    short mFirstFrame;
    Animation* mLifterAnimation;

public:
    // CTOR/DTOR
    ElevatorMachine(int x, int level, int width, Elevator* pElevator);
    virtual ~ElevatorMachine();

    // Implemantation
    void pos_calc();
    virtual void Update(float dt);
    virtual void Draw();
};

#endif //_ELEVATORMACHINE_H
