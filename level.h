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

#ifndef _LEVEL_H
#define _LEVEL_H

class C_AnimationSingle;
class C_FloorBase;
class C_Tower;

class C_level
{
private:
   std::vector<C_FloorBase *> m_floors;
   C_Tower * m_TowerParent;
   
protected:
   int m_level;
   int m_x, m_x2, m_y;
   C_AnimationSingle * m_fire_escape_l;
   C_AnimationSingle * m_fire_escape_r;

public:
   C_level::C_level (int level, C_Tower * TowerParent);
   void add_floor (C_FloorBase * floor);
   virtual void update (float dt);
   virtual void draw ();
};

#endif
