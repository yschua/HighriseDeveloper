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

#ifndef _OFFICE_H
#define _OFFICE_H

enum office_state
{
   s_unoccupied_day,
   s_occupied_day
};

class C_office : public C_FloorBase
{
private:
   office_state unoccupied_day (float dt);
   office_state occupied_day (float dt);
   std::map<office_state, C_Animation *> m_animations;
   office_state m_current_state;
   int m_current_animation;

public:
   void Update (float dt);
   void Draw ();
   C_office (int x, int level, C_Tower * TowerParent);
};

#endif
