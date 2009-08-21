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
#pragma once
#ifndef _PERSON_H
#define _PERSON_H

// temporary home for some structures
// If Location is a destination and m_Building <=0 then this person is leaving.
// If Location is a currentLocation and m_Building = 0 then this person is outside
// Above subject to change.
struct Location
{
   short m_State;    // 0 = Idle, 1 = waiting, 2 = moving
   short m_Building;
   short m_level;   // 0 = lobby
   short m_x;       // 0 = outide the building

   void clear()
   {
      m_State = 0;
      m_Building = 0;
      m_level = 0;
      m_x = 0;
   }
};

struct Occupation
{
   short m_Working; // 0 == looking, 1 = employed
};

class C_Person
{
   // enumerations
   enum Health_State
   {
      HS_Dead,          // remove from tower
      HS_Dire,          // outside services are needed
      HS_NeedMedical,   // a medical center will help
      HS_Ill,           // caught a cold, may miss work is not happy.
      HS_Well           // I think I'll go jogging today
   };

   enum Mood_State
   {
      MS_Furious,    // this soul is about to leave
      MS_Mad,        // not good, do something
      MS_Annoyed,    // why are the elevators soo slow?
      MS_Content,    // today was ok, no major bummers and the elevators where on time
      MS_Happy,      // it's great living/working here :)
      MS_Excited     // somebody got a raise.
   };
   enum Activity_State
   {
      AS_Sleeping,   // first four are done at home (mostly).
      AS_Relaxing,
      AS_Playing,
      AS_Reading,
      AS_GoingToWork,
      AS_Working,
      AS_GoingHome,
      AS_Shopping,
      AS_BreakFast,
      AS_LunchBreak, // be sure the service personell take one
      AS_Dining,     // if you order take out, go home and eat it, was that dine in or eat out?
      AS_RestRoom, 
      AS_OnVacation,  // we'll post pics in the lobby when we return
      AS_Evacuating,
      AS_WatchingMovie,
      AS_Socializing
   };

private:
   Health_State   m_Health;
   Mood_State     m_Mood;
   Occupation     m_Employment;  // school and retired are valid occupations

public:
   C_Person (Location& loc);    // x is their starting point, usually in the lobby.
   virtual ~C_Person (void);

   virtual void update (float dt);
   virtual void draw ();
};

#endif /_PERSON_H
