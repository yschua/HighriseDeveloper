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

#pragma once
#ifndef _APARTMENT_H
#define _APARTMENT_H
// base classes
#include "../Graphics/ModelObject.h"
#include "FloorBase.h"

class FloorBase;

enum apartment_state {
    apt_vacant,
    apt_unoccupied_day,
    apt_occupied_day,
    apt_occupied_night,
    apt_occupied_sleep
};

class Apartment : public FloorBase, public Gfx::ModelObject
{
private:
    apartment_state vacant(int dt);
    apartment_state unoccupied_day(int dt);
    apartment_state occupied_day(int dt);
    apartment_state occupied_night(int dt);
    apartment_state occupied_sleep(int dt); // running sandman functions
    std::map<apartment_state, Animation*> manimations;
    apartment_state mCurrentState;
    int mcurrent_animation;

public:
    Apartment(int x, int level, Tower* TowerParent);

    static BaseType GetBaseType() { return BaseApartment; }
    std::string GetTypeName() const override { return "apartment"; }

    virtual void Update(float dt, int tod);
    virtual void Draw();
    virtual void DrawFramework();
    virtual void Save(SerializerBase& ser);
    virtual BaseType GetType() { return BaseApartment; }
    virtual double GetRent();
};

#endif // _APARTMENT_H
