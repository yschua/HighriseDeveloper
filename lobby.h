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

class C_Lobby
{
private:
    int m_level;
    int m_x, m_x2, m_y;
    C_Tiler * tile;
    C_AnimationSingle * awn_left;
    C_AnimationSingle * awn_right;
    C_Camera * cam;
    void pos_calc ();

public:
    void update (float dt);
    void draw ();
    C_Lobby (int x, int x2, int level);
};

#endif