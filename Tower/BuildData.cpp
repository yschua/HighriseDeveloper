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

#include <iostream>
#include "../Root/SerializerBase.h"

#include "BuildData.h"

BuildData::BuildData ()
{
   BuildType = 0;
   Variant = 0;
   LevelsHigh = 0;
   UnitsWide = 0;
   EconomicEffect = 0;
   NeighborEffect = 0;
   MaxPeople = 1;
   MinPeople = 0;
   AmountPerPerson = 10;
   RentFrequency = 1;
   BuildCost = 1000.0;    
   PurchasePrice = 5000.0;
   RentalCost = 10.0;   
   IncomeFactor = 1.0;
   ImageName = "";
}

void BuildData::Load(SerializerBase& ser)
{
   BuildType = (short)ser.GetInt("BuildType");
   Variant = (short)ser.GetInt("Variant");
   LevelsHigh = (short)ser.GetInt("LeveleHigh");
   UnitsWide = (short)ser.GetInt("UnitsWide");
   EconomicEffect = (short)ser.GetInt("EconomicEffect");
   NeighborEffect = (short)ser.GetInt("NeighborEffect");
   MaxPeople = (short)ser.GetInt("MaxPeople");
   MinPeople = (short)ser.GetInt("MinPeople");
   RentFrequency = (short)ser.GetDouble("RentFrequency");
   AmountPerPerson= ser.GetDouble("AmountPerPerson");
   BuildCost = ser.GetDouble("BuildCost");
   PurchasePrice = ser.GetDouble("PurchasePrice");
   RentalCost = ser.GetDouble("RentalCost");
   IncomeFactor = ser.GetDouble("IncomeFactor");
   ImageName = ser.GetString("Image");
}

// Use by the levels editor
void BuildData::Save(SerializerBase& ser)
{
   ser.Add("Type", "FloorSpace");   // first tag
   ser.Add("BuildType", BuildType);
   ser.Add("Variant", Variant);
   ser.Add("LeveleHigh", LevelsHigh);
   ser.Add("UnitsWide", UnitsWide);
   ser.Add("EconomicEffect", EconomicEffect);
   ser.Add("NeighborEffect", NeighborEffect);
   ser.Add("MaxPeople", MaxPeople);
   ser.Add("MinPeople", MinPeople);
   ser.Add("AmountPerPerson", AmountPerPerson);
   ser.Add("RentFrequency", RentFrequency);
   ser.Add("BuildCost", BuildCost);
   ser.Add("PurchasePrice", PurchasePrice);
   ser.Add("RentalCost", RentalCost);
   ser.Add("IncomeFactor", IncomeFactor);
   ser.Add("Image", ImageName.c_str());
}