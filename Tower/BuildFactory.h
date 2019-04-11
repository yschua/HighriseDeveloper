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

// Data structure that defined rooms/floor space parameters.

#pragma once;
#ifndef _BUILDFACTORY_H
#define _BUILDFACTORY_H

class BuildStrategy;
class Tower;
struct BuildData;

namespace TowerObjects
{
class BuildFactory
{
protected:
    std::map<unsigned int, BuildData*> mBuildTypes;
    static BuildFactory* mInstance;

public:
    BuildFactory();
    BuildStrategyBase* CreateStrategy(int ToolID, Tower* pTower);
    static BuildFactory* GetInstance();

    typedef std::map<unsigned int, BuildData*>::iterator BuildTypeIterator;
    typedef std::map<unsigned int, BuildData*> BuildType;
    void Register(BuildData* bd);
    void Default(); // Build the initial set

    void Save(SerializerBase& ser);
    void Load(SerializerBase& ser);
};
}

#endif // _BUILDFACTORY_H
