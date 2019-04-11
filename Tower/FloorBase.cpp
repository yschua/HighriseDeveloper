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

#include "FloorBase.h"

#include "../People/Person.h"
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "../Scene/Scene.h" // registation into the scene
#include "../Types/String.h"
#include "../xml/tinyxml/tinyxml.h"
#include "Routes.h"
#include "Tower.h"

#include <iostream>

// using namespace Gfx;
unsigned int FloorBase::NextID = 1;

FloorBase::FloorBase(int x, int x2, int level, Tower* pTowerParent) :
    mX((float)x),
    mX2((float)x2),
    mTowerParent(pTowerParent)
{
    mLevel = level;
    mY = (float)(mLevel * -36);
    mZ = -0.5f;
    mID = FloorBase::GetNextID();
    mOccupants = 0;
    mOwner = nullptr;
    mRent = 0;
    mSalePrice = 0;
}

FloorBase::~FloorBase()
{
    // TODO might be better to banish or kill any occupants
    if (mOwner != nullptr)
        mOwner->ResetState();
}

void FloorBase::Save(SerializerBase& ser)
{
    ser.Add("number", this->mID);
    ser.Add("xpos", ToString(mX).c_str());
    ser.Add("ypos", ToString(mY).c_str());
    ser.Add("zpos", ToString(mZ).c_str());
    ser.Add("rent", ToString(mRent).c_str());
}

int FloorBase::GetNextID() // static
{
    return NextID++;
}

void FloorBase::SetOwner(Person* pPerson)
{
    mOwner = pPerson;
    // add family and/or partners for residences
    // allow employment for offices
    mOccupants = 1;
}

void FloorBase::Update(float dt, int tod)
{
    std::cout << "Floor base class: update function called" << std::endl;
}

void FloorBase::Draw()
{
    std::cout << "Floor base class: Draw function called" << std::endl;
}

std::string FloorBase::GetTypeName() const
{
    return "Room";
}

std::string FloorBase::GetName() const
{
    auto str = GetTypeName();
    str += " #" + std::to_string(mID);
    str += " Level " + std::to_string(mLevel);
    return str;
}
