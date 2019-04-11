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

#include "Security.h"

using namespace Gfx;

namespace TowerObjects
{
// use the XML serializer to replace this
//
const char* Security_Images0[] = {"Security_u.png",
                                  "Security_u.png",
                                  "Security_u.png",
                                  "Security_u_0.png",
                                  "Security_u_1.png",
                                  "Security_u_2.png",
                                  "Security_u_3.png",
                                  "Security_u_4.png",
                                  "Security_u_5.png"};
struct Security_Image {
    const char** Images;
    int count;
};
Security_Image Security_Images[] = {{Security_Images0, 3}};
const int TotalSets = 1;
}

using namespace TowerObjects;

Security::Security(int x, int level, Tower* TowerParent) :
    mCurrentState(SE_Unoccupied),
    FloorBase(x, x + 126, level, TowerParent)
{
    ImageManager* image_man = ImageManager::GetInstance();
    std::cout << "New Security_ at " << mX << ", " << mY << " level " << mLevel << std::endl;
    mPeopleInSecurity = 0;
    mEmployees = 0;
    mMaxPositions = rand() % 6 + 2;
    SetImages(0);
}

void Security::SecurityState(int tod)
{
    if (mPeopleInSecurity > 0) // some people are at work
    {
        mCurrentState = SE_Occupied;
    } else {
        mCurrentState = SE_Unoccupied;
    }
}

void Security::SetImages(int set)
{
    ImageManager* image_man = ImageManager::GetInstance();
    Security_Image& oi = Security_Images[set];
    manimations[SE_Unoccupied] = new AnimationSingle(image_man->GetTexture(oi.Images[1], GL_RGBA), 126, 36);
    manimations[SE_Unoccupied]->SetPosition(mX, mY);
    Animation* pAn = new Animation(126, 36);
    manimations[SE_Occupied] = pAn;
    for (int idx = 0; idx < oi.count; ++idx) {
        pAn->AddFrame(image_man->GetTexture(oi.Images[idx], GL_RGBA), (float)(1500 + rand() % 120));
        pAn->SetPosition(mX, mY);
    }
}

void Security::Update(float dt, int tod)
{
    SecurityState(tod);
    manimations[mCurrentState]->Update(dt);
}

void Security::Draw()
{
    Render(manimations[mCurrentState]);
}

void Security::DrawFramework()
{
    RenderFramework(manimations[mCurrentState], mID);
}

void Security::Save(SerializerBase& ser)
{
    ser.Add("type", "Security_"); // first tag
    FloorBase::Save(ser);
    ser.Add("state", SE_Occupied);
    // if something goes bump, either deal with it or throw it
}

void Security::PeopleInOut(int count)
{
    mPeopleInSecurity += count;
    if (mPeopleInSecurity < 0) {
        mPeopleInSecurity = 0;
    }
}

bool Security::PeopleApply()
{
    if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
    {
        mEmployees++;
        return true;
    }
    return false;
}