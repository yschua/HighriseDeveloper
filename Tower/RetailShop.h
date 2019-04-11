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

#ifndef _RETAILSHOP_H
#define _RETAILSHOP_H

#include <map>

#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class Animation;
class SerializerBase;

enum RetailShop_state { RS_Vacant, RS_Occupied };
enum RetailShop_mode { RM_Night = 0, RM_DayUnoccupied, RM_DayOccupied };

class RetailShop : public FloorBase, public Gfx::ModelObject
{
    std::map<RetailShop_mode, AnimationBase*> manimations;
    RetailShop_state mCurrentState; // vacant /occupied
    RetailShop_mode mCurrentMode;   // day / night
    int mCurrentAnimation;
    int mPeopleInShop;
    int mEmployees;
    int mMaxPositions;
    int mRetailShopStyle; // RetailShops, boardrooms, data centers, phone banks, etc
    int mRetailShopNumner;

public:
    RetailShop(int x, int level, Tower* TowerParent);
    static BaseType GetBaseType() { return BaseRetail; }
    std::string GetTypeName() const override { return "retailshop"; }

    void Update(float dt, int tod);
    void Draw();
    void DrawFramework();
    virtual BaseType GetType() { return BaseRetail; }

    void RemoveImages();
    void SetImages(int set);
    void Save(SerializerBase& ser);

    void PeopleInOut(int count);
    bool PeopleApply(); // get a job
    void SetRetailShopNumber(int no) { mRetailShopNumner = no; }
    int GetRetailShopNumber() { return mRetailShopNumner; }

private:
    void RetailShopMode(int tod);
    void RetailShopState();
};

#endif //_RETAILSHOP_H
