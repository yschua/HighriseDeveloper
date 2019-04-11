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

// These are all the people or citizens of your city some are in your tower(s) others are looking for a place
// to work, eat, shop and sleep or just hang out. The more of them you get the more profits you should see.

#ifndef _CITIZENS_H
#define _CITIZENS_H

#include <list>

struct Location; // from person
class Person;
class CitizensAgent;

class Citizens // : public Storage // add the serialization base
{
    friend class CitizensAgent;

private:
    std::list<Person*> mPeople; // reverted back to a list as we will only use a forward iterator
protected:
    static Citizens* minstance;

    Citizens();
    virtual ~Citizens(void);

public:
    // instance
    static Citizens* get_Instance();
    void destroy();
    // properties
    std::list<Person*>& get_Persons() { return mPeople; }
    size_t GetPopulation() { return mPeople.size(); }
    size_t GetPopulationForTower(int Tower);

    // methods
    Person* NewPerson();
    void DestroyPerson(Person* person);

    void Update(float dt);
    void Draw(); // draw the people here
};

#endif //_CITIZENS_H
