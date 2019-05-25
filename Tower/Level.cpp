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

#include "Level.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "../People/Person.h"
#include "../Root/HighRiseException.h"
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "../Types/String.h"
#include "FloorBase.h"
#include "../Routes/PersonQueue.h"
#include "../Routes/Routes.h"

#include <cstring>
#include <iostream>

using namespace Gfx;

const int Level::mUnitSize =
    9; // used as he minimum pixels that any level or empty floor space can be. Snap-To-Grid

Level::Level(int level, int x, int y, int x2, Tower* TowerParent) : mTowerParent(TowerParent)
{
    mLevel = level;
    mID = FloorBase::GetNextID();
    mRentCollected = 0;
    mNextRentDay = 0;
    // The levels origin and vectors (partial implementation for 3D)
    // mX, ,X2 are set in SetFloorPosiitons (x,x2)
    mY = y * -36; //(int)(Camera::GetInstance()->GetSceneRect ().Top ) - (mLevel * 36);
    mZ = -0.4f;   // Face is always at zero for now
                  // missing are the Y (up) and Z (foward) vectors.

    if (level < 0) {
        nFireEscapeLeft =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("Foundation.png", GL_RGBA), 9, 36);
        nFireEscapeRight =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("Foundation.png", GL_RGBA), 9, 36);
    } else if (level > 0) {
        nFireEscapeLeft =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("FireEscape_l.png", GL_RGBA), 24, 36);
        nFireEscapeRight =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("FireEscape_r.png", GL_RGBA), 24, 36);
    } else {
        nFireEscapeLeft =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("AwnLeft.png", GL_RGBA), 56, 36);
        nFireEscapeRight =
            new AnimationSingle(ImageManager::GetInstance()->GetTexture("AwnRight.png", GL_RGBA), 56, 36);
    }
    mEmptyFLoor =
        new AnimationSingle(ImageManager::GetInstance()->GetTexture("EmptyFloor_d_1.png", GL_RGBA), 56, 36);
    // proto code
    mTheLevel = new AnimationEmpty(x2 - x, 36);
    mpFloorSpaceGrid = NULL;
    mFloorSpaceGridSize = 0;
    SetFloorPositions(x, x2);
}

// Level::Level(TiXmlNode* pnLevel)
//{
//   TiXmlNode* pnNum = pnLevel->FirstChild("number");
//}

Level::~Level()
{
    if (mpFloorSpaceGrid != NULL) {
        delete mpFloorSpaceGrid;
    }
}

bool Level::HasLobby()
{
    if (mLevel == 0)
        return true;

    for (auto i = mFloorSpaces.begin(); i != mFloorSpaces.end(); i++) {
        FloorBase* pFB = (*i).second.get();
        if (pFB->GetType() == BaseSkyLobby) {
            return true;
        }
    }
    return false;
}

bool Level::AddFloorSpace(std::unique_ptr<FloorBase> floor)
{
    mFloorSpaces.insert(std::make_pair(floor->GetID(), std::move(floor)));
    //   if (floor->mX < mX)
    //      mX = (int)floor->mX;
    //   if (floor->mX2 > mX2)
    //      mX2 = (int)floor->mX2;
    ScanFloorSpace();
    return true;
}

bool Level::RemoveFloorSpace(FloorBase* floor)
{
    mFloorSpaces.erase(floor->GetID());
    ScanFloorSpace();
    return true;
}

void Level::SetFloorPositions(int x, int x2)
{
    // The levels origin and vectors (partial implementation for 3D)
    mX = x;   //(int)Camera::GetInstance()->GetSceneRect ().Left;
    mX2 = x2; // simple xvector defaults to a minimum floor size
    if (mLevel < 0) {
        nFireEscapeLeft->SetPosition((float)mX - 9.0f,
                                     (float)mY); // pour some concrete, replaces stairs underground
        nFireEscapeRight->SetPosition((float)mX2, (float)mY);
    } else {
        nFireEscapeLeft->SetPosition((float)mX - 24.0f, (float)mY);
        nFireEscapeRight->SetPosition((float)mX2, (float)mY);
    }
    mEmptyFLoor->SetPosition((float)mX, (float)mY); // x is irrelivant
    ResizeFloorSpaceGrid();
    mTheLevel->SetPosition((float)mX, (float)mY);
}

