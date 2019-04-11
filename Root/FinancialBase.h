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

// root financial base for setting up cost and income of rooms
#pragma once
#ifndef _FINANCIALBASE_H
#define _FINANCIALBASE_H

class Tower;
class Scene;
class TiXmlElement;
class TiXmlNode;

// Tower is a ModelObject along with all the FloorSpace entities
// This renderes the Tower in the ModelSpaces with perspective, pan and zoom.
namespace Root
{
enum BillingFrequency { BF_Never = 0, BF_Daily, BF_Weekly, BF_Monthly, BF_Annually, BF_Custome }
}

class FinancialBase
{

private:
    double BaseCost;

public:
    FinancialBase(){};
    ~FinancialBase() {}
};

#endif //_FINANCIALBASE_H
