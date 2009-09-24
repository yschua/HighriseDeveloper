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
// Tick Tock!

#pragma once
#ifndef _SERIALIZERBASE_H
#define _SERIALIZERBASE_H

// NO CPP

class SerializerBase
{
public:
   SerializerBase () {};
   virtual ~SerializerBase () {};
   virtual SerializerBase* AddChild( const char*pName ) = 0;
   virtual void Add( const char* tag, int val ) = 0;
   virtual void Add( const char* tag, float val ) = 0;
   virtual void Add( const char* tag, const char* tr ) = 0;
};

#endif // _SERIALIZERBASE_H
