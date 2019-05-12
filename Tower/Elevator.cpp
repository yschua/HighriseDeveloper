/*   This file is part of Highrise Developer.
 *
 *   Foobar is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.

 *   Highrise Developer is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with Foobar.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Elevator.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"
#include "../Graphics/Tiler.h"
#include "../People/Person.h"
#include "../Root/HighRiseException.h"
#include "../Root/Physics.h"
#include "../Root/SerializerBase.h"
#include "ElevatorBase.h"
#include "ElevatorMachine.h"
#include "ElevatorShaft.h"
#include "Level.h"
#include "PersonQueue.h"
#include "RouteBase.h" // Elevators route (levels).
#include "Tower.h"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>

int Elevator::m_nextId = 0;

Elevator::Elevator(LiftStyle style, int x, int bottomLevel, int topLevel, Tower* tower) :
    Body(32, 32),
    m_id(m_nextId++),
    mLiftStyle(style),
    m_tower(tower),
    m_dirUp(true),
    m_idle(true)
{
    mTopLevel = topLevel;
    mBottomLevel = bottomLevel;
    m_carPosition = mBottomLevel * 36;
    mIdleTime = 10;
    m_maxRiders = (style == LS_HighCapacity) ? 30 : 15;

    mX = x + 2;
    mY = mBottomLevel * 36;
    mZ = -0.49f; // slightly in front of the tower

    LoadImages();
    mRouteQueues = NULL;
    SetQueues();
    SetStopLevels();
}

Elevator::~Elevator()
{
    delete mElevatorImage;
    delete mRiderImage;
    delete mLiftMachine;
    delete mLiftPit;
    delete mElevatorShaft;
};

void Elevator::LoadImages()
{
    ImageManager* images = ImageManager::GetInstance();
    const char* pImageName = "Elevator_u_n.png";

    switch (mLiftStyle) {
    case LS_Standard:
        mWidth.x = 32;
        break;
    case LS_HighCapacity:
        mWidth.x = 41;
        pImageName = "Elevator_u_w.png";
        break;
    case LS_Freight:
        mWidth.x = 32;
        pImageName = "Elevator_u_s.png";
        break;
    case LS_Express:
        mWidth.x = 32;
        pImageName = "Elevator_o_x.png";
        break;
    }

    mElevatorImage = new AnimationSingle(images->GetTexture(pImageName, GL_RGBA),
                                         static_cast<int>(mWidth.x),
                                         static_cast<int>(mHeight.y));

    mRiderImage = new AnimationSingle(images->GetTexture("Person_e.png", GL_RGBA), 8, 16);

    mRiderImage->SetPosition((float)mX + 8,
                             (float)(mBottomLevel - 1) * -36); // neg 36 so it becomed positive for model view

    mLiftMachine = new ElevatorMachine(mX - 2,
                                       mTopLevel + 1,
                                       static_cast<int>(mWidth.x + 4),
                                       this);

    mLiftPit = new AnimationSingle(images->GetTexture("LiftPit_1.png", GL_RGBA),
                                   static_cast<int>(mWidth.x + 4), 36);

    mLiftPit->SetPosition((float)mX - 2,
                          (float)(mBottomLevel - 1) * -36); // neg 36 so it becomed positive for model view

    mElevatorShaft = new ElevatorShaft(mX - 2,
                                       mTopLevel,
                                       mBottomLevel - 1,
                                       static_cast<int>(mWidth.x + 4),
                                       this);
}

void Elevator::SetStopLevels()
{
    const int numLevels = mTopLevel - mBottomLevel + 1;
    int level = mBottomLevel;
    switch (mLiftStyle) {
    case LS_Standard:
        for (int idx = 0; idx < numLevels; ++idx) {
            m_floorButtons.insert(std::make_pair(idx, FloorButton()));
            m_callButtons.insert(std::make_pair(idx, CallButton()));
        }
        break;
    case LS_HighCapacity:
        for (int idx = 0; idx < numLevels; ++idx) {
            Level* pLevel = m_tower->GetLevel(level++);
            if (pLevel && pLevel->HasLobby()) {
                m_floorButtons.insert(std::make_pair(idx, FloorButton()));
            } else {
                m_floorButtons.insert(std::make_pair(idx, FloorButton(false)));
            }
            m_callButtons.insert(std::make_pair(idx, CallButton()));
        }
        break;
    case LS_Freight:
    case LS_Express:
        break;
    }
}

void Elevator::PosCalc()
{
    const int offset = mBottomLevel * 36; // adjust for starting floor.
    // elevator sprite is only 32x32
    mElevatorImage->SetPosition((float)mX, (float)(mY - (offset + m_carPosition) + 4));
    mRiderImage->SetPosition((float)mX, (float)(mY - (offset + m_carPosition) + 18));
}

void Elevator::SetFloorButton(RoutingRequest& req) // OK, take me there
{
    int reqLevel = req.DestinLevel - mBottomLevel;
    m_floorButtons[reqLevel].m_stopping = true;
}

bool Elevator::SetCallButton(RoutingRequest& req)
{
    bool bIsOnFloor = false;
    int reqLevel = req.OriginLevel - mBottomLevel;

    if (GetCurrentLevel() == reqLevel && CanStop()) {
        SetFloorButton(req);
        bIsOnFloor = true;
    } else {
        if (reqLevel >= 0 && reqLevel < GetNumLevels()) {
            if (req.DestinLevel > req.OriginLevel) {
                m_callButtons[reqLevel].m_callUp = true;
            } else {
                m_callButtons[reqLevel].m_callDown = true;
            }
        } else {
            std::cout << "Elevator Call for wrong floor level: " << req.OriginLevel
                      << " computed index: " << reqLevel;
        }
    }
    return bIsOnFloor;
}

int Elevator::LoadPerson(Person* person, RoutingRequest& req) // returns space remaining
{
    if (GetNumRiders() < m_maxRiders) {
        int destLevel = req.DestinLevel - mBottomLevel;
        m_riders.push_back(Rider{person, destLevel});
        std::cout << "load " << person->GetId() << " to: " << destLevel << "\n";
        SetFloorButton(req);
    }
    return m_maxRiders - GetNumRiders();
}

Person* Elevator::UnloadPerson()
{
    for (auto it = m_riders.begin(); it != m_riders.end(); ++it) {
        if (it->m_destLevel == GetCurrentLevel()) {
            auto person = it->m_person;
            m_riders.erase(it);
            std::cout << "unload " << person->GetId() << " at: " << GetCurrentLevel() << "\n";
            return person;
        }
    }
    return nullptr;
}

int Elevator::FindNearestCall() const
{
    // search outwards from current level
    int up = GetCurrentLevel() + 1;
    int down = GetCurrentLevel() - 1;
    bool searchUp = true;
    while (up < GetNumLevels() || down >= 0) {
        int level = (searchUp) ? up : down;
        if (m_callButtons.at(level).m_callDown) {
            return level;
        }
        if (m_callButtons.at(level).m_callUp) {
            return level;
        }

        if (searchUp) {
            up++;
            if (down >= 0) searchUp = false;
        } else {
            down--;
            if (up < GetNumLevels()) searchUp = true;
        }
    }
    return -1;
}

bool Elevator::KeepMovingInCurrentDirection() const
{
    if (m_dirUp) {
        for (int level = GetCurrentLevel() + 1; level < GetNumLevels(); level++) {
            if (m_floorButtons.at(level).m_stopping ||
                m_callButtons.at(level).m_callDown ||
                m_callButtons.at(level).m_callUp) {
                return true;
            }
        }
    } else {
        for (int level = GetCurrentLevel() - 1; level >= 0; level--) {
            if (m_floorButtons.at(level).m_stopping ||
                m_callButtons.at(level).m_callDown ||
                m_callButtons.at(level).m_callUp) {
                return true;
            }
        }
    }
    return false;
}

int Elevator::GetNumLevels() const
{
    return static_cast<int>(m_floorButtons.size());
}

int Elevator::GetCurrentLevel() const
{
    return m_carPosition / 36 - mBottomLevel;
}

bool Elevator::CanStop() const
{
    return m_carPosition % 36 == 0;
}

int Elevator::GetNumRiders() const
{
    return static_cast<int>(m_riders.size());
}

void Elevator::Motion()
{
    const int currentLevel = GetCurrentLevel();

    if (GetNumRiders() > 0) m_idle = false;

    if (m_idle) {
        int callLevel = FindNearestCall();
        if (callLevel == -1) {
            // do nothing
            mIdleTime = 20;
        } else {
            // start movement
            m_idle = false;
            m_dirUp = (callLevel > currentLevel);
            mIdleTime = 10;
        }
    } else if (CanStop()) {
        // check for stop on call or floor
        if (m_callButtons[currentLevel].m_callDown || m_callButtons[currentLevel].m_callUp) {
            m_callButtons[currentLevel].m_callDown = m_callButtons[currentLevel].m_callUp = false;
            mIdleTime = 10;
        }
        if (m_floorButtons[currentLevel].m_stopping) {
            m_floorButtons[currentLevel].m_stopping = false;
            mIdleTime = 10;
        }

        // check remaining stops in both directions
        if (mIdleTime == 0 && !KeepMovingInCurrentDirection()) {
            m_dirUp = !m_dirUp; // change direction
            if (!KeepMovingInCurrentDirection()) {
                m_idle = true;
            }
        }
    }

    if (mIdleTime == 0 && !m_idle) {
        // moving
        m_carPosition += m_dirUp ? 1 : -1;
        mLiftMachine->Update(1);
    }

    PosCalc();
}

void Elevator::Update(float dt)
{
    std::cout << "Elevator update without time called: " << std::endl;
}

// Elevator is either in motion or idle( doors open, loading, unloading, no calls )
// When idle do nothing. Idle times are set when the elevator arrives at a floor
// When idle cycle ends scan for destinations and calls.
void Elevator::Update(float dt, int tod)
{
    if (mIdleTime > 0) {
        Person* person = UnloadPerson();
        PersonQueue* pQ = (*mRouteQueues)[GetCurrentLevel()];
        Person* personOn = pQ->TakeNextPerson();
        pQ->Update();

        if (person == NULL && personOn == NULL) {
            mIdleTime--;
        } else {
            if (person != NULL) {
                person->SetCurrentState(Person::CS_Disembarking);
            }
            if (personOn != NULL) {
                int curLevel = personOn->get_Location().mLevel;
                int idx = personOn->get_WorkPath().index;
                if (idx < 0)
                    idx = 0; // bug patch

                // personOn->SetCurrentState( Person::CS_Boarding );
                RoutingRequest req; // routing code needs to queue this person
                req.OriginLevel = curLevel;
                req.DestinLevel = personOn->get_WorkPath().mPathList[idx].mLevel;
                personOn->SetCurrentState(Person::CS_Riding);
                LoadPerson(personOn, req);
            }
            mIdleTime += 2;
        }
    } else {
        mIdleTime = 0;
        Motion();
    }
    mLiftMachine->Update(1);
}

void Elevator::Draw()
{
    const float ArrowDown[] = {-3.0f, -3.0f, 0.1f, 0.0f, -6.0f, 0.1f, 3.0f, -3.0f, 0.1f};
    const float ArrowUp[] = {-3.0f, 3.0f, 0.1f, 0.0f, 6.0f, 0.1f, 3.0f, 3.0f, 0.1f};
    const float ArrowDim[] = {0.1f, 0.4f, 0.1f, 0.7f};
    const float ArrowLit[] = {0.2f, 1.0f, 0.2f, 1.0f};
    const std::vector<int> standingPos = {12, 20, 16, 4, 18, 22, 6, 24, 8, 10, 2, 5, 9, 13, 17, 21};

    mElevatorShaft->Draw();
    mLiftMachine->Draw();
    Render(mLiftPit);
    Render(mElevatorImage);

    const size_t numRiders = static_cast<size_t>(GetNumRiders());
    for (int idx = 0; idx < std::min(numRiders, standingPos.size()); ++idx) {
        Render(mRiderImage,
               (float)(mX + standingPos[idx]),
               (float)(mX + standingPos[idx] + 8));
    }

    int il = mBottomLevel;
    int index = 0;
    for (auto it = mRouteQueues->begin(); it != mRouteQueues->end(); ++it) {
        PersonQueue* pQ = (*it);
        pQ->Draw(mX + 18, 36 * il);
        il++;
        if (m_callButtons[index].m_callUp) {
            RenderTriangle(ArrowUp, ArrowLit, mX + 4.f, il * 36.f - 48, 0.0f);
        } else {
            RenderTriangle(ArrowUp, ArrowDim, mX + 4.f, il * 36.f - 48, 0.0f);
        }
        if (m_callButtons[index].m_callDown) {
            RenderTriangle(ArrowDown, ArrowLit, mX + 4.f, il * 36.f - 48, 0.0f);
        } else {
            RenderTriangle(ArrowDown, ArrowDim, mX + 4.f, il * 36.f - 48, 0.0f);
        }
        index++;
    }
}

void Elevator::Save(SerializerBase& ser)
{
}

void Elevator::SetQueues()
{
    if (mRouteQueues == NULL) {
        mRouteQueues = new std::vector<PersonQueue*>();
    }
    int count = mTopLevel - mBottomLevel + 1;
    for (int idx = 0; idx < count; ++idx) {
        PersonQueue* pQ = new PersonQueue();
        mRouteQueues->push_back(pQ);
    }
}

PersonQueue* Elevator::FindQueue(int level)
{
    unsigned int index = level - mBottomLevel;
    if (index >= 0 && index < mRouteQueues->size()) {
        PersonQueue* pQ = (*mRouteQueues)[index];
        return pQ;
    }
    return NULL;
}

bool Elevator::StopsOnLevel(int level)
{
    unsigned int index = level - mBottomLevel;
    if (index >= 0 && index < mRouteQueues->size()) {
        return m_floorButtons[index].m_enabled;
    }
    return false;
}

int Elevator::FindLobby()
{
    return 0;
}