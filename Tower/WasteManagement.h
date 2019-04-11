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

#ifndef _WasteManagement_H
#define _WasteManagement_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class Animation;
class SerializerBase;

enum WasteManagement_state { WMS_Vacant, WMS_Occupied };
enum WasteManagement_mode { WMM_Night = 0, WMM_DayUnoccupied, WMM_DayOccupied };

class WasteManagement : public FloorBase, public Gfx::ModelObject
{
    std::map<WasteManagement_mode, AnimationBase*> manimations;
    WasteManagement_state mCurrentState; // vacant /occupied
    WasteManagement_mode mCurrentMode;   // day / night
    int mCurrentAnimation;
    int mPeopleInWasteManagement;
    int mEmployees;
    int mMaxPositions;
    int mWasteManagementState;
    int mWasteManagementNumner;

public:
    WasteManagement(int x, int level, Tower* TowerParent);
    static BaseType GetBaseType() { return BaseWasteManagement; }
    std::string GetTypeName() const override { return "wastemanagement"; }

    void Update(float dt, int tod);
    void Draw();
    void DrawFramework();
    virtual BaseType GetType() { return BaseWasteManagement; }

    void RemoveImages();
    void SetImages(int set);
    void Save(SerializerBase& ser);

    void PeopleInOut(int count);
    bool PeopleApply(); // get a job
    void SetWasteManagementNumber(int no) { mWasteManagementNumner = no; }
    int GetWasteManagementNumber() { return mWasteManagementNumner; }

private:
    void WasteManagementMode(int tod);
    void WasteManagementState();
};

#endif
