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

// When somone wants to go somewhere, just hand them over to their own personal travel agent.
// "MyPathAgent 2500 will take you to your destination quickly and safely, only 19.95 + S&H"
// The Activities Agent will hand people to this agent when they enter a travel state.
// A location and destination will be set for the person(s) preparing to embark. The path agent will
// then find the best path to that destination. Folks in the tower(s) will be transitioned from
// point to point. The nearest elevalor is found and enqueued. Should the wait time exceed A limt
// the PA will look for the another elevator close by that stops on the level desired. It found then
// the person procedes there. If time exceeds A&B limit then a moderate distance is searched. Same
// for limit C but forther. If still no satifaction, enter drastic mode( leave, move etc).
#ifndef _PATHAGENT_H
#define _PATHAGENT_H

struct Location; // from person
class C_Person;

struct Path // this could have been a list<T> but it would slow this high traffic structure
{
   short size;   // elements in play at this time
   short index;  // the current position of the person in the array.
   Location m_PathList[8]; // the max is 4 or so transistions a person cares to make.
   Path() { clear(); }
   void clear()
   {
      for (int idx = 0; idx < 8; ++idx )
      {
         m_PathList[idx].clear();
      }
   }
};

class C_PathAgent
{
private:
   C_Person* m_peep;
   Path  m_CurrentPath;

public:
   void update (float dt);
   void draw ()   // just a pass through
   {
      m_peep->draw();
   };
   C_PathAgent (C_Person* peep, Location* dest );
   virtual ~C_PathAgent (void);
};

#endif //_PATHAGENT_H
