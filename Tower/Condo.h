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

// "I movin on up, to that delux apartment in the sky" The Jefferson's

#ifndef _CONDO_H
#define _CONDO_H
// base classes
#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

#include <map>

class FloorBase;
class Animation;

enum Condo_State {
    condo_vacant,
    condo_unoccupied_day,
    condo_occupied_day,
    condo_occupied_night,
    condo_occupied_sleep
};

class Condo : public FloorBase, public Gfx::ModelObject
{
private:
    std::map<Condo_State, Animation*> manimations;
    Condo_State mCurrentState;
    int mcurrent_animation;

public:
    Condo(int x, int level, Tower* TowerParent);
    static BaseType GetBaseType() { return BaseCondo; }
    std::string GetTypeName() const override { return "condo"; }

    virtual void Update(float dt, int tod);
    virtual void Draw();
    virtual void DrawFramework();
    virtual void Save(SerializerBase& ser);
    virtual BaseType GetType() { return BaseCondo; }

protected:
    Condo_State vacant(int dt);
    Condo_State unoccupied_day(int dt);
    Condo_State occupied_day(int dt);
    Condo_State occupied_night(int dt);
    Condo_State occupied_sleep(int dt); // running sandman functions
};

#endif // _CONDO_H
