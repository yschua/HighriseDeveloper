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

#include "Office.h"

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
const char* OfficeImagesU[] = {"Office_u_n.png", "Office_u_d.png", "Office_u_d.png"};
const char* OfficeImages0[] = {"Office_0_n.png",
                               "Office_0_d_0.png",
                               "Office_0_d_1.png",
                               "Office_0_d_2.png",
                               "Office_0_d_3.png",
                               "Office_0_d_4.png",
                               "Office_0_d_5.png"};
const char* OfficeImages6[] = {"Office_6_n.png", "Office_6_d_0.png", "Office_6_d_1.png", "Office_6_d_2.png"};
const char* OfficeImages7[] = {"Office_7_n.png",
                               "Office_7_d_0.png",
                               "Office_7_d_1.png",
                               "Office_7_d_2.png",
                               "Office_7_d_4.png",
                               "Office_7_d_3.png",
                               "Office_7_d_5.png"};
struct OfficeImage {
    const char** Images;
    int count;
};
OfficeImage OfficeImages[] = {{OfficeImagesU, 3}, {OfficeImages0, 7}, {OfficeImages6, 4}, {OfficeImages7, 7}};
const int TotalSets = 4;
}

using namespace TowerObjects;

int Office::mWidth = 8;
int Office::mHeight = 1;

Office::Office(int x, int level, Tower* TowerParent) :
    mCurrentState(OS_Vacant),
    mCurrentMode(OM_Night),
    FloorBase(x, x + 72, level, TowerParent)
{
    ImageManager* image_man = ImageManager::GetInstance();
    std::cout << "New office at " << mX << ", " << mY << " level " << mLevel << std::endl;
    mPeopleInOffice = 0;
    mEmployees = 0;
    mMaxPositions = 5;
    mOfficeStyle = 0;
    SetImages(0);
}

void Office::OfficeMode(int tod)
{
    if (mPeopleInOffice > 0) // some people are at work
    {
        mCurrentMode = OM_DayOccupied;
    } else if (tod > 8 * 60 && tod < 18 * 60) {
        mCurrentMode = OM_DayUnoccupied;
    } else {
        mCurrentMode = OM_Night;
    }
}

void Office::OfficeState()
{
    if (mCurrentState == OS_Vacant && mPeopleInOffice > 0) // need to check for rent paid
    {
        int set = 1 + rand() % (TotalSets - 1);
        RemoveImages();
        SetImages(set);
        mCurrentState = OS_Occupied;
    }
}

void Office::RemoveImages()
{
    manimations[OM_Night]->ClearFrames();
    manimations[OM_DayUnoccupied]->ClearFrames();
    manimations[OM_DayOccupied]->ClearFrames();
}

void Office::SetImages(int set)
{
    ImageManager* image_man = ImageManager::GetInstance();
    OfficeImage& oi = OfficeImages[set];
    manimations[OM_Night] = new AnimationSingle(image_man->GetTexture(oi.Images[0], GL_RGBA), 72, 36);
    manimations[OM_Night]->SetPosition(mX, mY);
    manimations[OM_DayUnoccupied] = new AnimationSingle(image_man->GetTexture(oi.Images[1], GL_RGBA), 72, 36);
    manimations[OM_DayUnoccupied]->SetPosition(mX, mY);
    Animation* pAn = new Animation(72, 36);
    manimations[OM_DayOccupied] = pAn;
    for (int idx = 2; idx < oi.count; ++idx) {
        pAn->AddFrame(image_man->GetTexture(oi.Images[idx], GL_RGBA),
                      static_cast<float>(1500 + rand() % 120));
        pAn->SetPosition(mX, mY);
    }
}

void Office::Update(float dt, int tod)
{
    OfficeMode(tod);
    manimations[mCurrentMode]->Update(dt);
}

void Office::Draw()
{
    Render(manimations[mCurrentMode]);
}

void Office::DrawFramework()
{
    RenderFramework(manimations[mCurrentMode], mID);
}

void Office::Save(SerializerBase& ser)
{
    ser.Add("type", "office"); // first tag
    FloorBase::Save(ser);
    ser.Add("state", ToString((mCurrentState == OS_Occupied) ? 1 : 0).c_str());
    ser.Add("mode", mCurrentMode);
    // if something goes bump, either deal with it or throw it
}

void Office::PeopleInOut(int count)
{
    mPeopleInOffice += count;
    if (mPeopleInOffice < 0) {
        mPeopleInOffice = 0;
    }
    OfficeState();
}

bool Office::PeopleApply()
{
    if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
    {
        mEmployees++;
        return true;
    }
    return false;
}

double Office::GetRent()
{
    if (mEmployees > 0)
        return mRent;
    return 0;
}
