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

// Here lies all your people. The purpose of this class it to keep track of people.
// Everyone in your city will be here including non-residents of your tower(s).
// This is stritly the data storage collection of persons and where they are created and destroyed.

#include <list>
#include <iostream>
#include "person.h"
#include "highriseException.h"

#include "citizens.h"

Citizens* Citizens::minstance = NULL;

Citizens* Citizens::get_Instance()
{
   if (minstance == NULL)
   {
      minstance = new Citizens();
   }
   return minstance;
}
void Citizens::destroy() // clear out the city
{
   try
   {
      if (minstance != NULL)
      {
         delete minstance;
      }
      minstance = NULL;
   }
   catch ( HighriseException* ex )
   {
      minstance = NULL;
      throw ex;            // pass on app generated exception
   }
   catch (...)
   {
      throw new HighriseException( "Error in cleaning up the Citezens collection" );
   }
}

Citizens::Citizens()
{

}

Citizens::~Citizens()
{
   std::cout << "Cleaning up Citizens";
   try
   {
      std::list<Person *>::iterator i;
      for (i = mPeople.begin (); i != mPeople.end (); i++)
      {
         Person* peep = (*i);
         delete peep;
      }
   }
   catch (...)
   {
      throw new HighriseException( "Error in Citezens destructor" );
   }
}

void Citizens::Update (float dt)
{
}

Person* Citizens::NewPerson()
{
   Location loc;
   Person* person = new Person( loc );
   mPeople.push_back (person);
   return person;
}

void Citizens::DestroyPerson( Person* person )
{
   std::list<Person *>::iterator i;
   for (i = mPeople.begin (); i != mPeople.end (); i++)
   {
      Person* peep = (*i);
      if (peep == person)
      {
         mPeople.remove(peep);
         delete peep;
      }
   }
}
