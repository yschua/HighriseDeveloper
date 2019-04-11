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

#include "MedicalClinic.h"

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
const char* MedicalClinicImagesU[] = {"MedicalClinic_u.png", "MedicalClinic_u.png", "MedicalClinic_u.png"};
const char* MedicalClinicImages0[] = {"MedicalClinic_0_n.png",
                                      "MedicalClinic_0_d_0.png",
                                      "MedicalClinic_0_d_1.png",
                                      "MedicalClinic_0_d_2.png",
                                      "MedicalClinic_0_d_3.png",
                                      "MedicalClinic_0_d_4.png",
                                      "MedicalClinic_0_d_5.png"};
const char* MedicalClinicImages6[] = {
    "MedicalClinic_6_n.png", "MedicalClinic_6_d_0.png", "MedicalClinic_6_d_1.png", "MedicalClinic_6_d_2.png"};
const char* MedicalClinicImages7[] = {"MedicalClinic_7_n.png",
                                      "MedicalClinic_7_d_0.png",
                                      "MedicalClinic_7_d_1.png",
                                      "MedicalClinic_7_d_2.png",
                                      "MedicalClinic_7_d_4.png",
                                      "MedicalClinic_7_d_3.png",
                                      "MedicalClinic_7_d_5.png"};
struct MedicalClinicImage {
    const char** Images;
    int count;
};
MedicalClinicImage MedicalClinicImages[] = {
    {MedicalClinicImagesU, 3}
    //{ MedicalClinicImages0, 7 },
    //{ MedicalClinicImages6, 4 },
    //{ MedicalClinicImages7, 7 }
};
const int TotalSets = 1;
}

using namespace TowerObjects;

MedicalClinic::MedicalClinic(int x, int level, Tower* TowerParent) :
    mCurrentState(MS_NightUnoccupied),
    FloorBase(x, x + 144, level, TowerParent)
{
    ImageManager* image_man = ImageManager::GetInstance();
    std::cout << "New MedicalClinic at " << mX << ", " << mY << " level " << mLevel << std::endl;
    mPatients = 0;
    mEmployees = 0;
    mMaxPositions = rand() % 6 + 2;
    mMedicalClinicStyle = 0;
    SetImages(0);
}

void MedicalClinic::MedicalClinicState(int tod)
{
    if (tod > 6 * 60 && tod < 18 * 60) {
        if (mPatients > 0) // some people are at work
        {
            mCurrentState = MS_DayOccupied;
        } else {
            mCurrentState = MS_DayUnoccupied;
        }
    } else {
        if (mPatients > 0) // some people are at work
        {
            mCurrentState = MS_DayOccupied;
        } else {
            mCurrentState = MS_NightUnoccupied;
        }
    }
}

void MedicalClinic::SetImages(int set)
{
    ImageManager* image_man = ImageManager::GetInstance();
    MedicalClinicImage& oi = MedicalClinicImages[set];
    manimations[MS_NightUnoccupied] =
        new AnimationSingle(image_man->GetTexture(oi.Images[0], GL_RGBA), 144, 36);
    manimations[MS_NightUnoccupied]->SetPosition(mX, mY);
    manimations[MS_DayUnoccupied] =
        new AnimationSingle(image_man->GetTexture(oi.Images[1], GL_RGBA), 144, 36);
    manimations[MS_DayUnoccupied]->SetPosition(mX, mY);
    Animation* pAn = new Animation(144, 36);
    manimations[MS_DayOccupied] = pAn;
    // MS_DayOccupied
    for (int idx = 2; idx < oi.count; ++idx) {
        pAn->AddFrame(image_man->GetTexture(oi.Images[idx], GL_RGBA), (float)(1500 + rand() % 120));
        pAn->SetPosition(mX, mY);
    }
}

void MedicalClinic::Update(float dt, int tod)
{
    MedicalClinicState(tod);
    manimations[mCurrentState]->Update(dt);
}

void MedicalClinic::Draw()
{
    Render(manimations[mCurrentState]);
}

void MedicalClinic::DrawFramework()
{
    RenderFramework(manimations[mCurrentState], mID);
}

void MedicalClinic::Save(SerializerBase& ser)
{
    ser.Add("type", "MedicalClinic"); // first tag
    FloorBase::Save(ser);
    ser.Add("state", mCurrentState);
    ser.Add("patients", mPatients);
    ser.Add("employees", mEmployees);
    // if something goes bump, either deal with it or throw it
}

void MedicalClinic::PeopleInOut(int count)
{
    mPatients += count;
    if (mPatients < 0) {
        mPatients = 0;
    }
}

bool MedicalClinic::PeopleApply()
{
    if (mEmployees < mMaxPositions) // && mCurrentState == OS_Occupied)
    {
        mEmployees++;
        return true;
    }
    return false;
}