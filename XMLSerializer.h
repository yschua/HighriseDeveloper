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
#ifndef _XMLSERIALIZER_H
#define _XMLSERIALIZER_H

#include "SerializerBase.h"

class TiXmlElement;
// NO CPP

class XMLSerializer : public SerializerBase
{
protected:
   TiXmlElement* mpnParent;
public:
   XMLSerializer (TiXmlElement* pnParent);
   virtual ~XMLSerializer ();
   virtual SerializerBase& AddChild( const char*pName );
   void Add( const char* tag, int val );
   void Add( const char* tag, float val );
   void Add( const char* tag, const char* str );
};

#endif // _XMLSERIALIZER_H
