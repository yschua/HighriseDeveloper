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

#ifndef _BUILDREMOVESTRATEGY_H
#define _BUILDREMOVESTRATEGY_H

#include "BuildStrategies.h"

class BuildRemoveStrategy : public BuildStrategyBase
{
public:
    BuildRemoveStrategy(BuildData& rBuildData);
    ~BuildRemoveStrategy();
    bool PlacingRoom() override;
    bool BuildHere(Tower* pTower, int x, int y) override;
    void ShowGhostBuild(Tower* pTower) override;
};

#endif