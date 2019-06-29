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

// People that make the tower thrive, treat them well and you prosper.
// Annoy them and they will fight back
// Make them made and they take their money elsewhere.
#ifndef _PERSON_H
#define _PERSON_H

#include "ActivityStateMachine.h"
#include "../Graphics/ModelObject.h"

#include <map>

class AnimationSingle;

class Person : public Gfx::ModelObject
{
public:
    // enumerations
    enum Health_State {
        HS_Dead,        // remove from tower
        HS_Dire,        // outside services are needed
        HS_NeedMedical, // a medical center will help
        HS_Ill,         // caught a cold, may miss work is not happy.
        HS_Well         // I think I'll go jogging today
    };

    enum Mood_State {
        MS_Furious, // this soul is about to leave
        MS_Mad,     // not good, do something
        MS_Annoyed, // why are the elevators soo slow?
        MS_Content, // today was ok, no major bummers and the elevators where on time
        MS_Happy,   // it's great living/working here :)
        MS_Excited  // somebody got a raise.
    };

public:
    Person(); // x is their starting point, usually in the lobby.
    virtual ~Person();

    void SetOccupation(int occ) { mOccupation = occ; }
    int GetOccupation() { return mOccupation; }
    FloorBase* GetWorkID() // number of the office or buisinee we work in
    {
        return mWorkID;
    }
    void SetWorkID(FloorBase* id)
    {
        mWorkID = id; // number of the office or buisinee we work in
    }
    // Implementation methods
    virtual void Update(int tod);
    virtual void Draw();
    virtual void Draw(int vx, int vy);
    virtual int DrawFramework(int id) { return 0; }
    void SetCurrent(int Level);
    int GetCurrent() { return m_location; }
    void ResetState();
    int GetId() const { return m_id; }
    ActivityStateMachine& GetActivityStateMachine();

private:
    static int m_nextId;
    const int m_id;

    int m_location; // location is level for now
    Health_State mHealth;
    Mood_State mMood;
    int mOccupation;             // school and retired are valid occupations
    std::map<Mood_State, AnimationSingle*> manimations;
    // not set on if this will be a class or enum
    FloorBase* mWorkID; // number of the office or buisinee we work in
    ActivityStateMachine m_activityState;
};

#endif //_PERSON_H
