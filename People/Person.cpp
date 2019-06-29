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

void Person::SetCurrent(int level)
{
    mLocation.mLevel = level;
}

void Person::ResetState()
{
    mOccupation = 0;
}

ActivityStateMachine& Person::GetActivityStateMachine()
{
    return m_activityState;
}
