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

class Tiler;
class AnimationSingle;
//class Camera;
class Level;

class Lobby : public Level // make lobby a level in itself
{
private:
   Tiler * tile;
   AnimationSingle * awn_left;
   AnimationSingle * awn_right;
   //Camera * cam;

public:
   void Update (float dt);
   void Draw ();
   Lobby (int x, int x2, int level, Tower * TowerParent);
};

#endif