void Level::Update(float dt, int tod)
{
    mRentCollected = 0;
    if (dt == 1 && mNextRentDay > 330)
        mNextRentDay = 1;
    for (auto i = mFloorSpaces.begin(); i != mFloorSpaces.end(); i++) {
        FloorBase* pFB = (*i).second.get();
        pFB->Update(20, tod);

        if (dt >= mNextRentDay) {
            double fRent = pFB->GetRent();
            mRentCollected += fRent;
        }
    }
    if (dt >= mNextRentDay)
        mNextRentDay += 7;
}

// Function that calls the OpenGL rendering in the subclass.
void Level::Draw()
{
    for (auto i = mFloorSpaces.begin(); i != mFloorSpaces.end(); i++) {
        FloorBase* pFB = (*i).second.get();
        if (pFB) {
            pFB->Draw();
        }
    }
    // Camera::GetInstance()->Draw (*nFireEscapeLeft);
    // Camera::GetInstance()->Draw (*nFireEscapeRight);
    DrawEmptySpace();
    if (mX2 > mX) {
        Render(nFireEscapeLeft);
        Render(nFireEscapeRight);
    }
}

void Level::DrawFramework(bool LevelOnly)
{
    if (LevelOnly) {
        RenderFramework(mTheLevel, mID);
    } else {
        for (auto i = mFloorSpaces.begin(); i != mFloorSpaces.end(); i++) {
            FloorBase* pFB = (*i).second.get();
            pFB->DrawFramework();
        }
        // RenderFramework (*nFireEscapeLeft); these three need framework draw too
        // RenderFramework (*nFireEscapeRight);
    }
}

void Level::DrawEmptyFramework()
{
    try {
        for (int i = 0; i < mFloorSpaceGridSize; ++i) {
            if (mpFloorSpaceGrid[i] == 0) {
                int x = i * 9;
                RenderFramework(mEmptyFLoor, (float)(mX + x), (float)(mX + x + 9), i + 1);
            }
        }
    } catch (...) {
        mFloorSpaceGridSize = 0; // stop this from recurring
        throw new HighriseException("Error rendering empty Floor Space");
    }
}

FloorBase* Level::GetSpaceByID(int id)
{
    auto it = mFloorSpaces.find(id);
    if (it != mFloorSpaces.end()) {
        FloorBase* fb = (*it).second.get();
        return fb;
    }
    return NULL;
}

FloorBase* Level::FindSpace(int x)
{
    for (auto it = mFloorSpaces.begin(); it != mFloorSpaces.end(); ++it) {
        FloorBase* pFB = (*it).second.get();
        if (x >= pFB->GetX() && x < pFB->GetX2()) {
            return pFB;
        }
    }
    return NULL;
}

// Possible Deprecation
bool Level::TestForEmptySpace(int x, int x2)
{
    for (auto it = mFloorSpaces.begin(); it != mFloorSpaces.end(); ++it) {
        FloorBase* pFB = (*it).second.get();
        if ((x >= pFB->GetX() && x <= pFB->GetX2()) || (x >= pFB->GetX() && x2 <= pFB->GetX2())) {
            return false;
        }
    }
    return true;
}

void Level::ResizeFloorSpaceGrid()
{
    if ((mX2 - mX) / 9 > mFloorSpaceGridSize) {
        try {
            mFloorSpaceGridSize = (mX2 - mX) / 9;
            if (mpFloorSpaceGrid != NULL) {
                delete mpFloorSpaceGrid;
                mpFloorSpaceGrid = NULL; // set null in case the new fails, don't want the old pointer
                                         // to make matters worse while the app attemps to save and exit.
            }
            mpFloorSpaceGrid = new unsigned char[mFloorSpaceGridSize + 1];
        } catch (...) {
            throw new HighriseException("Error resizing FloorSpace grid");
        }
    }
    ScanFloorSpace();
}

