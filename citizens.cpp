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

C_Citizens* C_Citizens::m_instance = NULL;

C_Citizens* C_Citizens::get_Instance()
{
   if (m_instance == NULL)
   {
      m_instance = new C_Citizens();
   }
   return m_instance;
}
void C_Citizens::destroy() // clear out the city
{
   try
   {
      if(m_instance != NULL)
      {
         delete m_instance;
      }
      m_instance = NULL;
   }
   catch( C_HighriseException* ex )
   {
      m_instance = NULL;
      throw ex;            // pass on app generated exception
   }
   catch (...)
   {
      throw new C_HighriseException( "Error in cleaning up the Citezens collection" );
   }
}

C_Citizens::C_Citizens()
{

}

C_Citizens::~C_Citizens()
{
   std::cout << "Cleaning up C_Citizens";
   try
   {
      std::list<C_Person *>::iterator i;
      for (i = m_People.begin (); i != m_People.end (); i++)
      {
         C_Person* peep = (*i);
         delete peep;
      }
   }
   catch (...)
   {
      throw new C_HighriseException( "Error in Citezens destructor" );
   }
}

void C_Citizens::update (float dt)
{
}

C_Person* C_Citizens::NewPerson()
{
   Location loc;
   C_Person* person = new C_Person( loc );
   m_People.push_back (person);
   return person;
}

void C_Citizens::DestroyPerson( C_Person* person )
{
   std::list<C_Person *>::iterator i;
   for (i = m_People.begin (); i != m_People.end (); i++)
   {
      C_Person* peep = (*i);
      if (peep == person)
      {
         m_People.remove(peep);
         delete peep;
      }
   }
}
