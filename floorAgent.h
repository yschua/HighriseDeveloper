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
// look for vacancies and fill them.
// Might be able to partner with the citizens agent to find jobs and places to live and play.

#ifndef _FLOORAGENT_H
#define _FLOORAGENT_H

struct Location;

class C_FloorAgent
{
protected:
   C_level* m_Level;
    
public:
   C_FloorAgent ( C_level* level );
   ~C_FloorAgent ( );
   bool findSpace (Location& origin);
};

#endif
