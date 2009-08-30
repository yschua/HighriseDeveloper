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

#ifndef _LOBBY_H
#define _LOBBY_H

class C_Tiler;
class C_AnimationSingle;
class C_Camera;
class C_level;

class C_Lobby : public C_level // make lobby a level in itself
{
private:
   C_Tiler * tile;
   C_AnimationSingle * awn_left;
   C_AnimationSingle * awn_right;
   C_Camera * cam;

public:
   void Update (float dt);
   void Draw ();
   C_Lobby (int x, int x2, int level, C_Tower * TowerParent);
};

#endif
