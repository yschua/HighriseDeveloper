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

// People that make the tower thrive.

#include "Person.h"

#include "../Graphics/Animation.h"
#include "../Graphics/Image.h"

#include <iostream>

int Person::m_nextId = 0;

Person::Person(Location& loc) : m_id(m_nextId++), m_activityState(*this)
{
    mHealth = HS_Well;
    mMood = MS_Content;
    ResetState();
    mLocation = loc; // copy
    ImageManager* pImageMam = ImageManager::GetInstance();
    Texture* ptexHappy = pImageMam->GetTexture("Person_h.png", GL_RGBA);
    Texture* ptexAnnoied = pImageMam->GetTexture("Person_a.png", GL_RGBA);
    Texture* ptexMad = pImageMam->GetTexture("Person_m.png", GL_RGBA);

    manimations[MS_Furious] = new AnimationSingle(ptexMad, 8, 16);
    manimations[MS_Mad] = new AnimationSingle(ptexMad, 8, 16);
    manimations[MS_Annoyed] = new AnimationSingle(ptexAnnoied, 8, 16);
    manimations[MS_Annoyed]->SetPosition(590, 0);
    manimations[MS_Content] = new AnimationSingle(ptexHappy, 8, 16);
    manimations[MS_Content]->SetPosition(590, 0);
    manimations[MS_Happy] = new AnimationSingle(ptexHappy, 8, 16);
    manimations[MS_Happy]->SetPosition(590, 0);
    manimations[MS_Excited] = new AnimationSingle(ptexHappy, 8, 16);
    manimations[MS_Excited]->SetPosition(590, 0);
}
Person::~Person(void) {}

void Person::Update(int tod) // actual time
{
    m_activityState.Update(tod);
}

void Person::Draw()
{
    Render(manimations[mMood]);
}

void Person::Draw(int vx, int vy)
{
    Render(manimations[mMood], static_cast<float>(vx), static_cast<float>(vx + 8));
}

void Person::SetResidence(int level)
{
    SetActivity(AS_GoingHome);
    mWorkPath.mPathList[0].mLevel = level;
    mWorkPath.mPathList[0].mX = 400; // need this
    mHome = 1;                       // pResidence
}

void Person::SetCurrent(int level)
{
    mLocation.mLevel = level;
}

void Person::ResetState()
{
    mActivity = AS_JobHunting; // noob, starts out looking for home, job etc.
    mOccupation = 0;
    mHome = 0;
    mCurrentState = CS_Idle;
}

void Person::GoingToWork()
{
    if (mWorkPath.index < mWorkPath.size) {
        Location& cur = mWorkPath.mPathList[mWorkPath.index];
        // TODO: check building first but for now we only have 1
        if (cur.mLevel == mLocation.mLevel) {
            mLocation.mX = cur.mX; // TODO: Move peep in animator
            mWorkPath.index++;
        } else {
            // waiting or on an elevator
        }
    }
    if (mWorkPath.index >= mWorkPath.size) // this can be handled better and also need to check times
    {
        mLocation.mLevel = mWorkPath.mPathList[mWorkPath.index - 1]
            .mLevel; // this will bring the car to the office level at days end
        SetActivity(AS_Working);        // offices and businesses show employees at work.
    }
}

void Person::Working(int tod)
{
    if (tod > 17 * 60) {
        SetActivity(AS_ClockingOut);
        SetCurrentState(Person::CS_Walking);
        mWorkPath.index--;                               // this is the return trip home
    } else if (tod > 12 * 60 && tod < 12 * 60 + 15) // do lunch
    {
        SetActivity(AS_LunchBreak);
        SetCurrentState(Person::CS_Walking);
        mWorkPath.index--; // this is the return trip home
    }
}

void Person::LunchBreak(int tod)
{
    if (tod > 13 * 60) {
        SetActivity(AS_GoingToWork);
        SetCurrentState(Person::CS_Walking);
    }
}

void Person::GoingHome()
{
    if (mWorkPath.index > 0) {
        Location& cur = mWorkPath.mPathList[mWorkPath.index];
        // TODO: check building first but for now we only have 1
        if (cur.mLevel == mLocation.mLevel) {
            mLocation.mX = cur.mX; // TODO: Move peep in animator
            mWorkPath.index--;
        } else {
            // waiting or on an elevator
        }
    } else {
        SetActivity(AS_Relaxing); // offices and businesses show employees at work.
        // this will bring the car to the office level at days end
        mLocation.mLevel = mWorkPath.mPathList[mWorkPath.index].mLevel; 
    }
}

void Person::Sleep(int tod)
{
    if (tod > 8 * 60 && tod < 14 * 60) {
        SetActivity(AS_GoingToWork);
        SetCurrentState(CS_Busy);
    }
}

ActivityStateMachine& Person::GetActivityStateMachine()
{
    return m_activityState;
}
