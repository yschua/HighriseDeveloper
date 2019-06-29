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

#ifndef _CITIZENSAGENT_H
#define _CITIZENSAGENT_H

class Person;
class Tower;

class CitizensAgent
{
public:
    CitizensAgent(Tower& mTower);
    virtual ~CitizensAgent();
    void Update(int tod);
    void Draw();

private:
    void JobHunting(Person* person, int tod);

    Tower& mTower;
};

#endif //_CITIZENSAGENT_H
