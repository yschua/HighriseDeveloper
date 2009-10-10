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
#ifndef _SKYLOBBY_H
#define _SKYLOBBY_H

#include "FloorBase.h"
#include "../Graphics/ModelObject.h"

class Tiler;
class AnimationSingle;
class Level;
class SerializerBase;

class SkyLobby : public FloorBase, public Gfx::ModelObject
{
private:
   Tiler* mTile;

public:
   SkyLobby (int x, int x2, int level, Tower * TowerParent);
   static BaseType GetBaseType() { return BaseSkyLobby; }
   static const char* GetTypeString() { return "skylobby"; }

   void Update (float dt, int tod);
   void Draw ();
   void DrawFramework ();
   void Save(SerializerBase& ser);
};

#endif //_SKYLOBBY_H
