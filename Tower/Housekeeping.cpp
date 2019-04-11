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

#include "Housekeeping.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "../Types/String.h"
#include "FloorBase.h"

#include <iostream>
#include <map>
#include <vector>

using namespace Gfx;

namespace TowerObjects
{
// use the XML serializer to replace this
//
const char* HousekeepingImages0[] = {"Housekeeping.png",
                                     "Housekeeping.png",
                                     "Housekeeping.png",
                                     "Housekeeping_0_d_0.png",
                                     "Housekeeping_0_d_1.png",
                                     "Housekeeping_0_d_2.png",
                                     "Housekeeping_0_d_3.png",
                                     "Housekeeping_0_d_4.png",
                                     "Housekeeping_0_d_5.png"};
struct HousekeepingImage {
    const char** Images;
    int count;
};
HousekeepingImage HousekeepingImages[] = {
    {HousekeepingImages0, 3}
    //{ HousekeepingImagesn, 7 },
    //{ HousekeepingImages6, 4 },
    //{ HousekeepingImages7, 7 }
};
const int TotalSets = 1;
}

using namespace TowerObjects;

Housekeeping::Housekeeping(int x, int level, Tower* TowerParent) :
    mCurrentState(SS_Vacant),
    mCurrentMode(SM_Night),
    FloorBase(x, x + 126, level, TowerParent)
{
    ImageManager* image_man = ImageManager::GetInstance();
    std::cout << "New Housekeeping at " << mX << ", " << mY << " level " << mLevel << std::endl;
    mPeopleInService = 0;
    mEmployees = 0;
    mMaxPositions = rand() % 6 + 2;
    SetImages(0);
}

void Housekeeping::ServiceMode(int tod)
{
    if (mPeopleInService > 0) // some people are at work
    {
        mCurrentMode = SM_DayOccupied;
    } else if (tod > 8 * 60 && tod < 16 * 60) {
        mCurrentMode = SM_DayUnoccupied;
    } else {
        mCurrentMode = SM_Night;
    }
}

void Housekeeping::ServiceState()
{
    if (mCurrentState == SS_Vacant && mPeopleInService > 0) // need to check for rent paid
    {
        int set = (1 + rand()) % (TotalSets);
        RemoveImages();
        SetImages(set);
        mCurrentState = SS_Occupied;
    }
}

void Housekeeping::RemoveImages()
{
    manimations[SM_Night]->ClearFrames();
    manimations[SM_DayUnoccupied]->ClearFrames();
    manimations[SM_DayOccupied]->ClearFrames();
}

void Housekeeping::SetImages(int set)
{
    ImageManager* image_man = ImageManager::GetInstance();
    HousekeepingImage& oi = HousekeepingImages[set];
    manimations[SM_Night] = new AnimationSingle(image_man->GetTexture(oi.Images[0], GL_RGBA), 126, 36);
    manimations[SM_Night]->SetPosition(mX, mY);
    manimations[SM_DayUnoccupied] =
        new AnimationSingle(image_man->GetTexture(oi.Images[1], GL_RGBA), 126, 36);
    manimations[SM_DayUnoccupied]->SetPosition(mX, mY);
    Animation* pAn = new Animation(126, 36);
    manimations[SM_DayOccupied] = pAn;
    for (int idx = 2; idx < oi.count; ++idx) {
        pAn->AddFrame(image_man->GetTexture(oi.Images[idx], GL_RGBA), (float)(1500 + rand() % 120));
        pAn->SetPosition(mX, mY);
    }
}

void Housekeeping::Update(float dt, int tod)
{
    ServiceMode(tod);
    manimations[mCurrentMode]->Update(dt);
}

void Housekeeping::Draw()
{
    Render(manimations[mCurrentMode]);
}

void Housekeeping::DrawFramework()
{
    RenderFramework(manimations[mCurrentMode], mID);
}

void Housekeeping::Save(SerializerBase& ser)
{
    ser.Add("type", "Housekeeping"); // first tag
    FloorBase::Save(ser);
    ser.Add("state", mCurrentState);
    ser.Add("mode", mCurrentMode);
    // if something goes bump, either deal with it or throw it
}

void Housekeeping::PeopleInOut(int count)
{
    mPeopleInService += count;
    if (mPeopleInService < 0) {
        mPeopleInService = 0;
    }
    ServiceState();
}

bool Housekeeping::PeopleApply()
{
    if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
    {
        mEmployees++;
        return true;
    }
    return false;
}