// Clear the floor space grid then scan through the occupied space list (mFloorSpaces).
// Keep track of spaces large enough to hold the minimum hotel room or restroom which is 3 units
// (3*mUnitSize); also keep track is there are any empty spaces to skip rendering if level is fully occupied
// and no empty spaces.
//
void Level::ScanFloorSpace() // Marks the gird for what is in the space
{
    int iEmpty = 0;
    int iMaxEmptyUnits = 0;
    mFloorIsFull = false;
    if (mpFloorSpaceGrid == NULL) {
        return; // for now
    }
    try {
        memset(mpFloorSpaceGrid, 0, sizeof(unsigned char) * mFloorSpaceGridSize);
        for (auto it = mFloorSpaces.begin(); it != mFloorSpaces.end(); ++it) {
            FloorBase* pFB = (*it).second.get();
            int x = int((pFB->GetX() - this->mX) / 9);
            int x2 = int((pFB->GetX2() - this->mX) / 9);

            for (int i = x; i < x2; ++i) {
                if (i >= 0 && i < mFloorSpaceGridSize) {
                    mpFloorSpaceGrid[i] = 1; // pFB->GetTypeCode(); // identify for the minimap
                }
            }
        }
        int iCount = 0;
        for (int i = 0; i < mFloorSpaceGridSize; ++i) {
            if (mpFloorSpaceGrid[i] == 0) {
                iCount++;
                iEmpty++;
            } else {
                if (iCount > iMaxEmptyUnits) {
                    iMaxEmptyUnits = iCount; // track floor space for at least one minimum space available
                                             // else flag no empty space
                }
                iCount = 0;
            }
        }
    } catch (...) {
        throw new HighriseException("Array Error scaning FloorSpace");
    }

    if (iEmpty == 0) {
        mNoEmptyFloorSpace = true;
    } else {
        mNoEmptyFloorSpace = false;
    }
    if (iMaxEmptyUnits < 3) {
        mFloorIsFull = true;
    }
}

bool Level::IsSpaceEmpty(int ix, int ix2) // TestForEmptySpace...
{
    bool bResult = true;
    int x = int((ix - this->mX) / 9);
    int x2 = int((ix2 - this->mX) / 9);
    if (x < 0 || x2 > mFloorSpaceGridSize)
        return false;

    for (int i = x; i < x2; ++i) {
        if (i >= 0 && i < mFloorSpaceGridSize) {
            if (mpFloorSpaceGrid[i]) {
                bResult = false;
                break;
            }
        }
    }
    return bResult;
}

void Level::DrawEmptySpace()
{
    try {
        int xStart = -1;
        int xCount = 0;
        for (int i = 0; i < mFloorSpaceGridSize; ++i) {
            if (mpFloorSpaceGrid[i] == 0) {
                if (xStart < 0) {
                    xCount = 1;
                    xStart = i;
                } else {
                    xCount++;
                }
            } else {
                if (xCount > 0) {
                    Render(mEmptyFLoor, mX + xStart * 9.0f, mX + (xStart + xCount) * 9.0f);
                    xStart = -1;
                    xCount = 0;
                }
            }
        }
        if (xCount > 0) {
            Render(mEmptyFLoor, mX + xStart * 9.0f, mX + (xStart + xCount) * 9.0f);
        }
    } catch (...) {
        mFloorSpaceGridSize = 0; // stop this from recurring
        throw new HighriseException("Error rendering empty Floor Space");
    }
}

// bool Level::Save(TiXmlElement* pnParent)
//{
//   TiXmlElement* pnType = new TiXmlElement("type");
//   TiXmlText* ptType = new TiXmlText((mLevel==0)?"Lobby":"Floor");
//   pnType->LinkEndChild(ptType);
//   TiXmlElement* pnLevel = new TiXmlElement("level");
//   TiXmlText* ptLevel = new TiXmlText(ToString(mLevel).c_str());
//   pnLevel->LinkEndChild(ptLevel);
//   TiXmlElement* pnXStart = new TiXmlElement("xstart");
//   TiXmlText* ptXStart = new TiXmlText(ToString(mX).c_str());
//   pnXStart->LinkEndChild(ptXStart);
//   TiXmlElement* pnXEnd = new TiXmlElement("xend");
//   TiXmlText* ptXEnd = new TiXmlText(ToString(mX2).c_str());
//   pnXEnd->LinkEndChild(ptXEnd);
//
//   pnParent->LinkEndChild(pnType);
//   pnParent->LinkEndChild(pnLevel);
//   pnParent->LinkEndChild(pnXStart);
//   pnParent->LinkEndChild(pnXEnd);
//   for (unsigned int i = 0; i < mFloorSpaces.size(); i++) {
//      TiXmlElement* pnSpace = new TiXmlElement("room");
//      mFloorSpaces[i]->Save(XMLSerializer(pnSpace));
//      pnParent->LinkEndChild(pnSpace);
//   }
//   return true;
//}

void Level::Save(SerializerBase& ser)
{
    ser.Add("type", "Floor"); // first tag
    ser.Add("level", mLevel); // first tag
    ser.Add("xstart", mX);    // first tag
    ser.Add("xend", mX2);     // first tag
    ser.Add("ystart", mY);    // first tag
    ser.Add("zstart", mZ);    // first tag
    //   ser.Add("state", ToString((mcurrent_state == floor_occupied_day)?1:0).c_str()); // use the state
    //   engine get this property
    // if something goes bump, either deal with it or throw it
}