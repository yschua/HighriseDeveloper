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
   short m_Route;   // changed from state to route meaning any elevator, stairs or other mode of traversal.
   short m_Building;
   short m_Level;   // 0 = lobby
   short m_X;       // 0 = outide the building
   Location ()
   {
      clear ();   // any time this structure is instantiated, clear the inner data
   }
   void clear()
   {
      m_Route = -1;
      m_Building = 0;
      m_Level = 0;
      m_X = 0;
   }
};

struct Path // this could have been a list<T> but it would slow this high traffic structure
{
   short size;   // elements in play at this time
   short index;  // the current position of the person in the array.
   Location m_PathList[8]; // the max is 4 or so transistions a person cares to make.
   Path()
   {
      clear();
   }
   void clear()
   {
      for (int idx = 0; idx < 8; ++idx )
      {
         m_PathList[idx].clear();
      }
   }
};

class C_Person
{
public:
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
      AS_Socializing,
      AS_JobHunting,
      AS_ApartmentHunting,
      AS_CondoHunting,   // Income dependant.
      AS_HotelHunting
   };

   enum Current_State   // had to add this to describe what a person is doing while heading to work, home or play.
   {
      // may also cover other activities. A person heading to work may also be stuck in an elevator queue.
      CS_Idle = 0,      // Idle is defined as doing nothing
      CS_Busy,          // Waiting for a timed event to trigger their next move. At work, sleeping etc.
      CS_Walking,       // Ok good, going somewhere
      CS_Riding,        // In a vehicle, elevator, train, car etc.
      CS_Disembarking,  // Car just dropped a person off;
      CS_Waiting        // In queue
   };

private:
   Location       m_Location;
   Path           m_WorkPath;    // To and from work, stays permanant as long as working.
   // Changes if they change jobs or the business goes bust.
   Path           m_OtherPath;   // To and from other activities when they go shopping etc.
   // Changes almost daily
   Health_State   m_Health;
   Mood_State     m_Mood;
   Activity_State m_Activity;
   Current_State  m_CurrentState;// Covers busy, waiting, walking, riding.
   int            m_Occupation;  // school and retired are valid occupations
   // not set on if this will be a class or enum

   int            m_Home;        // Where's the Crib
public:
   // CTOR/DTOR
   C_Person (Location& loc);    // x is their starting point, usually in the lobby.
   virtual ~C_Person (void);

   // Properties
   Path& get_WorkPath()    // this gets called to fill and route to and from work.
   {
      return m_WorkPath;
   }
   Path& get_OtherPath()   // this gets called to fill, move the person and alternate checking paths.
   {
      return m_OtherPath;
   }

   Activity_State get_Activity () // inline for faster access, same isolation, just quicker code.
   {
      return m_Activity;
   }
   void set_Activity (Activity_State state )
   {
      m_Activity = state;
   }
   Current_State get_CurrentState () // inline for faster access, same isolation, just quicker code.
   {
      return m_CurrentState;
   }
   void set_CurrentState (Current_State state )
   {
      m_CurrentState = state;
   }
   void set_Occupation( int occ )
   {
      m_Occupation = occ;
   }
   Location& get_Location()
   {
      return m_Location;
   }

   // Implementation
   virtual void Update (float dt);
   virtual void Draw ();
};

#endif //_PERSON_H
