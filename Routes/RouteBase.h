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

#ifndef _ROUTEBASE_H
#define _ROUTEBASE_H

#include "../Tower/FloorBase.h"
#include <vector>

class SerializerBase;
class Person;

class RouteBase
{
public:
    static BaseType GetBaseType() { return BaseSingleStair; }

    virtual bool SetCallButton(int from , int to) = 0;
    virtual void SetFloorButton(int to) = 0;
    virtual int LoadPerson(Person* person, int to) = 0; // return space remaining
    virtual void AddToQueue(int level, Person* person, int to) = 0;
    virtual bool StopsOnLevel(int level) = 0;
    virtual std::vector<int> GetConnectedLevels() const { return std::vector<int>(); }
    virtual int FindLobby() = 0;

    virtual void Update(float dt, int tod){};
    virtual void Update(float dt) = 0;
    virtual void Draw() = 0;
    virtual void Save(SerializerBase& ser) = 0;
};

#endif //_ROUTEBASE_H
