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

#ifndef _SERVICECENTER_H
#define _SERVICECENTER_H

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

#include <map>

class Animation;
class SerializerBase;

enum office_state { SS_Vacant, SS_Occupied };
enum office_mode { SM_Night = 0, SM_DayUnoccupied, SM_DayOccupied };

class ServiceCenter : public FloorBase, public Gfx::ModelObject
{
    std::map<office_mode, AnimationBase*> manimations;
    office_state mCurrentState; // vacant /occupied
    office_mode mCurrentMode;   // day / night
    int mCurrentAnimation;
    int mPeopleInService;
    int mEmployees;
    int mMaxPositions;
    int mServiceNumner;

public:
    ServiceCenter(int x, int level, Tower* TowerParent);

    void Update(float dt, int tod);
    void Draw();
    void DrawFramework();
    virtual BaseType GetType() { return BaseOffice; }

    void RemoveImages();
    void SetImages(int set);
    void Save(SerializerBase& ser);

    void PeopleInOut(int count);
    bool PeopleApply(); // get a job
    void SetServiceNumber(int no) { mServiceNumner = no; }
    int GetServiceNumber() { return mServiceNumner; }

private:
    void ServiceMode(int tod);
    void ServiceState();
};

#endif //_SERVICECENTER_H
