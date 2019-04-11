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

// Data structure that defined rooms/floor space parameters.

#pragma once;
#ifndef _BUILDDATA_H
#define _BUILDDATA_H

#include <string>

class SerializerBase;

struct BuildData {
    short BuildType; // office, condo, retail etc.
    short Variant;
    short LevelsHigh;
    short UnitsWide;
    short EconomicEffect;   // +/- influence on surrounding tenants.
    short NeighborEffect;   // +/- good or bad neightboor -(noisy, cooking or checmical oders)
                            // +(library,residential)
    short MaxPeople;        // Max people allowed
    short MinPeople;        // Min people needed for this to function
    short RentFrequency;    // zero for one time
    double AmountPerPerson; // cost or income per person.
    double BuildCost;       // cost to the Tower owner to build
    double PurchasePrice;   // condo and other space purchase. Some may have rent fees
    double RentalCost;      // periodic fee for lease and maintenace fees on purchased spaces.
    double IncomeFactor;    // zero for
    std::string ImageName;

    BuildData();
    BuildData(SerializerBase* ser) { Load(*ser); }

    void SetDefault(short type, short units, short levels, double cost, double price, double rent)
    {
        BuildType = type;
        LevelsHigh = levels;
        UnitsWide = units;
        BuildCost = cost;
        PurchasePrice = price;
        RentalCost = rent;
    }
    void Save(SerializerBase& ser);
    void Load(SerializerBase& ser);
};

#endif // _BUILDDATA_H
