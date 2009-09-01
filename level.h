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

class AnimationSingle;
class FloorBase;
class Tower;

class Level
{
private:
   std::vector<FloorBase *> mfloors;
   Tower * mTowerParent;

protected:
   int mLevel;
   int mX;    // lower left origin.x
   int mX2;   // x vector = width
   int mY;    // lower left origin.y
               // y vector = height
               // z vector = depth but not implement until 3D

   AnimationSingle * nFireEscapeLeft;
   AnimationSingle * nFireEscapeRight;

public:
   Level (int level, Tower * TowerParent);
   void AddFloor (FloorBase * floor);
   virtual void Update (float dt);
   virtual void Draw ();
};

#endif