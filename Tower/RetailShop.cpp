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

#include <iostream>
#include <map>
#include <vector>
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "../Graphics/Image.h"
#include "../Graphics/Animation.h"
#include "FloorBase.h"
#include "../Types/String.h"

#include "RetailShop.h"

using namespace Gfx;

namespace TowerObjects
{
// use the XML serializer to replace this
//
const char* RetailImagesU[] = {"Retail_u_n.png", "Retail_u_d.png", "Retail_u_0.png"};
const char* RetailImages0[] = {"Retail_0_n.png",
                               "Retail_0_d_0.png",
                               "Retail_0_d_1.png",
                               "Retail_0_d_2.png",
                               "Retail_0_d_3.png",
                               "Retail_0_d_4.png",
                               "Retail_0_d_5.png"};
const char* RetailImages6[] = {"Retail_6_n.png", "Retail_6_d_0.png", "Retail_6_d_1.png", "Retail_6_d_2.png"};
const char* RetailImages7[] = {"Retail_7_n.png",
                               "Retail_7_d_0.png",
                               "Retail_7_d_1.png",
                               "Retail_7_d_2.png",
                               "Retail_7_d_4.png",
                               "Retail_7_d_3.png",
                               "Retail_7_d_5.png"};
struct RetailImage {
    const char** Images;
    int count;
};
RetailImage RetailImages[] = {
    {RetailImagesU, 3}
    //{ RetailImages0, 7 },
    //{ RetailImages6, 4 },
    //{ RetailImages7, 7 }
};
const int TotalSets = 1;
}

using namespace TowerObjects;

RetailShop::RetailShop(int x, int level, Tower* TowerParent) :
    mCurrentState(RS_Vacant),
    mCurrentMode(RM_Night),
    FloorBase(x, x + 72, level, TowerParent)
{
    ImageManager* image_man = ImageManager::GetInstance();
    std::cout << "New Retail at " << mX << ", " << mY << " level " << mLevel << std::endl;
    mPeopleInShop = 0;
    mEmployees = 0;
    mRetailShopStyle = rand() % 6 + 2;
    mRetailShopStyle = 0;
    SetImages(0);
}

void RetailShop::RetailShopMode(int tod)
{
    if (mPeopleInShop > 0) // some people are at work
    {
        mCurrentMode = RM_DayOccupied;
    } else if (tod > 8 * 60 && tod < 16 * 60) {
        mCurrentMode = RM_DayUnoccupied;
    } else {
        mCurrentMode = RM_Night;
    }
}

void RetailShop::RetailShopState()
{
    if (mCurrentState == RS_Vacant && mPeopleInShop > 0) // need to check for rent paid
    {
        int set = 1 + rand() % (TotalSets);
        RemoveImages();
        SetImages(set);
        mCurrentState = RS_Occupied;
    }
}

void RetailShop::RemoveImages()
{
    manimations[RM_Night]->ClearFrames();
    manimations[RM_DayUnoccupied]->ClearFrames();
    manimations[RM_DayOccupied]->ClearFrames();
}

void RetailShop::SetImages(int set)
{
    ImageManager* image_man = ImageManager::GetInstance();
    RetailImage& oi = RetailImages[set];
    manimations[RM_Night] = new AnimationSingle(image_man->GetTexture(oi.Images[0], GL_RGBA), 72, 36);
    manimations[RM_Night]->SetPosition(mX, mY);
    manimations[RM_DayUnoccupied] = new AnimationSingle(image_man->GetTexture(oi.Images[1], GL_RGBA), 72, 36);
    manimations[RM_DayUnoccupied]->SetPosition(mX, mY);
    Animation* pAn = new Animation(72, 36);
    manimations[RM_DayOccupied] = pAn;
    for (int idx = 2; idx < oi.count; ++idx) {
        pAn->AddFrame(image_man->GetTexture(oi.Images[idx], GL_RGBA), (float)(1500 + rand() % 120));
        pAn->SetPosition(mX, mY);
    }
}

void RetailShop::Update(float dt, int tod)
{
    RetailShopMode(tod);
    manimations[mCurrentMode]->Update(dt);
}

void RetailShop::Draw() { Render(manimations[mCurrentMode]); }

void RetailShop::DrawFramework() { RenderFramework(manimations[mCurrentMode], mID); }

void RetailShop::Save(SerializerBase& ser)
{
    ser.Add("type", "Retail"); // first tag
    FloorBase::Save(ser);
    ser.Add("state", ToString((mCurrentState == RS_Occupied) ? 1 : 0).c_str());
    ser.Add("mode", mCurrentMode);
    // if something goes bump, either deal with it or throw it
}

void RetailShop::PeopleInOut(int count)
{
    mPeopleInShop += count;
    if (mPeopleInShop < 0) {
        mPeopleInShop = 0;
    }
    RetailShopState();
}

bool RetailShop::PeopleApply()
{
    if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
    {
        mEmployees++;
        return true;
    }
    return false;
}