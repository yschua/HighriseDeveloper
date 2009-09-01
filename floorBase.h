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

#ifndef _FLOORBASE_H
#define _FLOORBASE_H

class Tower;
class Level;

class FloorBase
{
   friend Level;  // allows level to own these spaces by being able to set protected variables.
protected:
   int mLevel;
   Tower * mTowerParent;

//public:
   int mX;    // lower left origin.x
   int mX2;   // x vector = width
   int mY;    // lower left origin.y
               // y vector = height
               // z vector = depth but not implement until 3D
//   int mx, mx2, my;
public:
   virtual void Update (float dt);
   virtual void Draw ();
   FloorBase (int x, int x2, int level, Tower * TowerParent);
};

#endif
