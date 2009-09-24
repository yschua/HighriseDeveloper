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
#include <string>
#include "xml/tinyxml/tinyxml.h"
#include "Types/String.h"
#include "XMLSerializer.h"

using namespace std;

XMLSerializer::XMLSerializer (TiXmlElement* pnParent)
:   mpnParent (pnParent)
{
}

XMLSerializer::~XMLSerializer ()
{
}

void XMLSerializer::Add( const char* tag, int val )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnVal = new TiXmlText(ToString(val).c_str());
   pnElement->LinkEndChild(pnVal);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::Add( const char* tag, float val )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnVal = new TiXmlText(ToString(val).c_str());
   pnElement->LinkEndChild(pnVal);
   mpnParent->LinkEndChild(pnElement);
}

void XMLSerializer::Add( const char* tag, const char* str )
{
   TiXmlElement* pnElement = new TiXmlElement(tag);
   TiXmlText* pnText = new TiXmlText(str);
   pnElement->LinkEndChild(pnText);
   mpnParent->LinkEndChild(pnElement);
}

SerializerBase* XMLSerializer::AddChild( const char* tag )
{
   TiXmlElement* pnSpace = new TiXmlElement(tag);
   mpnParent->LinkEndChild(pnSpace);
   return new XMLSerializer(pnSpace);
}