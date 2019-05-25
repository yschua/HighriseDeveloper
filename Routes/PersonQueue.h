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

#ifndef _PERSONQUEUE_H
#define _PERSONQUEUE_H

#include <queue>

class Person;

class PersonQueue 
{
public:
    PersonQueue();
    void AddPerson(Person* person);
    Person* TakeNextPerson();
    void Update();
    void Draw(int vx, int vy);

private:
    std::queue<Person*> m_queue;
};

#endif //_PERSONQUEUE_H
