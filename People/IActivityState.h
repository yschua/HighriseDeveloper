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

#ifndef _IACTIVITYSTATE_H
#define _IACTIVITYSTATE_H

class FloorBase;

class IActivityState
{
public:
    enum class Id {Home, Work, Lunch};
    virtual ~IActivityState() = default;
    virtual void Update(int time) = 0;
    //virtual void HandleInput() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;
    virtual FloorBase* GetLocation() const = 0;
};

#endif // _IACTIVITYSTATE_H
