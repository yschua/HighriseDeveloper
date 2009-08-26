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

struct Location; // from person
class C_Person;
class C_CitizensAgent;

class C_Citizens // : public C_Storage // add the serialization base
{
   friend C_CitizensAgent;
private:
   std::list <C_Person*> m_People;  // reverted back to a list as we will only use a forward iterator
protected:
   static C_Citizens* m_instance;

   C_Citizens();
   virtual ~C_Citizens(void);

public:
   // instance
   static C_Citizens* get_Instance();
   void destroy(); 
   // properties
   std::list <C_Person*>& get_Persons()
   {
      return m_People;
   }

   // methods
   C_Person* NewPerson();
   void DestroyPerson( C_Person* person );

   void C_Citizens::update (float dt);
   void Draw() {}; // nothing to draw unless we draw the people here
};

#endif //_CITIZENS_H
