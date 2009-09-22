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

#pragma once
#ifndef _INTERFACE_H
#define _INTERFACE_H

#include "Clock.h"
#include "Stats.h"

class Interface
{
private:

public:
   Interface ();
   Clock mClock;
   Stats mStats;

   int GetTimeOfDay() { return mClock.GetTimeOfDay();  }

   void PosCalc ();
   void Update (float dt);
   void Draw ();
};

#endif // _INTERFACE_H
